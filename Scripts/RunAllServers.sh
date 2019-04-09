#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver
readonly RESOURCE_SERVER_PATH=$SERVER_SIDE_PATH/resourceserver
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver

echo "Copyright 2018 Vladimir Balun - Script to run all the servers on Linux."

if ! [ -x "$(command -v java)" ]; then
  echo "Error: Java is not installed."
  exit 1
fi	

if ! [ -f "$DATABASE_SERVER_PATH/target/DatabaseServer.jar" ]; then
  echo "Error: database server is absent. Please build it and repeat."
  exit 2
fi

java -jar $DATABASE_SERVER_PATH/target/DatabaseServer.jar &

if ! [ -f "$GAME_SERVER_PATH/target/GameServer.jar" ]; then
  echo "Error: game server is absent. Please build it and repeat."
  exit 2
fi

java -jar $GAME_SERVER_PATH/target/GameServer.jar &

if ! [ -f "$RESOURCE_SERVER_PATH/target/ResourceServer.jar" ]; then
  echo "Error: resource server is absent. Please build it and repeat."
  exit 2
fi

java -jar $RESOURCE_SERVER_PATH/target/ResourceServer.jar &
