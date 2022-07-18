@echo off

set CompilerFlags=-Od -MTd -nologo  -fp:except- -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7
set LinkerFlags=-incremental:no -opt:ref -subsystem:windows shell32.lib user32.lib gdi32.lib winmm.lib

IF NOT EXIST build mkdir build
pushd build
cl %CompilerFlags% /Fe:application.exe ..\windows.cpp  /link %LinkerFlags%  
popd
