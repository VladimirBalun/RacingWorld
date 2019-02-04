@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide

set AUTHORIZATION_SERVER_PATH=%SERVER_SIDE_PATH%\authorization
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\game

echo "Copyright 2018 Vladimir Balun - Script to build all the servers on Windows."

echo "Building of the authorization server..."
cd %AUTHORIZATION_SERVER_PATH%
mvn clean compile assembly:single

echo "Building of the game server..."
cd %GAME_SERVER_PATH%
mvn clean compile assembly:single
