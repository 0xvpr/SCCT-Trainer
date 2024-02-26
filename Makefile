PROJECT     = sp3

LD          = i686-w64-mingw32-ld
LDFLAGS     = -s -shared --entry=_DllMain@12

ASM         = nasm
ASFLAGS     = -f win32

LIB         = lib
BUILD       = build
DEBUG       = $(OBJ)/debug
RELEASE     = $(OBJ)/release

SRC         = src
OBJ         = build
SOURCES     = $(wildcard $(SRC)/*.asm)
OBJECTS     = $(patsubst $(SRC)/%.asm,$(OBJ)/%.obj,$(SOURCES))

LIB_FILES   = d3d9 d3dx9 kernel32 user32 msvcrt
LIBS        = $(addprefix -l,$(LIB_FILES))

MAKEFLAGS  += $(addprefix -j,$(shell nproc))

all: release

release: $(PROJECT)
$(PROJECT): $(LIB)/$(PROJECT).dll

$(LIB)/$(PROJECT).dll: $(OBJ) $(LIB) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

$(OBJECTS): $(OBJ)/%.obj: $(SRC)/%.asm
	$(ASM) $(ASFLAGS) $^ -o $@

$(OBJ):
	mkdir -p build

$(LIB):
	mkdir -p lib

.PHONY: docker-container
docker-container:
	docker build -f "Dockerfile" -t "$(PROJECT)-dev" .
.PHONY: docker-build
docker-build:
	docker run -v "$(shell pwd):/var/$(PROJECT)-dev/$(PROJECT)" -u "$(shell id -u):$(shell id -g)" "$(PROJECT)-dev" make

clean:
	rm -f `find ./lib -name "*.dll"`
	rm -f `find ./build -name "*.o"`
	rm -f `find ./build -name "*.obj"`

extra-clean:
	rm -fr lib
	rm -fr build
