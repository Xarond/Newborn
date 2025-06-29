#!/bin/sh -e

mkdir client_distribution
mkdir client_distribution/assets
mkdir client_distribution/assets/user

mkdir client_distribution/mods
touch client_distribution/mods/mods_go_here

mkdir client_distribution/osx
cp -LR scripts/ci/macos/Newborn.app client_distribution/osx/
mkdir client_distribution/osx/Newborn.app/Contents/MacOS
cp dist/newborn client_distribution/osx/Newborn.app/Contents/MacOS/
cp lib/osx/x64/libsteam_api.so/*.dylib client_distribution/osx/Newborn.app/Contents/MacOS/
cp \
  dist/newborn_server \
  scripts/ci/macos/nbinit.config \
  scripts/ci/macos/run-server.sh \
  client_distribution/osx/

tar -cvf client.tar client_distribution
