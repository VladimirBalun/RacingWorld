rem Copyright 2018 Vladimir Balun
rem
rem Licensed under the Apache License, Version 2.0 (the "License");
rem you may not use this file except in compliance with the License.
rem You may obtain a copy of the License at
rem
rem    http://www.apache.org/licenses/LICENSE-2.0
rem
rem Unless required by applicable law or agreed to in writing, software
rem distributed under the License is distributed on an "AS IS" BASIS,
rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
rem See the License for the specific language governing permissions and
rem limitations under the License.

@echo off
 
set CURRENT_PATH=%cd%
set SERVER_SIDE_PATH=%CURRENT_PATH%\..\ServerSide

set AUTHORIZATION_SERVER_PATH=%SERVER_SIDE_PATH%\authorizationServer
set GAME_SERVER_PATH=%SERVER_SIDE_PATH%\gameServer

set AUTHORIZATION_SERVER_JAR=%AUTHORIZATION_SERVER_PATH%\target\authorizationServer-0.0.1-SNAPSHOT-jar-with-dependencies.jar
set GAME_SERVER_JAR=%GAME_SERVER_PATH%\target\gameServer-0.0.1-SNAPSHOT-jar-with-dependencies.jar

echo Copyright 2018 Vladimir Balun - Script to run all the servers on Windows. 
start java -jar %AUTHORIZATION_SERVER_JAR%
start java -jar %GAME_SERVER_JAR%
