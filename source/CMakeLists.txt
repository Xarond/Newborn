cmake_minimum_required(VERSION 3.23)

# Find SCCache or CCache
if (NOT CMAKE_CXX_COMPILER_LAUNCHER MATCHES "ccache")
  find_program(SCCACHE_PATH sccache)
  if(SCCACHE_PATH)
    message(STATUS "Using SCCache at ${SCCACHE_PATH}")
    set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE_PATH})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE_PATH})
  else()
    find_program(CCACHE_PATH ccache)
    if(CCACHE_PATH)
      set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PATH}")
      set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PATH}")
      message(STATUS "Using CCache")
    endif()
  endif()
endif()

if(CMAKE_CXX_COMPILER_LAUNCHER MATCHES "ccache")
  set(NEWBORN_CCACHE TRUE)
  set(NEWBORN_PRECOMPILED_HEADERS FALSE)
else()
  set(NEWBORN_CCACHE FALSE)
  set(NEWBORN_PRECOMPILED_HEADERS TRUE)
  message(STATUS "Not using CCache")
endif()

project(newborn)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

set(CMAKE_CONFIGURATION_TYPES Debug RelWithAsserts RelWithDebInfo Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS_RELWITHASSERTS "" CACHE STRING "" FORCE)

#include(CheckIPOSupported)
#check_ipo_supported(RESULT lto_supported OUTPUT lto_output)
#if(lto_supported)
#  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
#endif()

# Update the docstring on CMAKE_BUILD_TYPE to show what options we actually
# allow
# SET (CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Choose the type of build, options are: Debug RelWithAsserts RelWithDebInfo Release" FORCE)

# Discover all the relevant environment / system information and place the
# result in NEWBORN_* cmake variables.

# NEWBORN_SOURCE_IDENTIFIER may be set to any string value
if(NOT DEFINED NEWBORN_SOURCE_IDENTIFIER)
  include(GetGitRevisionDescription)
  get_git_head_revision(NEWBORN_GIT_REFSPEC NEWBORN_GIT_HASHVAR)
  set(NEWBORN_SOURCE_IDENTIFIER "${NEWBORN_GIT_HASHVAR}")
endif()

# Architecture identifier, like i386, x86_64 or ppc
if(NOT DEFINED NEWBORN_ARCHITECTURE)
  include(TargetArch)
  target_architecture(NEWBORN_ARCHITECTURE)
endif()

# Either TRUE or FALSE
if(NOT DEFINED NEWBORN_LITTLE_ENDIAN)
  include(TestBigEndian)
  test_big_endian(BIGENDIAN)
  if(NOT BIGENDIAN)
    set(NEWBORN_LITTLE_ENDIAN TRUE)
  else()
    set(NEWBORN_LITTLE_ENDIAN FALSE)
  endif()
endif()

