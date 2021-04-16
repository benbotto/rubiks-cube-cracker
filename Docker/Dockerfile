FROM ubuntu:20.04

# Env vars for the nvidia-container-runtime.
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute

# tzdata.
ENV DEBIAN_FRONTEND=noninteractive

ARG UID=1000

WORKDIR /var/src/

# Note that only the dependencies up to and including libglu1-mesa-dev are
# required for building the application.  The others are for running the OpenGL
# component from inside the docker container.  For more detail, see:
# https://medium.com/@benjamin.botto/opengl-and-cuda-applications-in-docker-af0eece000f1
RUN apt-get update \
  && apt-get install -qq -y \
    g++ \
    cmake \
    pkg-config \
    wget \
    unzip \
    xorg-dev \
    libglu1-mesa-dev \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6 \
  && rm -rf /var/lib/apt/lists/*

# GLFW.
RUN wget https://github.com/glfw/glfw/releases/download/3.3.3/glfw-3.3.3.zip \
  && unzip glfw-3.3.3.zip \
  && cd glfw-3.3.3 \
  && mkdir build \
  && cd build \
  && cmake -DBUILD_SHARED_LIBS=ON .. \
  && make -j4 \
  && make install \
  && cd ../../ \
  && rm -rf glfw*

# GLM.
RUN wget https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip \
  && unzip glm-0.9.8.5.zip \
  && cp -R glm/glm /usr/local/include/ \
  && rm -rf glm*

# GLEW.
RUN wget https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip \
  && unzip glew-2.2.0.zip \
  && cd glew-2.2.0 \
  && make -j4 \
  && make install GLEW_DEST=/usr/local \
  && cd .. \
  && rm -rf glew*

# Local user with supplied UID (default 1000).
RUN adduser \
    --disabled-password \
    --gecos '' \
    --uid $UID \
    rubik

USER rubik
