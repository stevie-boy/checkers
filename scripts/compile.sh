#!/bin/bash

# load env params
SCRIPT_DIR=$(dirname "$0")

. ${SCRIPT_DIR}/common.sh

EXTRA_OPTS=
OUT_DIR=
CURRENT_DIR=$(pwd)

if [ "$1" == "debug" ]; then
	EXTRA_OPTS=$DEBUG_OPTS
	OUT_DIR=$COMPILE_DEBUG_OUT_DIR
else 
	OUT_DIR=$COMPILE_PROD_OUT_DIR
fi

cd $OUT_DIR

g++ -I${PROJECT_ROOT}/src/headers ${DEBUG_OPTS} -c ${PROJECT_ROOT}/src/classes/*.cpp

cd $CURRENT_DIR