# System name, like windows, macos, linux, freebsd, or (generic) unix
if(NOT DEFINED NEWBORN_SYSTEM)
  if(WIN32)
    set(NEWBORN_SYSTEM "windows")
  elseif(APPLE AND ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(NEWBORN_SYSTEM "macos")
  elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(NEWBORN_SYSTEM "linux")
  elseif(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    set(NEWBORN_SYSTEM "freebsd")
  elseif(${CMAKE_SYSTEM_NAME} STREQUAL "NetBSD")
    set(NEWBORN_SYSTEM "netbsd")
  elseif(UNIX)
    set(NEWBORN_SYSTEM "unix")
  else()
    set(NEWBORN_SYSTEM "unknown")
  endif()
endif()

if(NOT DEFINED NEWBORN_SYSTEM_FAMILY)
  if(WIN32)
    set(NEWBORN_SYSTEM_FAMILY "windows")
  elseif(UNIX)
    set(NEWBORN_SYSTEM_FAMILY "unix")
  else()
    set(NEWBORN_SYSTEM_FAMILY "unknown")
  endif()
endif()

# C/C++ compiler ID, like clang, gnu, or msvc
if(NOT DEFINED NEWBORN_COMPILER)
  if(NOT CMAKE_C_COMPILER_ID STREQUAL CMAKE_CXX_COMPILER_ID)
    message(FATAL_ERROR "C and C++ compiler id do not match, unsupported build configuration")
  endif()

  if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(NEWBORN_COMPILER "clang")
  elseif(CMAKE_COMPILER_IS_GNUC)
    set(NEWBORN_COMPILER "gnu")
  elseif(MSVC)
    set(NEWBORN_COMPILER "msvc")
  else()
    string(TOLOWER "${CMAKE_C_COMPILER_ID}" NEWBORN_COMPILER)
  endif()
endif()

# Enable OPTIONs based on the discovered system / environment...

if(NEWBORN_COMPILER STREQUAL "gnu")
  option(NEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX "Statically link libgcc and libstdc++" OFF)
  option(NEWBORN_ENABLE_GCC_PROFILING "Enable gcc/g++ profiling via the -pg flag" OFF)
  option(NEWBORN_ENABLE_GLIBCXX_DEBUG "Enable _GLIBCXX_DEBUG for g++" OFF)
endif()

if(NEWBORN_COMPILER STREQUAL "msvc")
  option(NEWBORN_ENABLE_STATIC_MSVC_RUNTIME "Statically link with the CRT" OFF)
endif()

option(NEWBORN_BUILD_GUI "Build GUI utilities and Client" ON)

if(NEWBORN_BUILD_GUI)
  option(NEWBORN_BUILD_QT_TOOLS "Build GUI utilities that require Qt" OFF)
  option(NEWBORN_ENABLE_STEAM_INTEGRATION "Use Steam platform services" OFF)
  option(NEWBORN_ENABLE_DISCORD_INTEGRATION "Use Discord platform services" OFF)
endif()

option(NEWBORN_LUA_APICHECK "Use lua api checks" OFF)
option(NEWBORN_USE_JEMALLOC "Use jemalloc allocators" OFF)
option(NEWBORN_USE_MIMALLOC "Use mimalloc allocators" OFF)
option(NEWBORN_USE_RPMALLOC "Use rpmalloc allocators" OFF)

# Report all the discovered system / environment settings and all options.

message(STATUS "Source ID: ${NEWBORN_SOURCE_IDENTIFIER}")
message(STATUS "Architecture: ${NEWBORN_ARCHITECTURE}")
message(STATUS "Little Endian: ${NEWBORN_LITTLE_ENDIAN}")
message(STATUS "System: ${NEWBORN_SYSTEM}")
message(STATUS "System family: ${NEWBORN_SYSTEM_FAMILY}")
message(STATUS "C/C++ compiler: ${NEWBORN_COMPILER}")

if(DEFINED NEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX)
  message(STATUS "Statically linking to libgcc / libstdc++: ${NEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX}")
endif()

if(DEFINED NEWBORN_ENABLE_STATIC_MSVC_RUNTIME)
  message(STATUS "Statically linking to CRT: ${NEWBORN_ENABLE_STATIC_MSVC_RUNTIME}")
endif()

if(DEFINED NEWBORN_ENABLE_GLIBCXX_DEBUG)
  message(STATUS "Enabling _GLIBCXX_DEBUG: ${NEWBORN_ENABLE_GLIBCXX_DEBUG}")
endif()

message(STATUS "Building GUI: ${NEWBORN_BUILD_GUI}")

if(DEFINED NEWBORN_BUILD_QT_TOOLS)
  message(STATUS "Building Qt tools: ${NEWBORN_BUILD_QT_TOOLS}")
endif()

if(DEFINED NEWBORN_ENABLE_STEAM_INTEGRATION)
  message(STATUS "Using Steam platform services: ${NEWBORN_ENABLE_STEAM_INTEGRATION}")
endif()

if(DEFINED NEWBORN_ENABLE_DISCORD_INTEGRATION)
  message(STATUS "Using Discord platform services: ${NEWBORN_ENABLE_DISCORD_INTEGRATION}")
endif()

message(STATUS "Using Lua API checks: ${NEWBORN_LUA_APICHECK}")
message(STATUS "Using jemalloc: ${NEWBORN_USE_JEMALLOC}")
message(STATUS "Using mimalloc: ${NEWBORN_USE_MIMALLOC}")
message(STATUS "Using rpmalloc: ${NEWBORN_USE_RPMALLOC}")

# Set C defines and cmake variables based on the build settings we have now
# determined...

# Set a cmake variable to true and define a corresponding C/C++ definition
function(SET_FLAG flagValue)
  set(${flagValue} TRUE PARENT_SCOPE)
  add_definitions(-D${flagValue})
endfunction()

if(NEWBORN_LITTLE_ENDIAN)
  set_flag(NEWBORN_LITTLE_ENDIAN)
elseif()
  set_flag(NEWBORN_BIG_ENDIAN)
endif()

if(NEWBORN_ARCHITECTURE STREQUAL "i386")
  set_flag(NEWBORN_ARCHITECTURE_I386)
elseif(NEWBORN_ARCHITECTURE STREQUAL "x86_64")
  set_flag(NEWBORN_ARCHITECTURE_X86_64)
endif()

if(NEWBORN_SYSTEM STREQUAL "windows")
  set_flag(NEWBORN_SYSTEM_WINDOWS)
elseif(NEWBORN_SYSTEM STREQUAL "macos")
  set_flag(NEWBORN_SYSTEM_MACOS)
elseif(NEWBORN_SYSTEM STREQUAL "linux")
  set_flag(NEWBORN_SYSTEM_LINUX)
elseif(NEWBORN_SYSTEM STREQUAL "freebsd")
  set_flag(NEWBORN_SYSTEM_FREEBSD)
elseif(NEWBORN_SYSTEM STREQUAL "netbsd")
  set_flag(NEWBORN_SYSTEM_NETBSD)
endif()

if(NEWBORN_SYSTEM_FAMILY STREQUAL "windows")
  set_flag(NEWBORN_SYSTEM_FAMILY_WINDOWS)
elseif(NEWBORN_SYSTEM_FAMILY STREQUAL "unix")
  set_flag(NEWBORN_SYSTEM_FAMILY_UNIX)
endif()

if(NEWBORN_COMPILER STREQUAL "gnu")
  set_flag(NEWBORN_COMPILER_GNU)
elseif(NEWBORN_COMPILER STREQUAL "clang")
  set_flag(NEWBORN_COMPILER_CLANG)
elseif(NEWBORN_COMPILER STREQUAL "msvc")
  set_flag(NEWBORN_COMPILER_MSVC)
endif()

if(NEWBORN_LUA_APICHECK)
  add_definitions(-DLUA_USE_APICHECK)
endif()

if(NEWBORN_SYSTEM_WINDOWS)
  # LUA_USE_WINDOWS is automatically defined in luaconf if _WIN32 is defined
elseif(NEWBORN_SYSTEM_MACOS)
  add_definitions(-DLUA_USE_MACOSX)
elseif(NEWBORN_SYSTEM_LINUX)
  add_definitions(-DLUA_USE_LINUX)
elseif(NEWBORN_SYSTEM_FAMILY_UNIX)
  add_definitions(-DLUA_USE_POSIX)
endif()

if(NEWBORN_ENABLE_STEAM_INTEGRATION)
  add_definitions(-DNEWBORN_ENABLE_STEAM_INTEGRATION)
endif()

if(NEWBORN_ENABLE_DISCORD_INTEGRATION)
  add_definitions(-DNEWBORN_ENABLE_DISCORD_INTEGRATION)
endif()

if(NEWBORN_USE_JEMALLOC)
  add_definitions(-DNEWBORN_USE_JEMALLOC)
elseif(NEWBORN_USE_MIMALLOC)
  add_definitions(-DNEWBORN_USE_MIMALLOC)
elseif(NEWBORN_USE_RPMALLOC)
  add_definitions(-DNEWBORN_USE_RPMALLOC -DENABLE_PRELOAD)
endif()

# Set C/C++ compiler flags based on build environment...

if(NEWBORN_COMPILER_GNU)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic -Wall -Wextra -Wno-unused -Wno-implicit-fallthrough -no-pie")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -rdynamic -Wall -Wextra -Wno-unused -Wno-implicit-fallthrough -no-pie")

  if(NEWBORN_SYSTEM_FAMILY_WINDOWS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthreads")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -D_REENTRANT")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -D_REENTRANT")
  endif()

  if(NEWBORN_ENABLE_STATIC_LIBGCC_LIBSTDCXX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
  endif()

  if(NEWBORN_ENABLE_GCC_PROFILING)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
  endif()

  set(CMAKE_C_FLAGS_DEBUG "-g -Og")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")

  set(CMAKE_C_FLAGS_RELWITHASSERTS "-g -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELWITHASSERTS "-g -O3 -ffast-math")

  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -DNDEBUG -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -DNDEBUG -O3 -ffast-math")

  set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -ffast-math")

  set(CMAKE_SKIP_BUILD_RPATH TRUE)

elseif(NEWBORN_COMPILER_CLANG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wuninitialized -Wno-parentheses-equality -Wno-deprecated-declarations -Wno-nan-infinity-disabled")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wuninitialized -Wno-parentheses-equality -Wno-deprecated-declarations -Wno-nan-infinity-disabled")

  if(NEWBORN_SYSTEM_MACOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-export_dynamic")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-export_dynamic")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
  elseif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -D_REENTRANT")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -D_REENTRANT")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export_dynamic")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--export_dynamic")
  endif()

  set(CMAKE_C_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")

  set(CMAKE_C_FLAGS_RELWITHASSERTS "-g -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELWITHASSERTS "-g -O3 -ffast-math")

  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-gline-tables-only -DNDEBUG -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-gline-tables-only -DNDEBUG -O3 -ffast-math")

  set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3 -ffast-math")
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -ffast-math")

  set(CMAKE_SKIP_BUILD_RPATH TRUE)

elseif(NEWBORN_COMPILER_MSVC)
  # /MP      - Multi-processor building
  # /EHsc    - Enable normal C++ exception handling
  # /bigobj  - More sections in .obj files (Cannot build in Debug without it)
  # /MT      - Use multi-threaded statically linked C runtime library
  # /GA      - Optimize for windows application
  # /Ox      - Full optimization
  # /fp:fast - Equivalent to -ffast-math
  # /GS-     - Disable buffers security check
  # /Zi      - Generates debugging information without Edit and Continue
  # /Z7      - Like the above, but debugging information is stored per-object
  # /Gy      - Use function-level linking
  # /wd4996  - Disable warnings about unsafe C functions
  # /wd4351  - Disable warnings about new behavior of default initialization of
  #            arrays (which is the correct behavior anyway)
  # /wd4800  - Disable warnings about using non-bool as true or false (useless
  #            performance warning)
  # /wd4244  - Disable warnings about type conversion loss of data, it's a nice
  #            warning, but it triggers on lots and lots of harmless things that no
  #            other compiler warns about, like passing an int as a float parameter
  # /wd4305  - Disable warnings about truncation from double to float
  # /wd4267  - Disable warnings about 64 - 32 bit truncation
  # /wd4456  - Disable warnings about hiding previous local declaration
  # /wd4503  - Silence warnings about MSVC generating a name so long it has to
  #            truncate it
  # /wd4250  - Silence "XX inherits YY via dominance"
  # /wd4624  - Silence implicitly deleted destructor warnings that show up when
  #            using unions in interesting ways.

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /nologo /MP /EHsc /bigobj /wd4996 /wd4351 /wd4800 /wd4244 /wd4305 /wd4267 /wd4456 /wd4503 /wd4250 /wd4624")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /std:c++17 /MP /EHsc /bigobj /wd4996 /wd4351 /wd4800 /wd4244 /wd4305 /wd4267 /wd4456 /wd4503 /wd4250 /wd4624")

  if(NEWBORN_ENABLE_STATIC_MSVC_RUNTIME)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
  endif()

  set(CMAKE_C_FLAGS_DEBUG "/Z7 /Od")
  set(CMAKE_CXX_FLAGS_DEBUG "/Z7 /Od")

  set(CMAKE_C_FLAGS_RELWITHASSERTS "/Ox /fp:fast /GA /GS- /Z7 /Gy")
  set(CMAKE_CXX_FLAGS_RELWITHASSERTS "/Ox /fp:fast /GA /GS- /Z7 /Gy")

  set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Ox /fp:fast /GA /GS- /Z7 /Gy /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Ox /fp:fast /GA /GS- /Z7 /Gy /DNDEBUG")

  set(CMAKE_C_FLAGS_RELEASE "/Ox /fp:fast /GA /GS- /Gy /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/Ox /fp:fast /GA /GS- /Gy /DNDEBUG")

  if(NEWBORN_ARCHITECTURE_I386)
    # Assume all 32 bit target cpus support MMX, SSE, and SSE2

    set(CMAKE_C_FLAGS_RELWITHASSERTS "${CMAKE_C_FLAGS_RELWITHASSERTS} /arch:SSE2")
    set(CMAKE_CXX_FLAGS_RELWITHASSERTS "${CMAKE_CXX_FLAGS_RELWITHASSERTS} /arch:SSE2")

    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /arch:SSE2")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /arch:SSE2")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /arch:SSE2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /arch:SSE2")
  endif()

  add_definitions(/DUNICODE)
  add_definitions(/D_UNICODE)
  add_definitions(/DNOMINMAX)

else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread -D_REENTRANT")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread -D_REENTRANT")

  set(CMAKE_C_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")

  set(CMAKE_C_FLAGS_RELWITHASSERTS "-g -O2")
  set(CMAKE_CXX_FLAGS_RELWITHASSERTS "-g -O2")

  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-DNDEBUG -g -O2")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -g -O2")

  set(CMAKE_C_FLAGS_RELEASE "$-DNDEBUG -O2")
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

