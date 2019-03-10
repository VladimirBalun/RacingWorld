@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameserver
set RESOURCE_SERVER_PATH=%SERVER_SIDE_PATH%\resourceserver
set DATABASE_SERVER_PATH=%SERVER_SIDE_PATH%\databaseserver

echo Copyright 2018 Vladimir Balun - Script to run all the servers on Windows.

cd %DATABASE_SERVER_PATH%\target
start java -jar DatabaseServer.jar

cd %GAME_SERVER_PATH%\target
start java -jar GameServer.jar

cd %RESOURCE_SERVER_PATH%\target
start java -jar ResourceServer.jar