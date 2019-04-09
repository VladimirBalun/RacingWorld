#!/bin/bash

readonly CURRENT_PATH=$(pwd)
readonly SERVER_SIDE_PATH=$CURRENT_PATH/../ServerSide
readonly RESOURCE_SERVER_PATH=$SERVER_SIDE_PATH/resourceserver

echo "Copyright 2018 Vladimir Balun - Script to run resource server on Linux."

if ! [ -x "$(command -v java)" ]; then
  echo "Error: Java is not installed."
  exit 1
fi

if ! [ -f "$RESOURCE_SERVER_PATH/target/ResourceServer.jar" ]; then
  echo "Error: resource server is absent. Please build it and repeat."
  exit 2
fi

java -jar $RESOURCE_SERVER_PATH/target/ResourceServer.jar