endif()

# Set other global build settings based on environment...

if(NEWBORN_SYSTEM_MACOS)
  set(CMAKE_MODULE_LINKER_FLAGS "-flat_namespace -undefined suppress")
elseif(NEWBORN_SYSTEM_WINDOWS)
  set(CMAKE_RC_COMPILER_INIT windres)

  enable_language(RC)
  if(NEWBORN_COMPILER STREQUAL "msvc")
    set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> /fo <OBJECT> <SOURCE>")
  else()
    set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
  endif()
endif()

if(NEWBORN_COMPILER STREQUAL "msvc")
  # /largeaddressaware - Make 32 bit build able to use 3GB addresses
  # /OPT:REF           - Eliminates functions and data that are never referenced
  # /OPT:ICF           - Performs identical COMDAT folding
  # /PDBCompress       - Hint to windows that it should compress the resulting PDB files
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /largeaddressaware /OPT:REF /OPT:ICF /PDBCompress")

  # Make sure RelWithAsserts has debugging enabled
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHASSERTS "${CMAKE_EXE_LINKER_FLAGS_RELWITHASSERTS} /DEBUG")
endif()

if(NEWBORN_SYSTEM_WINDOWS)
  set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} ws2_32.lib iphlpapi.lib shlwapi.lib dbghelp.lib")
  set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} ws2_32.lib iphlpapi.lib shlwapi.lib dbghelp.lib")

