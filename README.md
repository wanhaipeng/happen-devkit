# happen-devkit
> 记录工作中一些实用的开发工具和设计模式

## 1. network programming

### 1.1. detection_socket
> 使用socket通信完成简单的目标检测流程数据传输

* 语言: cpp/python
* 结构:
  - server: 接受视频流或者图像文件，返回检测结果
  - client: 发送视频流或者图像文件，接受检查结果

## 2. multi-thread programming

### 2.1. producer-consumer
> 使用生产者消费者模型完多路视频流的处理

* 语言: cpp/python
* 特性:
  - producer: 解析视频流并做预处理
  - consumer: 从共享内存中取出视频帧做后续处理
  - dropped: 目前只实现了不丢帧的处理流程适用于本地视频流，网络视频流通常需要丢帧处理