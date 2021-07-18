#!/bin/bash

PREFIX_PATH=$HOME/local_linux_amd64

cd geco

echo "Building Debug"
mkdir -p build_pc_d
cd build_pc_d
cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_INSTALL_PREFIX=$PREFIX_PATH \
  .. 
make -j`nproc`  
cd ..

exit 0
echo "Building Release"
mkdir -p build_pc_r
cd build_pc_r
cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=$PREFIX_PATH \
  .. > log_make 2>&1
make -j`nproc` install >> log_make 2>&1 
cd ..

