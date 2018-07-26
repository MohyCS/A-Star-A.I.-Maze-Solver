#!/bin/sh

PRACSYS_CODE_SRC_PARENT_DIR="$PRACSYS_PATH/prx_core/prx/utilities"
PRACSYS_CODE_SRC_DIR="$PRACSYS_CODE_SRC_PARENT_DIR/applications"
echo "Moving contents to $PRACSYS_CODE_SRC_DIR"

rm -rf $PRACSYS_CODE_SRC_DIR
mkdir $PRACSYS_CODE_SRC_DIR
mv ../AStar/* $PRACSYS_CODE_SRC_DIR

rm -rf ../AStar
