# run socket client

## usage

* cpp版本

```shell
# 设置server的ip addr 和 port 修改 main.cpp的ip_addr和port

# 编译程序
mkdir build && cd ./build
make -j && make install

# 测试程序
cd ./install
./test_socket_client (需要先打开test_socket_server)
input: (需要在命令行输入图像路径 ex: ../data/6.jpg) 会打印出检测结果

# 结束程序关闭socket connect
input: break
``` 

* python3版本

```shell
cd ./python3
python3 test_socket_client.py (需要先打开test_socket_server)
input: (需要在命令行中输入图像路径 ex: ../data/6.jpg) 会打印出检测结果
```
