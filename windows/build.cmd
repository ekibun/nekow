@echo off

cd /d %~dp0
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
set BUILD_DIR="build"
cmake -DRUNTIME_OUTPUT_DIRECTORY=bin -B "%BUILD_DIR%" -S "."
cmake --build "%BUILD_DIR%" --verbose %*