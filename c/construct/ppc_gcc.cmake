#compile cfgs
SET(CMAKE_SYSTEM_NAME "Linux")
SET(CMAKE_C_COMPILER /os_dev/toolchain/old_gcc/Cross_Tools/gcc-4.7.2-XMe500v2-linuxspe/bin/powerpc-unknown-linux-gnuspe-gcc)

#SET(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)

SET(CMAKE_FIND_ROOT_PATH /os_dev/toolchain/old_gcc/Cross_Tools/gcc-4.7.2-XMe500v2-linuxspe/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

