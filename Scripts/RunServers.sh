#!/bin/bash

readonly GAME_SERVER_JAR_FILE=.."/ServerSide/GameServer/target/gameServer-0.0.1-SNAPSHOT"
readonly AUTHORIZATION_SERVER_JAR_FILE=.."/ServerSide/AuthorizationServer/target/authorizationServer-0.0.1-SNAPSHOT"

isExistJava() {
	if type -p java; then
		return 1
	else
		return 0
	fi	
}

isValidJavaVersion() {
    version=$(java -version 2>&1 | awk -F '"' '/version/ {print $2}')
	echo "Java version : $version"
	if [[ "$version" > "1.7" ]]; then
        return 1
	else
		return 0
    fi
}

if isExistJava; then
	echo "Error! Java does not exist on your PC..."
	exit -1
fi	

if isValidJavaVersion; then
	echo "Error! Java version is less than 1.8..."
	exit -2
fi	

java -jar GAME_SERVER_JAR_FILE
java -jar AUTHORIZATION_SERVER_JAR_FILE
