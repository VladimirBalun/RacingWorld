#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver

echo "Copyright 2018 Vladimir Balun - Script to run database server on Linux."

cd $DATABASE_SERVER_PATH/target
bash java -jar DatabaseServer.jar
