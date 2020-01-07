#pragma once
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <string>
#include <queue>
#include <stack>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>

/**
 * @brief global repository
 * 
 * the class of multi thread common data repository
 */
class Grepository {
 public:
  /**
   * @brief the constructor of Global repository.
   *
   * @param thread_num input stream num
   * @param dropped whether dropped frame]
   */
  Grepository(int threads_num, bool dropped);
  ~Grepository() {};

  /**
   * @brief put the img data into global repository.
   * 
   * @param i_img input image data
   */
  void produce_data(cv::Mat i_img);

  /**
   * @brief get the img data from global repository.
   * 
   * @return the img data
   */
  cv::Mat consume_data();

  /**
   * @brief check global buffer is full
   * 
   * @return whether buffer is full
   */
  bool is_full();

  /**
   * @brief check global buffer is empty
   * 
   * @return whether buffer is empty
   */
  bool is_empty();

  /**
   * @brief get global data mutex
   *
   * @return the mutex of global data
   */
  std::mutex& get_mtx();

 private:
  int max_buffer_size_; // max buffer size [10 * thread_num]
  int current_buffer_size_ = 0; // current buffer size
  bool dropped_; // whether dropped
  std::queue<cv::Mat> nondropped_buffer_; // g_buffer for nondropped
  std::stack<cv::Mat> dropped_buffer_; // g_buffer for dropped
  std::mutex mtx_;
  std::condition_variable buffer_not_empty_;
  std::condition_variable buffer_not_full_;
};

/**
 * @brief produce preprocessed frame data from current video stream
 * 
 * @param g_data global data repository
 * @param input_path input video stream file path
 * @param loops_num set current thread frame numbers
 * @param thread_id set current thread id
 */
void produce(Grepository& g_data,
             std::string& input_path,
             int loops_num,
             int thread_id);

/**
 * @brief consume preprocessed frame data
 * 
 * @param g_data global data repository
 * @param input_path input model data file path
 * @param thread_id set current thread id
 */
void consume(Grepository& g_data,
             std::string& model_path,
             int thread_id);