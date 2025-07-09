#!/bin/sh -e

cd macos_binaries

cp ../scripts/osx/nbinit.config .

./core_tests
./game_tests

