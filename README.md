# happen-devkit
> 记录工作中一些实用的开发工具和设计模式

## 1. network programming

### 1.1. detection_socket
> 使用socket通信完成简单的目标检测流程数据传输

* 语言: cpp/python
* 结构
  - server: accept video stream or image file，finish detect and return detection result
  - client: send video stream or image file， accept detection result

## 2. multi-thread programming

### 2.1. producer-consumer
> 使用生产者消费者模型完多路视频流的处理
