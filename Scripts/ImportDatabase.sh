#!/bin/bash

readonly USERNAME=root
readonly DATABASE_NAME=RacingWorld

readonly CURRENT_PATH=$(pwd)
readonly DATABASE_PATH=$CURRENT_PATH/../Database

echo "Copyright 2018 Vladimir Balun - Script to import database on Linux."

mysql -u $USERNAME -p $DATABASE_NAME < $DATABASE_PATH/$DATABASE_NAME.sql