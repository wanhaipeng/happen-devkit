# -*- coding=utf-8 -*-
"""test socket client."""

import os
import sys
import socket
import time
import numpy as np

def send_data(s, file_path):
  """ send data.

  Parameters
  ----------
  s : socket.socket
    create socket instance
  file_path : str
    input file path
  """
  if file_path == "break":
    file_info = file_path
  else:
    file_name = file_path.strip().split('/')[-1]
    file_size = os.stat(file_path).st_size
    # print(file_name, file_size)
    file_info = "%s|%s" % (file_name, file_size)
  s.sendall(str.encode(file_info))
  server_check_file_info = bytes.decode(s.recv(1024))
  print('\033[32m' + " - server check: {}".format(server_check_file_info) + '\033[0m')
  if file_info == "break":
    return
  has_send_bytes = 0
  with open(file_path, 'rb') as f:
    while has_send_bytes != file_size:
      inner_data = f.read(1024)
      s.sendall(inner_data) # send 1024 bytes to server
      has_send_bytes += len(inner_data) # update send bytes
      # print('\033[32m' + "send: {} bytes".format(len(inner_data)) + '\033[0m')
  print('\033[32m' + " - sended: {}".format(file_info) + '\033[0m')
  result = s.recv(1024)
  print('\033[32m' + " - detected: {}".format(bytes.decode(result)) + '\033[0m')

def socket_client():
  """ socket client on master pc.
  """
  try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('10.30.34.172', 6666))
  except socket.error as msg:
    print('\033[31m', msg, '\033[0m')
    sys.exit(1)
  print('\033[32m' + " - Create connection..." + '\033[0m')
  while True:
    file_path = input("input: ").strip()
    if len(file_path) == 0:
      continue
    send_data(s, file_path)
    if file_path == "break":
      break
  s.close()
        


if __name__ == '__main__':
  socket_client()
