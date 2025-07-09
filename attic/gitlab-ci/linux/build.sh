#!/bin/sh -e

mkdir -p build

cd build
rm -f CMakeCache.txt

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DNEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX=ON \
  -DNEWBORN_USE_JEMALLOC=ON \
  -DNEWBORN_ENABLE_STEAM_INTEGRATION=ON \
  -DCMAKE_INCLUDE_PATH=../lib/linux/include \
  -DCMAKE_LIBRARY_PATH=../lib/linux \
  ../source

make -j2

cd ..

mv dist linux_binaries
cp lib/linux/*.so linux_binaries/
