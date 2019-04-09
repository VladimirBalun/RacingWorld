@echo off

set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide
set DATABASE_SERVER_PATH=%SERVER_SIDE_PATH%\databaseserver

echo Copyright 2018 Vladimir Balun - Script to run database server on Windows.

java -version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Error: Java is not installed.
  exit 1
) 

if not exist %DATABASE_SERVER_PATH%\target\DatabaseServer.jar (
  echo Error: database server is absent. Please build it and repeat.
  exit 2
) 

java -jar %DATABASE_SERVER_PATH%\target\DatabaseServer.jar