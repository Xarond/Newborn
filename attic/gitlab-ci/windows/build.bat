set QT_PREFIX_PATH="C:\Qt\5.7\msvc2015_64"
set CMAKE_PREFIX_PATH="C:\Program Files\CMake"
set PATH=%PATH%;%CMAKE_PREFIX_PATH%\bin;%QT_PREFIX_PATH%\bin

mkdir build
cd build || exit /b 1

del /f CMakeCache.txt

cmake.exe ^
  -G"Visual Studio 17 2022" ^
  -T"v143" ^
  -DCMAKE_PREFIX_PATH=%QT_PREFIX_PATH% ^
  -DNEWBORN_USE_JEMALLOC=OFF ^
  -DNEWBORN_ENABLE_STEAM_INTEGRATION=ON ^
  -DNEWBORN_ENABLE_DISCORD_INTEGRATION=ON ^
  -DNEWBORN_BUILD_QT_TOOLS=OFF ^
  -DCMAKE_INCLUDE_PATH="..\lib\windows\include" ^
  -DCMAKE_LIBRARY_PATH="..\lib\windows" ^
  ..\source || exit /b 1

cmake.exe --build . --config RelWithDebInfo || exit /b 1

cd ..

move dist windows_binaries || exit /b 1

if exist windows_binaries\mod_uploader.exe (
  windeployqt.exe windows_binaries\mod_uploader.exe || exit /b 1
)

copy lib\windows\*.dll windows_binaries\ || exit /b 1
