#!/bin/sh -e

cd linux_binaries

cp ../scripts/linux/nbinit.config .

./core_tests
./game_tests
