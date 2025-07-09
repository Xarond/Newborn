#!/bin/sh -e

mkdir client_distribution
mkdir client_distribution/assets
mkdir client_distribution/tiled

./linux_binaries/asset_packer -c scripts/packing.config assets/packed client_distribution/assets/packed.pak
cp -r assets/user client_distribution/assets/

cp -r tiled/packed client_distribution/tiled/

cp -r doc client_distribution/doc

mkdir client_distribution/mods
touch client_distribution/mods/mods_go_here

mkdir client_distribution/win64
cp -r \
  windows_binaries/newborn.exe \
  windows_binaries/newborn.pdb \
  windows_binaries/newborn_server.exe \
  windows_binaries/mod_uploader.exe \
  windows_binaries/*.dll \
  windows_binaries/iconengines \
  windows_binaries/imageformats \
  windows_binaries/platforms \
  windows_binaries/translations \
  scripts/gitlab-ci/windows/nbinit.config \
  client_distribution/win64/

mkdir client_distribution/osx
cp -LR scripts/gitlab-ci/macos/Newborn.app client_distribution/osx/
mkdir client_distribution/osx/Newborn.app/Contents/MacOS
cp macos_binaries/newborn client_distribution/osx/Newborn.app/Contents/MacOS/
cp macos_binaries/*.dylib client_distribution/osx/Newborn.app/Contents/MacOS/
cp \
  macos_binaries/newborn_server \
  macos_binaries/asset_packer \
  macos_binaries/asset_unpacker \
  macos_binaries/dump_versioned_json \
  macos_binaries/make_versioned_json \
  macos_binaries/planet_mapgen \
  scripts/gitlab-ci/macos/nbinit.config \
  scripts/gitlab-ci/macos/run-server.sh \
  client_distribution/osx/

mkdir client_distribution/linux
cp \
  linux_binaries/newborn \
  linux_binaries/newborn_server \
  linux_binaries/asset_packer \
  linux_binaries/asset_unpacker \
  linux_binaries/dump_versioned_json \
  linux_binaries/make_versioned_json \
  linux_binaries/planet_mapgen \
  linux_binaries/*.so \
  scripts/gitlab-ci/linux/nbinit.config \
  scripts/gitlab-ci/linux/run-client.sh \
  scripts/gitlab-ci/linux/run-server.sh \
  client_distribution/linux/

mkdir server_distribution
mkdir server_distribution/assets

mkdir server_distribution/mods
touch server_distribution/mods/mods_go_here

./linux_binaries/asset_packer -c scripts/packing.config -s assets/packed server_distribution/assets/packed.pak

mkdir server_distribution/win64
mkdir server_distribution/linux

cp \
  linux_binaries/newborn_server \
  linux_binaries/*.so \
  scripts/gitlab-ci/linux/run-server.sh \
  scripts/gitlab-ci/linux/nbinit.config \
  server_distribution/linux/

cp \
  windows_binaries/newborn_server.exe \
  windows_binaries/*.dll \
  scripts/gitlab-ci/windows/nbinit.config \
  server_distribution/win64/
