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

ASM_TARGET  = health_detour
ASM_SRC     = asm
ASM_OBJ     = $(BUILD)/asm
ASM_SOURCES = $(wildcard $(ASM_SRC)/*.asm)
ASM_OBJECTS = $(patsubst $(ASM_SRC)/%.asm,$(ASM_OBJ)/%.obj,$(ASM_SOURCES))

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS += -g
$(DEBUG): $(OBJ) $(BIN) $(ASM_OBJECTS) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(DBG_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS  += -O3 -fno-ident -fvisibility=hidden
$(PROJECT): LDFLAGS += -s
$(PROJECT): $(OBJ) $(BIN) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(REL_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(ASM_OBJECTS): $(ASM_OBJ)/%.obj: $(ASM_SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p build/asm
	mkdir -p build/debug
	mkdir -p build/release

$(BIN):
	mkdir -p bin

clean:
	rm -f bin/*
	rm -f build/{asm,debug,release}/*

extra-clean:
	rm -fr bin
	rm -fr build
