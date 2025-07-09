cd windows_binaries

set PATH="%PATH%;..\lib\windows"

copy ..\scripts\windows\nbinit.config .

.\core_tests || exit /b 1
.\game_tests || exit /b 1
