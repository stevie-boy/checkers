#!/bin/bash

# load env params
SCRIPT_DIR=$(dirname "$0")

. ${SCRIPT_DIR}/common.sh

EXTRA_OPTS=
CURRENT_DIR=$(pwd)
BUILD_PARENT=${PROJECT_ROOT}/build
BUILD_OUT_DIR=


if [ "$1" == "debug" ]; then
	EXTRA_OPTS=$DEBUG_OPTS
	BUILD_OUT_DIR=${BUILD_PARENT}/debug
else 
	BUILD_OUT_DIR=${BUILD_PARENT}/prod
	EXTRA_OPTS=$RELEASE_OPTS
fi

# create output dir if necessary
if [ ! -d $BUILD_OUT_DIR ]; then
	mkdir $BUILD_OUT_DIR
fi

g++ -I${PROJECT_ROOT}/src/headers ${EXTRA_OPTS} -o ${BUILD_OUT_DIR}/checkers.exe ${PROJECT_ROOT}/src/classes/*.cpp

