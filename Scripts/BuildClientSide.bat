@echo off

set CURRENT_PATH=%cd%
set CLIENT_SIDE_PATH=%CURRENT_PATH%\..\ClientSide

echo "Copyright 2018 Vladimir Balun - Script to build game on Windows for Visual Studio 2017."

cd %CLIENT_SIDE_PATH%
rmdir /S /Q Build
mkdir Build
cd Build
cmake -G "Visual Studio 15 2017" ..
