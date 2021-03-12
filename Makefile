CC=/usr/bin/i686-w64-mingw32-gcc
all:
	$(CC) -m32 -std=c17 -shared -o ./Release/sp3.dll ./src/*.c \
	-isystem/usr/lib/gcc/x86_64-w64-mingw32/9.3-win32/include \
	-isystem/usr/lib/gcc/x86_64-w64-mingw32/9.3-win32/include-fixed \
	-isystem/usr/x86_64-w64-mingw32/include \
	-Isrc \
	-Iincludes \
	-Wno-ignored-attributes \
	-Wno-pointer-to-int-cast \
	-Wno-int-to-pointer-cast \
	-Wno-ignored-attributes
clean:
	rm Release/sp3.dll
