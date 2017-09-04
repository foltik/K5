#!/bin/bash

NAME=$1
DEST=$2

if [ "$#" != 2 ]; then
	echo "Usage: init.sh [name] [path]"
	exit
fi

mkdir -p $DEST
mkdir -p $DEST/src
mkdir -p $DEST/models
mkdir -p $DEST/textures
mkdir -p $DEST/shaders
mkdir -p $DEST/fonts

cp base/main.cpp $DEST/src/
cp base/mainframe.cpp $DEST/src/
cp base/mainframe.h $DEST/src/
cp base/CMakeLists.txt $DEST
cp textures/* $DEST/textures/
cp models/* $DEST/models/

sed -i -e "s/k5starter/$NAME/g" $DEST/src/main.cpp
sed -i -e "s/k5starter/$NAME/g" $DEST/CMakeLists.txt
