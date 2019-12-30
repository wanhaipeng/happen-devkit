#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/**
 * @brief init socket connection.
 *
 * @param ip_addr  server ip address
 * @param port     server link port
 * @return the sockfd socket descriptor
 */
int init_socket(std::string ip_addr, int port);

/**
 * @brief split str by input char
 *
 * @param input_str  input string
 * @param input_char input char
 * @return the split string vector
 */
std::vector<std::string> split_str(std::string input_str, char input_char);
