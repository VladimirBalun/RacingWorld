#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly DATABASE_SERVER_PATH=$SERVER_SIDE_PATH/databaseserver

echo "Copyright 2018 Vladimir Balun - Script to run database server on Linux."

if ! [ -x "$(command -v java)" ]; then
  echo "Error: Java is not installed."
  exit 1
fi	

if ! [ -f "$DATABASE_SERVER_PATH/target/DatabaseServer.jar" ]; then
  echo "Error: database server is absent. Please build it and repeat."
  exit 2
fi

java -jar $DATABASE_SERVER_PATH/target/DatabaseServer.jar
