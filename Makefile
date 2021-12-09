PROJECT = sp3

CC      = i686-w64-mingw32-gcc
CFLAGS  = -std=c99 -masm=intel -pedantic -Wall -Wextra -Werror -shared

LD      = i686-w64-mingw32-gcc
LDFLAGS = -shared

ASM     = nasm
ASFLAGS = -f win32

BIN     = bin
BUILD   = build
DEBUG   = $(OBJ)/debug
RELEASE = $(OBJ)/release

SRC     = src
OBJ     = build
SOURCES = $(wildcard $(SRC)/*.c)
DBG_OBJECTS = $(patsubst $(SRC)/%.c,$(DEBUG)/%.o,$(SOURCES))
REL_OBJECTS = $(patsubst $(SRC)/%.c,$(RELEASE)/%.o,$(SOURCES))

INCLUDE  = include 
INCLUDES = $(addprefix -I,$(INCLUDE))

LIB_FILES = d3d9 d3dx9
LIBS      = $(addprefix -l,$(LIB_FILES))

ASM_TARGET = healthDetour
ASM_SRC    = $(SRC)/healthDetour.asm
ASM_OBJ    = $(OBJ)/healthDetour.o

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS += -g
$(DEBUG): $(OBJ) $(BIN) $(ASM_OBJ) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(ASM_OBJ) $(DBG_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS  += -O3 -fno-ident -fvisibility=hidden
$(PROJECT): LDFLAGS += -s
$(PROJECT): $(OBJ) $(BIN) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(ASM_OBJ) $(REL_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(ASM_OBJ): $(OBJ)/%.o: $(SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p $@/debug
	mkdir -p $@/release

$(BIN):
	mkdir -p $@

clean:
	rm -f bin/*
	rm -f build/*

extra-clean:
	rm -fr bin
	rm -fr build
