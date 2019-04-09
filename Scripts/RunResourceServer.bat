@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set RESOURCE_SERVER_PATH=%SERVER_SIDE_PATH%\resourceserver

echo Copyright 2018 Vladimir Balun - Script to run resource server on Windows."

java -version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Error: Java is not installed.
  exit 1
) 

if not exist %RESOURCE_SERVER_PATH%\target\ResourceServer.jar (
  echo Error: resource server is absent. Please build it and repeat.
  exit 2
) 

java -jar %RESOURCE_SERVER_PATH%\target\ResourceServer.jar