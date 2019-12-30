# -*- coding=utf-8 -*-
"""test socket server."""

import os
import sys
import socket
import threading
import time
import cv2
import numpy as np

def run_detect(net, file_path):
  """ detected upload image. (yolov3)

  Parameters
  ----------
  net : network instance
    inference engine
  file_path : str
    upload file path

  Returns
  -------
  detected_str : str
    detected result string
  """
  pass


def process_upload_data(conn, addr, net):
  """ process received data.

  Parameters
  ----------
  conn : socket.connect
    connect instance between server and client
  addr : client addr
    the addr of client
  net : sail.Engine
    bitmain inference engine
  """
  while True:
    upload_data_path = "./upload_data"
    data_info = conn.recv(1024) # recv file_info
    data_info_str = bytes.decode(data_info)
    server_check_file_info = data_info_str
    conn.sendall(str.encode(server_check_file_info))
    if data_info_str == "break":
      break
    if len(data_info_str.split('|')) == 2:
      filename = data_info_str.split('|')[0]
      filesize = data_info_str.split('|')[1]
      upload_data_path = os.path.join(upload_data_path, filename)
      filesize = int(filesize)
      # save upload image
      has_receive_bytes = 0
      with open(upload_data_path, 'wb') as f:
        while has_receive_bytes != filesize:
          inner_data = conn.recv(1024) # receive 1024 bytes from client
          f.write(inner_data)
          has_receive_bytes += len(inner_data) # update received bytes
          # print("\033[32m" + " - receive: {} bytes".format(len(inner_data)) + '\033[0m')
      print('\033[32m' + " - received: {}".format(data_info_str) + '\033[0m')
      result = run_detect(net, upload_data_path)
      conn.sendall(str.encode(result)) # send detected result to client


def socket_service(net):
  """ socket server on se3/5.

  Parameters
  ----------
  net : sail.Engine
    bitmain inference engine
  """
  try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket object
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # set socket options
    s.bind(('xxx.xxx.xxx.xxx', 6666)) # bind server ip && port
    s.listen(10)
  except socket.error as msg:
    print('\033[31m' + msg + '\033[0m')
    sys.exit(1)
  print('\033[32m' + " - Waiting connection..." + '\033[0m')
  while True:
    conn, addr = s.accept()
    print('\033[32m' + " - Accept {} request".format(addr) + '\033[0m')
    process_upload_data(conn, addr, net)
    conn.close()
  s.close()


if __name__ == '__main__':
  net = init_model()
  socket_service(net)