elseif(NEWBORN_SYSTEM_LINUX)
  set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lpthread -ldl -lrt")
  set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lpthread -ldl -lrt")

elseif(NEWBORN_SYSTEM_FREEBSD)
  set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lpthread -lrt")
  set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lpthread -lrt")

elseif(NEWBORN_SYSTEM_NETBSD)
  set(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} -lpthread -lrt -lexecinfo")
  set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lpthread -lrt -lexecinfo")

endif()

# Find all required external libraries, based on build settings...

if(NEWBORN_USE_JEMALLOC)
  # Assumes jemalloc was configured with a "je_" function prefix
  find_package(JeMalloc REQUIRED)

  include_directories(SYSTEM ${JEMALLOC_INCLUDE_DIR})
  set(NEWBORN_EXT_LIBS ${JEMALLOC_LIBRARY})
endif()

if (NEWBORN_USE_MIMALLOC)
  find_package(mimalloc CONFIG REQUIRED)
  set(NEWBORN_EXT_LIBS ${NEWBORN_EXT_LIBS} $<IF:$<TARGET_EXISTS:mimalloc-static>,mimalloc-static,mimalloc>)
endif()

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
find_package(Opus CONFIG REQUIRED)
find_package(OggVorbis REQUIRED)
find_package(zstd CONFIG REQUIRED)

