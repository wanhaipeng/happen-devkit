# -*- coding: utf-8 -*-
"""test video"""
import cv2
import time

cap = cv2.VideoCapture("../data/det.h264")
fps = cap.get(cv2.CAP_PROP_FPS)
print("video fps: {}".format(fps))

size = (cap.get(cv2.CAP_PROP_FRAME_HEIGHT), cap.get(cv2.CAP_PROP_FRAME_WIDTH))
print("video resolution: {}".format(size))

frame_num = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
print("total frame: {}".format(frame_num))

cnt = 0
while cap.isOpened():
  ret, frame = cap.read()
  # time.sleep(0.1)
  if ret == 0:
    break
  cnt += 1

cap.release()
print("total frame real: {}".format(cnt))
