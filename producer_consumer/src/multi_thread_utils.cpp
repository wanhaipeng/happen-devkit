#include "multi_thread_utils.hpp"

Grepository::Grepository(int threads_num, bool dropped) {
  max_buffer_size_ = 10 * threads_num;
  dropped_ = dropped;
}

void Grepository::produce_data(cv::Mat i_img) {
  std::unique_lock<std::mutex> lock(mtx_);
  while(is_full()) { // buffer is full, wait here
    std::cout << "produces is waiting for a empty place in buffer..." << std::endl;
    buffer_not_full_.wait(lock);
  }
  if (dropped_) {
    std::cout << "to be implemented" << std::endl;
  } else {
    nondropped_buffer_.push(i_img);
    current_buffer_size_++;
  }
  buffer_not_empty_.notify_all();
  lock.unlock();
}

cv::Mat Grepository::consume_data() {
  cv::Mat data;
  std::unique_lock<std::mutex> lock(mtx_);
  while(is_empty()) { // buffer is empty, wait here
    std::cout << "consumer is waiting for a avalible data in buffer..." << std::endl;
    buffer_not_empty_.wait(lock);
  }
  if (dropped_) {
    std::cout << "to be implemented" << std::endl;
  } else {
    data = nondropped_buffer_.front();
    nondropped_buffer_.pop();
    current_buffer_size_--;
  }
  buffer_not_full_.notify_all();
  lock.unlock();
  return data;
}

bool Grepository::is_full() {
  return (current_buffer_size_ == max_buffer_size_);
}

bool Grepository::is_empty() {
  return (current_buffer_size_ == 0);
}

std::mutex& Grepository::get_mtx() {
  return mtx_;
}

void produce(Grepository& g_data, std::string& input_path,
             int loops_num, int thread_id) {
  // check input file exist
  struct stat input_buffer;
  if (stat(input_path.c_str(), &input_buffer) != 0) {
    std::cout << "input: " << input_path << " does not exist!" << std::endl;
    exit(-1);
  }
  // check input stream status
  int total_loops = loops_num;
  cv::VideoCapture cap(input_path);
  if (!cap.isOpened()) {
    std::cout << "Open video stream failed!" << std::endl;
    exit(-1);
  }
  cv::Mat frame;
  while(cap.read(frame)) {
    // finish default loops
    loops_num--;
    if (loops_num < 0) { break; }
    // produce data
    g_data.produce_data(frame);
    {
      std::lock_guard<std::mutex> lock(std::mutex);
      std::cout << "producer: " << thread_id 
                << " produce: " << (total_loops - loops_num)
                << " data shape: [" << frame.rows << " "
                << frame.cols << "]" << std::endl;
    }
  }
  std::cout << "producer exit!" << std::endl;
}

void consume(Grepository& g_data, std::string& model_path,
             int thread_id) {
  int consume_num = 1;
  while(true) {  // consume image data
    // consume data
    cv::Mat input_data = g_data.consume_data();
    sleep(0.1); // wait 100ms simulate inference 10fps
    {
      std::lock_guard<std::mutex> lock(std::mutex);
      std::cout << "consumer: " << thread_id
                << " consume: " << consume_num << std::endl;
    }
    consume_num++;
  }
  std::cout << "consumer exit!" << std::endl;
}