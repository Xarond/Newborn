<div align="center">

# Newborn

**An open-source, modding-focused 2D sandbox game engine written in C++.**

Newborn builds a full game **client** and a standalone **dedicated server** from
a single codebase, plus a suite of command-line tools for working with assets
and worlds.

[![Build](https://github.com/Xarond/Newborn/actions/workflows/build.yml/badge.svg)](https://github.com/Xarond/Newborn/actions/workflows/build.yml)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)
![Language](https://img.shields.io/badge/language-C%2B%2B-00599C)

</div>

> [!IMPORTANT]
> Newborn is **work-in-progress**. Base game assets are **not** included — you
> need an installed copy of the base game to actually play.

---

## Contents

- [About the game](#about-the-game)
- [Features](#features)
- [Quick start](#quick-start)
- [Building](#building)
- [Running](#running)
- [Repository layout](#repository-layout)
- [Tools](#tools)
- [License](#license)

## About the game

Newborn is an open-ended, sci-fi sandbox adventure. You begin adrift in space
with a ship of your own and an entire **procedurally generated universe** to
explore — star systems full of planets, moons and asteroid fields, each with its
own biomes, gravity, weather and threats.

There's no single way to play:

- **Explore** thousands of unique worlds, from lush surfaces down to glowing
  underground layers and the planet core.
- **Mine & gather** resources, then **craft** tools, weapons, armor and
  furniture from them.
- **Build** anything you like, block by block — bases, ships, sky castles —
  and attract **NPC tenants** to settle your colonies.
- **Fight** procedurally generated monsters, bosses and hostile NPCs, and
  unlock **tech** that changes how you move and survive.
- **Farm**, cook and manage **hunger** as you survive harsher worlds.
- Follow **quests**, collect **codex** lore, play music, and customize a
  character from several playable **species**.
- Play **solo** or together on a shared universe via the dedicated server.

> The engine is content-driven: nearly everything above — worlds, items,
> monsters, dungeons, quests — is defined in JSON assets and Lua scripts, so it
> is **highly moddable**.

## Features

- Native **client** and **dedicated server** built from one C++ codebase.
- Cross-platform: **Windows**, **Linux** and **macOS** (x86_64 & Apple Silicon).
- Extensive **Lua scripting** bindings for mods — rendering, world, universe
  server, widgets, players and more.
- Optional **Steam** and **Discord** integration.
- A full suite of **asset & world tools**: packing, unpacking, conversion,
  map inspection and generation benchmarks.

## Quick start

```bash
# 1. Make sure VCPKG_ROOT points at your vcpkg checkout
export VCPKG_ROOT=/path/to/vcpkg

# 2. Configure + build (pick your platform preset)
cmake --preset linux-release
cmake --build --preset linux-release

# 3. Point dist/nbinit.config at your assets, then launch
./dist/newborn          # client
./dist/newborn_server   # dedicated server
```

> Requires **CMake ≥ 3.23**, **Ninja** and **vcpkg**. See [Building](#building)
> for per-platform details.

## Building

Newborn uses **CMake**, **Ninja** and **vcpkg** for dependency management. The
dependencies declared in [`source/vcpkg.json`](source/vcpkg.json) — GLEW, SDL2,
libvorbis, zlib, freetype, libpng, opus, zstd and mimalloc — are fetched
automatically by vcpkg. Just make sure `VCPKG_ROOT` is set, then use one of the
provided presets ([`source/CMakePresets.json`](source/CMakePresets.json)).

<details>
<summary><b>Windows (MSVC 2022)</b></summary>

```powershell
cmake --preset windows-release
cmake --build --preset windows-release
```

A Visual Studio helper is also available:

```bat
scripts\windows\setup.bat
scripts\windows\build.bat RelWithDebInfo
```

</details>

<details>
<summary><b>Linux (Clang)</b></summary>

```bash
sudo apt-get install -y pkg-config libxmu-dev libxi-dev libgl-dev \
  libglu1-mesa-dev libsdl2-dev python3-jinja2

cmake --preset linux-release
cmake --build --preset linux-release
```

</details>

<details>
<summary><b>macOS</b></summary>

```bash
brew install autoconf automake libtool

# Intel
cmake --preset macos-release && cmake --build --preset macos-release

# Apple Silicon
cmake --preset macos-arm-release && cmake --build --preset macos-arm-release
```

</details>

Build artifacts (client, server and tools) are placed in `dist/`.

#### Build options

A few notable CMake options (see [`source/CMakeLists.txt`](source/CMakeLists.txt)):

| Option                                | Default | Description                |
| ------------------------------------- | :-----: | -------------------------- |
| `NEWBORN_ENABLE_STEAM_INTEGRATION`    |  `ON`   | Build with Steam support   |
| `NEWBORN_ENABLE_DISCORD_INTEGRATION`  |  `ON`   | Build with Discord support |
| `BUILD_TESTING`                       |  `ON`   | Build the test suites      |

## Running

Newborn does **not** ship the base game — you supply the base game assets.

1. Point Newborn at your asset directories. The default startup configuration
   ([`scripts/windows/nbinit.config`](scripts/windows/nbinit.config) /
   [`scripts/linux/nbinit.config`](scripts/linux/nbinit.config)) lists the
   `assetDirectories` (e.g. `../assets/` and `./mods/`) and the
   `storageDirectory` used for player and world saves.
2. Launch `newborn` (client) or `newborn_server` (dedicated server) from `dist/`.

## Repository layout

| Path        | Description                                                  |
| ----------- | ------------------------------------------------------------ |
| `source/`   | Engine source code (see modules below)                       |
| `assets/`   | Newborn's own assets and bundled mods (no base game assets)  |
| `cmake/`    | CMake `Find*` modules and helpers                            |
| `lib/`      | Prebuilt platform libraries (Steam SDK, Discord SDK, …)      |
| `scripts/`  | Build, packaging, CI and developer helper scripts            |
| `triplets/` | Custom vcpkg triplets                                        |
| `dist/`     | Build output — git-ignored                                   |

<details>
<summary><b>Source modules (<code>source/</code>)</b></summary>

| Module        | Responsibility                                              |
| ------------- | ----------------------------------------------------------- |
| `core`        | Foundations: containers, math, JSON, I/O, networking, Lua   |
| `base`        | Assets, configuration, lighting, world storage              |
| `game`        | Game logic: world, entities, items, AI, generation          |
| `rendering`   | Tile, drawable, text and environment painters               |
| `windowing`   | GUI widgets and layout                                       |
| `frontend`    | In-game interfaces (inventory, char creation, menus, …)     |
| `client`      | Client application entry point                              |
| `server`      | Dedicated server (RCON, query thread, …)                    |
| `application` | Platform/application layer, renderer, audio, P2P            |
| `platform`    | Platform service abstractions (Steam, Discord, …)           |
| `utility`     | Standalone command-line tools                                |
| `test`        | Unit and integration tests                                   |

</details>

## Tools

The `utility` module builds a number of standalone tools (output to `dist/`):

| Tool                                   | Purpose                                      |
| -------------------------------------- | -------------------------------------------- |
| `asset_packer` / `asset_unpacker`      | Pack and unpack `.pak` asset bundles         |
| `btree_repacker`                       | Repack BTree databases (worlds, player files)|
| `dump_versioned_json` / `make_versioned_json` | Versioned JSON conversion             |
| `planet_mapgen`                        | World/planet generation                      |
| `generation_benchmark` / `dungeon_generation_benchmark` | Generation benchmarks       |
| `map_grep`                             | Search world data                            |
| `game_repl`                            | Interactive Lua/game REPL                    |

## License

Newborn is licensed under the **GNU General Public License v3.0**.
See [LICENSE](LICENSE) for the full text.
