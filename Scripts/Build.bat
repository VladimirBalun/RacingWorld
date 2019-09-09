@echo off

set CURRENT_PATH=%cd%
set CLIENT_SIDE_PATH=%CURRENT_PATH%\..\ClientSide

echo Copyright 2018 Vladimir Balun - Script to build game on Windows for Visual Studio 2017.

cmake --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Error: CMake is not installed.
  exit 1
) 

cd %CLIENT_SIDE_PATH%
rmdir /S /Q Build
mkdir Build
cd Build
cmake -G "Visual Studio 15 2017" ..