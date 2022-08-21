CROSS_COMPILE_HARD=arm-linux-gnueabihf-
CROSS_COMPILE=arm-linux-gnueabi-

NE10_LIB_PATH = /second/src/Ne10/build/modules
NE10_INC_PATH = /second/src/Ne10/inc

ifeq ($(NE10_ON),y)
	NE10 = -lNE10
	CFLAGS = -L$(NE10_LIB_PATH) -I$(NE10_INC_PATH)
else
	NE10 = 
endif
ifeq ($(FLOAT), hard)
	CC=$(CROSS_COMPILE_HARD)gcc
	LD=$(CROSS_COMPILE_HARD)ld
	NEON_FLAGS = -mfpu=neon #enable neon
else
	ifeq ($(FLOAT), soft)
		CC=$(CROSS_COMPILE)gcc
		LD=$(CROSS_COMPILE)ld
		NEON_FLAGS = -mfpu=neon #enable neon
	else
		$(error "FLOAT=hard or soft?")
	endif
endif

ifeq ($(NUM), )
	$(error "NUM=test?")
endif

QEMU=qemu-arm

HARD=hard
SOFT=softfp

NEON_FLAGS = -mfpu=neon #disable neon
FLOAT_FLAGS = -mfloat-abi=#I used hard float arm gcc,softfp should used in normal arm gcc
CPU_FLAGS = -mcpu=cortex-a9 #cortex a serials have neon

ifeq ($(FLOAT), hard)
	CFLAGS += $(FLOAT_FLAGS)$(HARD) $(NEON_FLAGS) $(CPU_FLAGS) -static #must compile with static,or cannot running in qemu-arm
else
	ifeq ($(FLOAT), soft)
		CFLAGS += $(FLOAT_FLAGS)$(SOFT) $(NEON_FLAGS) $(CPU_FLAGS) -static #must compile with static,or cannot running in qemu-arm
	endif
endif

SRC_FILE = neon_$(NUM).c
LIB_FILE = neon_$(NUM).o
EXE_FILE = neon

all: NEON_TEST
	$(CC) $(CFLAGS) -o $(EXE_FILE) $(LIB_FILE) $(NE10)
	$(QEMU) $(EXE_FILE)
	rm neon_$(NUM).o

NEON_TEST: $(LIB_FILE)

clean:
	rm neon
	rm *.[oa]

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<
