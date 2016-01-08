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
cmake -DCMAKE_TOOLCHAIN_FILE=../ppc_gcc.cmake ..
make
powerpc-unknown-linux-gnuspe-objdump -D EXECC > EXECCdump
