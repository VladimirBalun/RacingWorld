#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver

echo "Copyright 2018 Vladimir Balun - Script to run game server on Linux."

if ! [ -x "$(command -v java)" ]; then
  echo "Error: Java is not installed."
  exit 1
fi

if ! [ -f "$GAME_SERVER_PATH/target/GameServer.jar" ]; then
  echo "Error: game server is absent. Please build it and repeat."
  exit 2
fi

java -jar $GAME_SERVER_PATH/target/GameServer.jar