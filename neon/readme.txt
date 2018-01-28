compile method:

make FLOAT=hard NUM=test4 NE10_ON=y

FLOAT => hard or float
NUM => test1 ~ testN
NE10_ON => y or disable


ps:
1. ne10 https://github.com/projectNe10/Ne10.git
    cross compile(for armv7): mkdir build;cd build; cmake -DCMAKE_TOOLCHAIN_FILE=../GNUlinux_config.cmake -DNE10_LINUX_TARGET_ARCH=armv7 ..;make -j4;
    you should provide ne10 lib&inc path in Makefile.
