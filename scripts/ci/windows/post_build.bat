@echo off

for %%f in (lib\windows\*.dll) do (
    xcopy "%%f" "dist\" /Y
)

for %%f in (dist\*.pdb) do (
    echo %%f | find "newborn" > nul || del %%f
)
