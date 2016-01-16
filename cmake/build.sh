#!/bin/sh

if [ -d build ]
then
    echo "start building"
else
    echo "mkdir output dir"
    mkdir build
    echo "start building"
fi

rm -rf ./build/*
cd build
if [ $# -eq 1 ]
then
    if [ $1 = "ppc" ]
    then
        cmake -DCMAKE_TOOLCHAIN_FILE=../p1020_toolchain.cmake ..
        make
        powerpc-unknown-linux-gnuspe-objdump -D RTS > RTSdump
    elif [ $1 = "arm" ]
    then
        cmake -DCMAKE_TOOLCHAIN_FILE=../a9_toolchain.cmake ..
        make
        arm-linux-gnueabihf-objdump -D RTS > RTSdump
    elif [ $1 = "local" ]
    then
        cmake  ..
        make
        objdump -D RTS > RTSdump
    fi
fi


