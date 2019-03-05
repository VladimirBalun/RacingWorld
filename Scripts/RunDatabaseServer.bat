@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set DATABASE_SERVER_PATH=%SERVER_SIDE_PATH%\databaseserver

echo Copyright 2018 Vladimir Balun - Script to run database server on Windows.

cd %DATABASE_SERVER_PATH%\target
start java -jar DatabaseServer.jar
