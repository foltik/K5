#!/bin/bash

NAME=$1
DEST=$2

if [ "$#" != 2 ]; then
	echo "Usage: init.sh [name] [path]"
	exit
fi

mkdir -p $DEST

cp base/main.cpp $DEST
cp base/mainframe.cpp $DEST
cp base/mainframe.h $DEST
cp base/CMakeLists.txt $DEST

mkdir -p $DEST/models
mkdir -p $DEST/textures
mkdir -p $DEST/shaders
mkdir -p $DEST/fonts

cp textures/* $DEST/textures/
cp models/* $DEST/models/

sed -i -e "s/k5starter/$NAME/g" $DEST/main.cpp
sed -i -e "s/k5starter/$NAME/g" $DEST/CMakeLists.txt
