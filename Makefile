PROJECT = sp3

CC      = i686-w64-mingw32-gcc
CFLAGS  = -std=c99 -masm=intel -Wall -Wextra -Werror -shared

LD      = i686-w64-mingw32-gcc
LDFLAGS = 

BIN     = bin
BUILD   = build
DEBUG   = $(OBJ)/debug
RELEASE = $(OBJ)/release

SRC     = src
OBJ     = build
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))


INCLUDE  = include 
INCLUDES = -I$(INCLUDE)

LIB_FILES = -ld3d9 -ld3dx9
LIBS      = $(LIB_FILES)

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS+=-g -DDEBUG
$(DEBUG): $(OBJ) $(BIN) $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS+=-s -O2
$(PROJECT): $(OBJ) $(BIN) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p $@

$(BIN):
	mkdir -p $@

clean:
	rm -f bin/*
	rm -f build/*

extra-clean:
	rm -fr bin
	rm -fr build
