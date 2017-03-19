#!/bin/bash

# load env params
SCRIPT_DIR=$(dirname "$0")

. ${SCRIPT_DIR}/common.sh

BUILD_PARENT=${PROJECT_ROOT}/build
COMPILE_OUT_DIR=
BUILD_OUT_DIR=

if [ "$1" == "debug" ]; then
	COMPILE_OUT_DIR=$COMPILE_DEBUG_OUT_DIR
	BUILD_OUT_DIR=${BUILD_PARENT}/debug
else
	COMPILE_OUT_DIR=$COMPILE_PROD_OUT_DIR
	BUILD_OUT_DIR=${BUILD_PARENT}/prod
fi

g++ ${COMPILE_OUT_DIR}/*.o -o ${BUILD_OUT_DIR}/checkers.exe

