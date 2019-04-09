@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameserver
set RESOURCE_SERVER_PATH=%SERVER_SIDE_PATH%\resourceserver
set DATABASE_SERVER_PATH=%SERVER_SIDE_PATH%\databaseserver

echo Copyright 2018 Vladimir Balun - Script to run all the servers on Windows.

java -version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
  echo Error: Java is not installed.
  exit 1
) 

if not exist %DATABASE_SERVER_PATH%\target\DatabaseServer.jar (
  echo Error: database server is absent. Please build it and repeat.
  exit 2
) 

start java -jar %DATABASE_SERVER_PATH%\target\DatabaseServer.jar

if not exist %GAME_SERVER_PATH%\target\GameServer.jar (
  echo Error: game server is absent. Please build it and repeat.
  exit 2
) 

start java -jar %GAME_SERVER_PATH%\target\GameServer.jar

if not exist %RESOURCE_SERVER_PATH%\target\ResourceServer.jar (
  echo Error: resource server is absent. Please build it and repeat.
  exit 2
) 

start java -jar %RESOURCE_SERVER_PATH%\target\ResourceServer.jar