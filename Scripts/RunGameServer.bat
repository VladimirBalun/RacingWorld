@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameserver

echo Copyright 2018 Vladimir Balun - Script to run game server on Windows."

cd %GAME_SERVER_PATH%\target
start java -jar GameServer.jar
