#!/bin/bash

# load env params
SCRIPT_DIR=$(dirname "$0")

. ${SCRIPT_DIR}/common.sh

BUILD_ARTIFACT=
BUILD_OPTS=

if [ "$1" == "debug" ]; then
	BUILD_OPTS=$DEBUG_OPTS
	BUILD_ARTIFACT=$DEBUG_ARTIFACT
else
	BUILD_OPTS=$RELEASE_OPTS							
	BUILD_ARTIFACT=$RELEASE_ARTIFACT

fi

# create output dir if necessary
BUILD_OUT_DIR=$(dirname "${BUILD_ARTIFACT}")
if [ ! -d $BUILD_OUT_DIR ]; then
	mkdir $BUILD_OUT_DIR
fi

g++ -I${PROJECT_ROOT}/src/headers ${BUILD_OPTS} -o ${BUILD_ARTIFACT} ${PROJECT_ROOT}/src/classes/*.cpp

