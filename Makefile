PROJECT = sp3

CC      = i686-w64-mingw32-gcc-posix
CFLAGS  = -std=c++2a -masm=intel -Wall -Wextra -Werror -Wshadow -Wconversion -Wpedantic\
		  -Wno-write-strings

LD      = i686-w64-mingw32-ld
LDFLAGS = -shared 

ASM     = nasm
ASFLAGS = -f win32

BIN     = Lib
BUILD   = Build
DEBUG   = $(OBJ)/debug
RELEASE = $(OBJ)/release

SRC     = Sources
OBJ     = $(BUILD)
SOURCES = $(wildcard $(SRC)/*.cpp)
DBG_OBJECTS = $(patsubst $(SRC)/%.cpp,$(DEBUG)/%.o,$(SOURCES))
REL_OBJECTS = $(patsubst $(SRC)/%.cpp,$(RELEASE)/%.o,$(SOURCES))

INCLUDE  = Includes
INCLUDES = $(addprefix -I,$(INCLUDE))

LIB_FILES = d3d9 d3dx9 msvcrt kernel32 user32
LIBS      = $(addprefix -l,$(LIB_FILES))

ASM_TARGET  = health_detour
ASM_SRC     = $(SRC)/asm
ASM_OBJ     = $(BUILD)/asm
ASM_SOURCES = $(wildcard $(ASM_SRC)/*.asm)
ASM_OBJECTS = $(patsubst $(ASM_SRC)/%.asm,$(ASM_OBJ)/%.obj,$(ASM_SOURCES))

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS += -g
$(DEBUG): $(OBJ) $(BIN) $(ASM_OBJECTS) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(DBG_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS  += -O3 -fno-ident -fvisibility=hidden -fno-rtti
$(PROJECT): LDFLAGS += -s
$(PROJECT): $(OBJ) $(BIN) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(REL_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(ASM_OBJECTS): $(ASM_OBJ)/%.obj: $(ASM_SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SRC)/%.cpp
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
