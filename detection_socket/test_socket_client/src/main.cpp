#include "socket_client.hpp"

void send_data(int sockfd, std::string file_path) {
  std::ifstream filei;
  std::string file_name, file_info;
  int file_size = 0;
  if (file_path == "break") {
    file_info = file_path;
  } else {
    // get input file name
    std::vector<std::string> split_file_path = split_str(file_path, '/');
    file_name = split_file_path[split_file_path.size() - 1];
    // get input file size
    filei.open(file_path.c_str(), std::ios::in | std::ios::binary); 
    if (!filei) {
      std::cout << "open file error: " << file_path << std::endl;
    }
    filei.seekg(0, filei.end); // go to the end
    file_size = filei.tellg();
    file_info = file_name + '|' + std::to_string(file_size);
    filei.seekg(0, filei.beg); // go back to the beginning
  }
  // send file_info to server
  int sd_size = send(sockfd, file_info.c_str(), file_info.length(), 0);
  // std::cout << " - check file_info size: " << sd_size << file_info << std::endl;
  // server check for fix tcp package bug
  char* server_check = new char[1024];
  int check_size = recv(sockfd, server_check, 1024, 0);
  server_check[check_size] = '\0';
  std::cout << " - server check: " << server_check << std::endl;
  delete [] server_check;
  if (file_info == "break") {
    return;
  }
  int tobe_send_bytes = file_size;
  size_t inner_size = 1024;
  char* inner_data = new char[1024];
  while (tobe_send_bytes != 0) {
    if (tobe_send_bytes >= 1024) {
      inner_size = 1024;
    } else {
      inner_size = tobe_send_bytes;
    }
    filei.read(inner_data, inner_size);
    int size_rt = send(sockfd, inner_data, inner_size, 0);
    tobe_send_bytes -= inner_size;
    // std::cout << " - send: " << size_rt << " bytes" << std::endl;
  }
  delete [] inner_data;
  std::cout << " - sended: " << file_info << std::endl;
  filei.close();
  // recv result with result_size
  char* result = new char[10*1024];
  int result_size = recv(sockfd, result, 10240, 0);
  result[result_size] = '\0';
  // std::cout << " - result size: " << result_size << " bytes" << std::endl;
  std::cout << " - detected: " << result << std::endl;
  delete [] result;
}

int main(int argc, char* argv[]){
  // set server ip addr and port
  std::string ip_addr = "xxx.xxx.xxx.xxx";
  int port = 6666;
  // init socket
  int sockfd = init_socket(ip_addr, port);
  // input file path && send file && get result
  std::string file_path;
  while(1) {
    std::cout << "input: ";
    std::getline(std::cin, file_path);
    if (file_path.length() == 0) {
      continue;
    }
    send_data(sockfd, file_path);
    if (file_path == "break") {
      break;
    }
  } 
  close(sockfd);
  return 0;
}
