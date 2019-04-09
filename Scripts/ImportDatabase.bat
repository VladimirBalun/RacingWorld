@echo off

set USERNAME=root
set DATABASE_NAME=RacingWorld

set CURRENT_PATH=%cd%
set DATABASE_PATH=%CURRENT_PATH%\..\Database

echo Copyright 2018 Vladimir Balun - Script to import database on Windows.

mysql --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Error: MySQL is not installed.
  exit 1
) 

mysql -u %USERNAME% -p %DATABASE_NAME% < %DATABASE_PATH%\%DATABASE_NAME%.sql
