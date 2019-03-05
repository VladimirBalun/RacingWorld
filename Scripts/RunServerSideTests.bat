@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameserver
set DATABASE_SERVER_PATH=%SERVER_SIDE_PATH%\databaseserver

echo Copyright 2018 Vladimir Balun - Script to testing all the servers on Windows.

echo Testing of the game server...
cd %GAME_SERVER_PATH%
mvn test

echo Testing of the database server...
cd %DATABASE_SERVER_PATH%
mvn test