include_directories(SYSTEM
    ${FREETYPE_INCLUDE_DIRS}
    ${OGGVORBIS_INCLUDE_DIR}
)

set(NEWBORN_EXT_LIBS ${NEWBORN_EXT_LIBS}
    ZLIB::ZLIB
    PNG::PNG
    $<IF:$<TARGET_EXISTS:Freetype::Freetype>,Freetype::Freetype,freetype>
    $<IF:$<TARGET_EXISTS:zstd::libzstd_shared>,zstd::libzstd_shared,zstd::libzstd_static>
    Opus::opus
    ${VORBISFILE_LIBRARY}
    ${VORBIS_LIBRARY}
    ${OGG_LIBRARY}
)

if(NEWBORN_BUILD_GUI)
  find_package(SDL2 CONFIG REQUIRED)

  set(NEWBORN_EXT_GUI_LIBS
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  )

  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)

  include_directories(SYSTEM ${GLEW_INCLUDE_DIR})
  set(NEWBORN_EXT_GUI_LIBS ${NEWBORN_EXT_GUI_LIBS}
      ${OPENGL_LIBRARY}
      GLEW::glew_s
  )

  if(NEWBORN_SYSTEM_MACOS)
    set(NEWBORN_EXT_GUI_LIBS ${NEWBORN_EXT_GUI_LIBS} "-framework CoreAudio")
  endif()

  if(NEWBORN_ENABLE_STEAM_INTEGRATION)
    find_package(SteamApi REQUIRED)
    include_directories(SYSTEM ${STEAM_API_INCLUDE_DIR})
    set(NEWBORN_EXT_GUI_LIBS ${NEWBORN_EXT_GUI_LIBS} ${STEAM_API_LIBRARY})
  endif()

  if(NEWBORN_ENABLE_DISCORD_INTEGRATION)
    find_package(DiscordApi REQUIRED)
    set(NEWBORN_EXT_GUI_LIBS ${NEWBORN_EXT_GUI_LIBS} ${DISCORD_API_LIBRARY})
  endif()
