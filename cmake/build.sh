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
cmake -DCMAKE_TOOLCHAIN_FILE=../p1020_toolchain.cmake ..
make
powerpc-unknown-linux-gnuspe-objdump -D RTS > RTSdump

if [ $# -eq 1 ]
then
    if [ $1 = "qemu" ]
    then
        qemu-ppc -cpu e500v2_v22 RTS
    fi
fi
