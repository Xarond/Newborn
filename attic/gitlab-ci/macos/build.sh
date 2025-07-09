#!/bin/sh -e

mkdir -p build
cd build

rm -f CMakeCache.txt

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DNEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX=ON \
  -DNEWBORN_USE_JEMALLOC=OFF \
  -DNEWBORN_ENABLE_STEAM_INTEGRATION=ON \
  -DNEWBORN_ENABLE_DISCORD_INTEGRATION=ON \
  -DCMAKE_INCLUDE_PATH=../lib/osx/include \
  -DCMAKE_LIBRARY_PATH=../lib/osx \
  -DCMAKE_OSX_SYSROOT=/ \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 \
  ../source

make -j2

cd ..

mv dist macos_binaries
cp lib/osx/*.dylib macos_binaries/
