@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameserver

echo Copyright 2018 Vladimir Balun - Script to run game server on Windows."

java -version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Error: Java is not installed.
  exit 1
) 

if not exist %GAME_SERVER_PATH%\target\GameServer.jar (
  echo Error: game server is absent. Please build it and repeat.
  exit 2
) 

java -jar %GAME_SERVER_PATH%\target\GameServer.jar