PROJECT       = sp3

CC            = i686-w64-mingw32-g++-posix
CFLAGS        = -std=c++2a -O2\
                -Wall -Wextra -Werror -Wshadow -Wconversion -Wpedantic\
                -Wno-write-strings

LD            = i686-w64-mingw32-ld
LDFLAGS       = -shared -nostdinc++

ASM           = nasm
ASFLAGS       = -f win32

BIN           = Lib
BUILD         = Build
DEBUG         = $(BUILD)/Debug
RELEASE       = $(BUILD)/Release

SOURCE        = Sources
OBJECT        = $(BUILD)
SOURCES       = $(wildcard $(SOURCE)/*.cpp)
DBG_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(DEBUG)/%.o,$(SOURCES))
REL_OBJECTS   = $(patsubst $(SOURCE)/%.cpp,$(RELEASE)/%.o,$(SOURCES))
MINGW_OBJECTS = /usr/i686-w64-mingw32/lib/dllcrt2.o

INCLUDE       = Includes
INCLUDES      = $(addprefix -I,$(INCLUDE))

LINK_DIRS     = /usr/lib/gcc/i686-w64-mingw32/9.3-posix
LINKS         = $(addprefix -L,$(LINK_DIRS))

LIB_FILES     = d3d9 d3dx9 mingw32 moldname mingwex msvcrt user32 kernel32 msvcrt gcc
LIBS          = $(addprefix -l,$(LIB_FILES))

ASM_TARGET    = health_detour
ASM_SOURCE    = $(SOURCE)/asm
ASM_OBJECT    = $(BUILD)/asm
ASM_SOURCES   = $(wildcard $(ASM_SOURCE)/*.asm)
ASM_OBJECTS   = $(patsubst $(ASM_SOURCE)/%.asm,$(ASM_OBJECT)/%.obj,$(ASM_SOURCES))

MAKEFLAGS    += -j$(shell nproc)

all: debug release

debug: $(DEBUG)
release: $(PROJECT)

$(DEBUG): CFLAGS += -g
$(DEBUG): $(BUILD) $(BIN) $(ASM_OBJECTS) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(LINKS) $(ASM_OBJECTS) $(DBG_OBJECTS) $(MINGW_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT)_d.dll

$(PROJECT): CFLAGS  += -O3 -ffast-math -fvisibility=hidden -fno-ident -fno-rtti
$(PROJECT): LDFLAGS += -s
$(PROJECT): $(BUILD) $(BIN) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(LINKS) $(ASM_OBJECTS) $(REL_OBJECTS) $(MINGW_OBJECTS) $(LIBS) -o $(BIN)/$(PROJECT).dll

$(ASM_OBJECTS): $(ASM_OBJECT)/%.obj: $(ASM_SOURCE)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%.o: $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SOURCE)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(BUILD):
	mkdir -p Build/Asm
	mkdir -p Build/Debug
	mkdir -p Build/Release

$(BIN):
	mkdir -p Bin

clean:
	rm -f Bin/*
	rm -f Build/{Asm,Debug,Release}/*

extra-clean:
	rm -fr Bin
	rm -fr Build
