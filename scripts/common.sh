SCRIPT_DIR=$(dirname "$(realpath "$0")")
PROJECT_ROOT=${SCRIPT_DIR}/../
DEBUG_OPTS="-g -ggdb -g3"
RELEASE_OPTS="-static-libgcc -static-libstdc++"

export PROJECT_ROOT
export DEBUG_OPTS
export RELEASE_OPTS

