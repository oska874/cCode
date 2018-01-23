
CROSS_COMPILE=arm-linux-gnueabihf-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
QEMU=qemu-arm

NEON_FLAGS = -mfpu=neon #enable neon
FLOAT_FALGS = -mfloat-abi=hard #I used hard float arm gcc,softfp should used in normal arm gcc
CPU_FLAGS = -mcpu=cortex-a9 #cortex a serials have neon
CFLAGS = $(FLOAT_Flags) $(NEON_FLAGS) $(CPU_FLAGS) -static #must compile with static,or cannot running in qemu-arm

SRC_FILE = neon_test1.c
LIB_FILE = neon_test1.o
EXE_FILE = neon

all: NEON_TEST
	$(CC) $(CFLAGS) -o $(EXE_FILE) $(LIB_FILE)
	$(QEMU) $(EXE_FILE)

NEON_TEST: $(LIB_FILE)

clean:
	rm *.[oa]
	rm neon

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
