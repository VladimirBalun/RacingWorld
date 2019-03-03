#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver

echo "Copyright 2018 Vladimir Balun - Script to run game server on Windows."
cd $GAME_SERVER_PATH/target
bash java -jar GameServer.jar
