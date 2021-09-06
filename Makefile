# MAKEFLAGS += silent

PROJECT=sp3

CC=i686-w64-mingw32-gcc
CFLAGS=-std=c99 -masm=intel -Wall -Wextra -shared
EXTRA_FLAGS=-fms-extensions

SRC=src
OBJ=build
SOURCES=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

BIN=bin
DEBUG=$(OBJ)/debug
RELEASE=$(OBJ)/release

INCLUDE=include 
DIRECTX_INCLUDE=/usr/i686-w64-mingw32/include
INCLUDES=-I$(INCLUDE) -I$(DIRECTX_INCLUDE)

LIB_FILES=-ld3d9 -ld3dx9
LIBS=$(LIB_FILES)

#TEST=tests
#TESTS=$(wildcard $(TEST)/*.c)

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS+=-g -DDEBUG
$(DEBUG): $(OBJS) $(OBJ) $(BIN)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS+=-s -O3
$(PROJECT): $(OBJS) $(OBJ) $(BIN)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p $@
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm $(OBJ)/*
	rm $(BIN)/*
