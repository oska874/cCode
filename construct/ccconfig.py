import os


ARCH="arm"
CPU='zynq7000'
CROSS_TOOL='gcc'

if ARCH == 'arm':
    EXEC_PATH='/usr/bin/'
    CROSS_COMPILE='arm-linux-gnueabi-'
#    SYS_ROOT=''
    CFLAGS=' -std=gnu99 -g -ggdb -static -O0 -Wall '
elif ARCH == 'ppc':
    EXEC_PATH=''
    CROSS_COMPILE=''
    SYS_ROOT=''
elif ARCH == 'x86':
    EXEC_PATH='/usr/bin'
    CROSS_COMPILE=''
    SYS_ROOT=''
    

CC = CROSS_COMPILE +'gcc' 
CXX = CROSS_COMPILE + 'g++'
AS = CROSS_COMPILE + 'gcc'                                              
AR = CROSS_COMPILE + 'ar'
LINK = CROSS_COMPILE + 'gcc'
TARGET_EXT = 'elf'
SIZE = CROSS_COMPILE + 'size'
OBJDUMP = CROSS_COMPILE + 'objdump'
OBJCPY = CROSS_COMPILE + 'objcopy'                                      
DEVICE = ' -Wall -mcpu=cortex-a9 -mfpu=vfpv3 -ftree-vectorize -ffast-math -mfloat-abi=softfp'
CFLAGS += DEVICE
AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
#LINK_SCRIPT = ''
#LFLAGS = ' -L /usr/arm-linux-gnueabi/lib' 

CPATH = ''                                                       
LPATH = ''                                                       
