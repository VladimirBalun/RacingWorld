#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH\..\ServerSide

readonly AUTHORIZATION_SERVER_PATH=$SERVER_SIDE_PATH\authorization
readonly GAME_SERVER_PATH=$SERVER_SIDE_PATH\game

echo "Copyright 2018 Vladimir Balun - Script to build all the servers on Linux."

echo "Building of the authorization server..."
cd $AUTHORIZATION_SERVER_PATH
mvn clean compile assembly:single

echo "Building of the game server..."
cd $GAME_SERVER_PATH
mvn clean compile assembly:single
