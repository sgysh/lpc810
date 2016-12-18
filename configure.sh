#!/bin/bash

USAGE="
USAGE: ${0} <example_name>
"

EXAMPLE_DIR_NAME="examples"
CORE_DIR_NAME="core"
OUT_DIR_NAME="out"

if [ ${#} -ne 1 ]; then
  echo "${USAGE}"
  exit 1
fi

ROOT=`pwd`
EXAMPLE_NAME=${1}
PATH_TO_EXAMPLE=${ROOT}/${EXAMPLE_DIR_NAME}/${EXAMPLE_NAME}
PATH_TO_CORE=${ROOT}/${CORE_DIR_NAME}
PATH_TO_OUT=${ROOT}/${OUT_DIR_NAME}

CLEAN_OPT="clean"
if [ ${1} = ${CLEAN_OPT} ]; then
  rm -rfv ${PATH_TO_OUT}
  exit 0
fi

if [ ! -d ${PATH_TO_EXAMPLE} ]; then
  echo "Example ${EXAMPLE_NAME} does not exist."
  echo "${USAGE}"
  exit 2
fi

if [ -d ${PATH_TO_OUT} ]; then
  rm -rfv ${PATH_TO_OUT}
fi
mkdir -pv ${PATH_TO_OUT}
cp -v ${PATH_TO_EXAMPLE}/* ${PATH_TO_OUT}
cp -v ${PATH_TO_CORE}/* ${PATH_TO_OUT}
