#!/bin/bash

# load env params
SCRIPT_DIR=$(dirname "$0")
. ${SCRIPT_DIR}/common.sh

rm -f "$DEBUG_ARTIFACT" "$RELEASE_ARTIFACT"

