### Environment

This software was developed under Linux, but it's also been built and run on
Windows.

### OpenGL Dependencies

The program has an OpenGL component, so the following dependencies are
required.

GLFW
  Download and extract the source.  Version 3.0.4 was used during development.
    sudo apt-get install libglu1-mesa-dev xorg-dev (from install guide)
    mkdir build
    cd build
    cmake -DBUILD_SHARED_LIBS=ON ..
    make
    sudo make install
  The libraries will be in /usr/local/lib/, and the headers will be in /usr/local/include/

GLM
  Download and extract the source.  Version 0.9.5.3 was used during development.
  sudo cp -R glm/glm /usr/local/include/

GLEW
  Download and extract the source.  Version 1.6.0-4 was available in the Ubuntu
  12.04 repos and was used during development.  The most recent stable version
  was 1.10.0 during development.  Build instructions for 1.10.0 are outlined
  below (custom install dir of /usr/local).
    make
    sudo make install GLEW_DEST=/usr/local

### Pattern Databases

The pattern databases used for the optimal solver are quite large, roughly a
gigabyte in total.  The databases are stored using git lfs (Large File
Storage).  Install the [git-lfs](https://git-lfs.github.com/) plugin prior to
cloning the repository, and the pattern databases will be downloaded
automatically.  Alternatively, wipe out the files in the `Data` directory and
the program will initialize the databases on first run, although that will take
a long time (the better part of a day).

### Build and Run

Use an out-of-tree build.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
```

The program must be run from the base directory, because certain files (pattern
databases and shaders) are loaded relatively.

```
./build/rubiksCube
```

