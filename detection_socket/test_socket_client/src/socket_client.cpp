#include "socket_client.hpp"

int init_socket(std::string ip_addr, int port) {
  // create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cout << "create socket error: " << strerror(errno) << std::endl;
    exit(-1);
  }
  // create server addr
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET; // use ipv4 address
  servaddr.sin_port = htons(port);
  if (inet_pton(AF_INET, ip_addr.c_str(), &servaddr.sin_addr) <= 0) {
    std::cout << "inet_pton error for " << ip_addr << std::endl;
    exit(-1);
  }
  // create connect
  int conn_status = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  if (conn_status < 0) {
    std::cout << "connect error: " << strerror(errno) << std::endl;
    exit(-1);
  }
  return sockfd;
}

std::vector<std::string> split_str(std::string input_str, char input_char) {
  // replace input_char by blank space
  int str_size = input_str.length();
  for (int i = 0; i < str_size; i++) {
    if (input_str[i] == input_char) {
      input_str[i] = ' ';
    }
  }
  std::istringstream out(input_str);
  std::string temp_str;
  std::vector<std::string> output;
  while(out >> temp_str) {
    output.emplace_back(temp_str);
  }
  return output;
}
