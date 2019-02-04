@echo off

echo "Copyright 2018 Vladimir Balun - Script to build game on Windows for Visual Studio 2017."

cd ../ClientSide
rmdir /S /Q Build
mkdir Build
cd Build
cmake -G "Visual Studio 15 2017" ..
