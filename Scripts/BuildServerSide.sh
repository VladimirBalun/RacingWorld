#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH/gameserver
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver
readonly PROTOCOL_PATH=$SERVER_SIDE_PATH/protocol

echo "Copyright 2018 Vladimir Balun - Script to build all the servers on Linux."

echo "Building of the protocol between servers..."
cd $PROTOCOL_PATH
mvn clean compile assembly:single

echo "Building of the game server..."
cd $GAME_SERVER_PATH
mvn clean compile assembly:single

echo "Building of the database server..."
cd $DATABASE_SERVER_PATH
mvn clean compile assembly:single