#!/bin/sh -e

mkdir client_distribution
mkdir client_distribution/assets
mkdir client_distribution/assets/user

mkdir client_distribution/mods
touch client_distribution/mods/mods_go_here

mkdir client_distribution/linux
cp \
  dist/newborn \
  lib/linux/libdiscord_game_sdk.so \
  lib/linux/libsteam_api.so \
  scripts/ci/linux/nbinit.config \
  scripts/ci/linux/run-client.sh \
  client_distribution/linux/

mkdir server_distribution
mkdir server_distribution/assets

mkdir server_distribution/mods
touch server_distribution/mods/mods_go_here

mkdir server_distribution/linux

# makes the server function on older Linux versions (this is so stupid)
nm --dynamic --undefined-only --with-symbol-versions dist/newborn_server | grep GLIBC_2.29
./scripts/ci/linux/patchelf dist/newborn_server \
  --clear-symbol-version exp \
  --clear-symbol-version exp2 \
  --clear-symbol-version log \
  --clear-symbol-version log2 \
  --clear-symbol-version pow

cp \
  dist/newborn_server \
  scripts/ci/linux/run-server.sh \
  scripts/ci/linux/nbinit.config \
  server_distribution/linux/

tar -cvf client.tar client_distribution
tar -cvf server.tar server_distribution
