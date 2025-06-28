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
cp dist/*.dylib client_distribution/osx/Newborn.app/Contents/MacOS/
cp \
  dist/newborn_server \
  dist/planet_mapgen \
  scripts/ci/macos/nbinit.config \
  scripts/ci/macos/run-server.sh \
  client_distribution/osx/