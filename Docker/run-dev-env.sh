#!/bin/bash

docker run --rm -it --gpus all \
  -u $(id -u):$(id -g) \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v `pwd`:/var/src \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  avejidah/rubiks-cube-cracker-builder:4.0.0 \
  bash
