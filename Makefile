PROJECT     = sp3

CC          = i686-w64-mingw32-gcc
CFLAGS      = -std=c99 -O2 -m32\
              -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion\
              -Wno-error=attributes -Wno-error=pedantic

LD          = i686-w64-mingw32-ld
LDFLAGS     = -shared --entry=_DllMain@12

ASM         = nasm
ASFLAGS     = -f win32

BIN         = lib
BUILD       = build
DEBUG       = $(OBJ)/debug
RELEASE     = $(OBJ)/release

SRC         = src
OBJ         = build
SOURCES     = $(wildcard $(SRC)/*.c)
DBG_OBJECTS = $(patsubst $(SRC)/%.c,$(DEBUG)/%_d.o,$(SOURCES))
REL_OBJECTS = $(patsubst $(SRC)/%.c,$(RELEASE)/%.o,$(SOURCES))

INCLUDE     = include
INCLUDES    = $(addprefix -I,$(INCLUDE))
HEADERS     = $(wildcard $(INCLUDE)/*.h)

LIB_FILES   = d3d9 d3dx9 kernel32 user32 msvcrt
LIBS        = $(addprefix -l,$(LIB_FILES))

ASM_TARGET  = health_detour
ASM_SRC     = $(SRC)/asm
ASM_OBJ     = $(BUILD)/asm
ASM_SOURCES = $(wildcard $(ASM_SRC)/*.asm)
ASM_OBJECTS = $(patsubst $(ASM_SRC)/%.asm,$(ASM_OBJ)/%.obj,$(ASM_SOURCES))

MAKEFLAGS  += $(addprefix -j,$(shell nproc))

all: release

debug: $(DEBUG)
$(DEBUG): $(BIN)/$(PROJECT)_d.dll
$(DEBUG): CFLAGS += -g

release: $(PROJECT)
$(PROJECT): $(BIN)/$(PROJECT).dll
$(PROJECT): CFLAGS  += -march=native -Ofast -fPIE -funsafe-math-optimizations -fomit-frame-pointer
$(PROJECT): CFLAGS  += -funroll-loops -funsafe-loop-optimizations -funswitch-loops -floop-parallelize-all
$(PROJECT): CFLAGS  += -finline-functions -falign-functions -falign-loops -falign-jumps -fno-function-sections
$(PROJECT): CFLAGS  += -fno-ident -fvisibility=hidden -fstrict-aliasing
$(PROJECT): LDFLAGS += -s

$(BIN)/$(PROJECT)_d.dll: $(OBJ) $(BIN) $(ASM_OBJECTS) $(DBG_OBJECTS) 
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(DBG_OBJECTS) $(LIBS) -o $@

$(BIN)/$(PROJECT).dll: $(OBJ) $(BIN) $(ASM_OBJECTS) $(REL_OBJECTS)
	$(LD) $(LDFLAGS) $(ASM_OBJECTS) $(REL_OBJECTS) $(LIBS) -o $@

$(ASM_OBJECTS): $(ASM_OBJ)/%.obj: $(ASM_SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(DBG_OBJECTS): $(DEBUG)/%_d.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(REL_OBJECTS): $(RELEASE)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(OBJ):
	mkdir -p build/asm
	mkdir -p build/debug
	mkdir -p build/release

$(BIN):
	mkdir -p lib

clean:
	rm -f `find ./lib -name "*.dll"`
	rm -f `find ./build -name "*.o"`
	rm -f `find ./build -name "*.obj"`

extra-clean:
	rm -fr lib
	rm -fr build
