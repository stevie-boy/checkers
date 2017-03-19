CORE_PATH=/usr/bin
SCRIPT_PATH=$(pwd)
SCRIPTS_DIR=`${CORE_PATH}/dirname "${SCRIPT_PATH}"`/scripts
MINGW=/c/MinGw/bin
GIT_HOME=/mingw64/bin

PATH=$CORE_PATH:$SCRIPTS_DIR:$MINGW:$GIT_HOME

export PATH

