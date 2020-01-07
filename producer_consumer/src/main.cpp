#include <getopt.h>
#include "multi_thread_utils.hpp"

void usage() {
  std::cout << "Usage: mutil_thread \n [--bmodel bmode_path] \n"
            << " [--input input_path] \n [--threads threads_num] \n"
            << " [--loops loops_num] \n"
            << " [--dropped frame_dropped]" << std::endl;
}

void test_multi_thread(std::string& bmodel_path, std::string& input_path,
                       int threads_num, int loops_num, bool dropped) {
  Grepository g_data(threads_num, dropped);
  // init producer
  std::vector<std::thread> producer_thread_pool(threads_num);
  for (int i = 0; i < threads_num; i++) {
    producer_thread_pool[i] = 
      std::thread(produce, std::ref(g_data), std::ref(input_path), loops_num, i);
  }
  // init consumer
  std::thread consumer_0(consume, std::ref(g_data), std::ref(bmodel_path), 0);
  // join thread
  for (int i = 0; i < threads_num; i++) {
    producer_thread_pool[i].join();
  }
  consumer_0.join();
}

int main(int argc, char* argv[]) {
  // set bmodel path / input path / thread num / dropped frame
  std::string bmodel_path, input_path;
  int threads_num = 1, loops_num = 1, c;
  bool dropped = false;

  // set options str
  const char* opt_strings = "b:i:t:c";
  const struct option long_opts[] {
    {"bmodel", required_argument, nullptr, 'b'},
    {"input", required_argument, nullptr, 'i'},
    {"threads", required_argument, nullptr, 't'},
    {"loops", required_argument, nullptr, 'l'},
    {"dropped", no_argument, nullptr, 'd'}
  };
  while ((c = getopt_long(argc, argv, opt_strings, long_opts, nullptr)) != -1) {
    switch(c) {
      case 'b':
        bmodel_path = optarg; break;
      case 'i':
        input_path = optarg; break;
      case 't':
        threads_num = std::stoi(optarg); break;
      case 'l':
        loops_num = std::stoi(optarg); break;
      case 'd':
        dropped = true; break;
      default:
        usage(); break;
    }
  }
  // check arg
  std::cout << "bmodel_path: " << bmodel_path << std::endl;
  std::cout << "input_path: " << input_path << std::endl;
  std::cout << "threads_num: " << threads_num << std::endl;
  std::cout << "loops_num: " << loops_num << std::endl;
  std::cout << "dropped frame: " << dropped << std::endl;
  if (input_path.empty()) {
    usage();
    exit(-1);
  }
  test_multi_thread(bmodel_path, input_path, threads_num, loops_num, dropped);
  return 0;
}