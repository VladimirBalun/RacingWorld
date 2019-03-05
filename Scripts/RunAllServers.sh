#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver

echo "Copyright 2018 Vladimir Balun - Script to run all the servers on Linux."

cd $GAME_SERVER_PATH/target
bash java -jar GameServer.jar

cd $DATABASE_SERVER_PATH/target
bash java -jar DatabaseServer.jar