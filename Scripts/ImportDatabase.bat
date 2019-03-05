@echo off

set USERNAME=root
set DATABASE_NAME=RacingWorld

set CURRENT_PATH=%cd%
set DATABASE_PATH=%CURRENT_PATH%\..\Database

echo Copyright 2018 Vladimir Balun - Script to import database on Windows.

mysql -u %USERNAME% -p %DATABASE_NAME% < %DATABASE_PATH%\%DATABASE_NAME%.sql