endif()

# Set basic build flags, include all the relevant source directories, based on
# build settings...

set(BUILD_SHARED_LIBS false)

# First set output dir for the generic no-config case (e.g. macos / linux)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../dist)

# Second, set output dir for multi-config builds (e.g. msvc)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/../dist)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# External code included with newborn source, which core depends on
set(NEWBORN_EXTERN_INCLUDES ${PROJECT_SOURCE_DIR}/extern)
add_subdirectory(extern)

# Core support code, not specific to newborn.
set(NEWBORN_CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/core/scripting
)
add_subdirectory(core)

# Less general purpose code than core that is available to both the game and
# application modules.
set(NEWBORN_BASE_INCLUDES
    ${PROJECT_SOURCE_DIR}/base
    ${PROJECT_SOURCE_DIR}/base/scripting
)
add_subdirectory(base)

# Platform APIs that are implemented by the application module
set(NEWBORN_PLATFORM_INCLUDES ${PROJECT_SOURCE_DIR}/platform)
add_subdirectory(platform)

# Core game logic used by both server and client.
set(NEWBORN_GAME_INCLUDES
    ${PROJECT_SOURCE_DIR}/game
    ${PROJECT_SOURCE_DIR}/game/interfaces
    ${PROJECT_SOURCE_DIR}/game/items
    ${PROJECT_SOURCE_DIR}/game/objects
    ${PROJECT_SOURCE_DIR}/game/scripting
    ${PROJECT_SOURCE_DIR}/game/terrain
  )
add_subdirectory(game)

# Googletest based tests
option(BUILD_TESTING "Build test projects" OFF)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# Newborn stand-alone server.
add_subdirectory(server)

# cmdline utilities
add_subdirectory(utility)

if(NEWBORN_BUILD_GUI)
  # Handles creating windows, keyboard / mouse / joystick input, and the 2d
  # rendering model.
  set(NEWBORN_APPLICATION_INCLUDES ${PROJECT_SOURCE_DIR}/application)
  add_subdirectory(application)

  # Rendering code not dependent on widget system
  set(NEWBORN_RENDERING_INCLUDES ${PROJECT_SOURCE_DIR}/rendering)
  add_subdirectory(rendering)

  # Panes and Widgets
  set(NEWBORN_WINDOWING_INCLUDES ${PROJECT_SOURCE_DIR}/windowing)
  add_subdirectory(windowing)

  # Client interface code
  set(NEWBORN_FRONTEND_INCLUDES ${PROJECT_SOURCE_DIR}/frontend)
  add_subdirectory(frontend)

  # Newborn game / client
  add_subdirectory(client)

endif()
