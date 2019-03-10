#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver
readonly RESOURCE_SERVER_PATH=$SERVER_SIDE_PATH/resourceserver
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver

echo "Copyright 2018 Vladimir Balun - Script to testing all the servers on Linux."

echo "Testing of the game server..."
cd $GAME_SERVER_PATH
mvn test

echo "Testing of the database server..."
cd $DATABASE_SERVER_PATH
mvn test

echo "Testing of the resource server..."
cd $RESOURCE_SERVER_PATH
mvn test