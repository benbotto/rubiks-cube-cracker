### Environment

This software was developed under Linux, but it's also been built and run on
Windows.

### Using Docker

The easiest way to build run the application is with Docker.  However, since
the application uses OpenGL to render the cube, the [NVIDIA Container
Toolkit](https://github.com/NVIDIA/nvidia-docker) must be installed. Once
installed, a dev environment can be run by running:

```
./Docker/run-dev-env.sh
```

The application code will be mounted under `/var/src/` inside the container.

Docker image can be built using the `Docker/build.sh` script (a version number,
e.g. 4.0.1, is required as an argument.

### Without Docker: OpenGL Dependencies

To build the application without Docker, the `Docker/Dockerfile` serves as a
requirements document, as it encapsulates all the dependencies and shows how to
configure a development environment.  Below is a brief description of the
library requirements.  The commands below can be run from a temporary
directory.

###### GLFW

Version 3.3.3 was used during development.

```
wget https://github.com/glfw/glfw/releases/download/3.3.3/glfw-3.3.3.zip \
  && unzip glfw-3.3.3.zip \
  && cd glfw-3.3.3 \
  && mkdir build \
  && cd build \
  && cmake -DBUILD_SHARED_LIBS=ON .. \
  && make -j4 \
  && sudo make install \
  && cd ../../ \
  && rm -rf glfw*
```

The libraries will be in `/usr/local/lib/`, and the headers will be in
`/usr/local/include/`.

###### GLM

Version 0.9.8.5 was used during development.

```
wget https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip \
  && unzip glm-0.9.8.5.zip \
  && sudo cp -R glm/glm /usr/local/include/ \
  && rm -rf glm*
```

Headers will be in `/usr/local/include/`.

###### GLEW

The most recent stable version was 2.2.0 during development.

```
wget https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip \
  && unzip glew-2.2.0.zip \
  && cd glew-2.2.0 \
  && make -j4 \
  && sudo make install GLEW_DEST=/usr/local \
  && cd .. \
  && rm -rf glew*
```

Libraries will be in `/usr/local/lib64/`, and headers will be in
`/usr/local/include/GL/`.

### Pattern Databases

The pattern databases used for the solvers are quite large, roughly a gigabyte
in total.  The databases are stored using git lfs (Large File Storage).
Install the [git-lfs](https://git-lfs.github.com/) plugin prior to cloning the
repository, and the pattern databases will be downloaded automatically.
Alternatively, wipe out the files in the `Data` directory and the program will
initialize the databases on first run, although that will take a long time (the
better part of a day).

### Build and Run

Use an out-of-tree build.

```
mkdir build
cd build
cmake ..
make -j4
cd ..
```

The program must be run from the base directory, because certain files (pattern
databases and shaders) are loaded relatively.

```
./build/rubiksCube
```

### Debug Build

```
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
cd ..
```

Run with gdb:

```
gdb ./debug/rubiksCube
```

