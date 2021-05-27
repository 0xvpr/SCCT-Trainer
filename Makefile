# MAKEFLAGS += silent

PROJECT=sp3

ifeq ($(shell uname), Linux)
	CC=i686-w64-mingw32-gcc
else
	CC=gcc
endif

STD=c99

OUT_DIR=./bin
SRC_DIR=./src
INCLUDE_DIR=./include

EXTRA_FLAGS=-s -O3 -shared -masm=intel

SOURCES=$(SRC_DIR)/*.c
INCLUDES=-I$(INCLUDE_DIR)
LIB_FILES=-lwinmm

WARNINGS=-Wno-ignored-attributes \
	-Wno-pointer-to-int-cast \
	-Wno-int-to-pointer-cast \
	-Wno-ignored-attributes \
	-Wno-implicit-function-declaration \

COMPATIBILITY= -fms-extensions

all:
	$(CC) -std=$(STD) $(EXTRA_FLAGS) -o $(OUT_DIR)/$(PROJECT).dll \
	$(SOURCES) \
	$(INCLUDES) \
	$(LIB_FILES) \
	$(WARNINGS) \
	$(COMPATIBILITY)

clean:
	rm $(OUT_DIR)/$(PROJECT).dll