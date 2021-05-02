cmake_minimum_required(VERSION 3.8)

project("Splinter Cell 3 Hacks")
set(EXEC "sp3")

set(CMAKE_CXX_STANDARD 17)

## Sources
file(GLOB SOURCES src/*.cpp src/*.c)

## Includes
include_directories(include "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")

## Library Directories
link_directories(lib "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86")

## Output DLL
add_library(${EXEC} SHARED ${SOURCES})

# compiler options for LNK2026 error
#target_compile_options(${EXEC} PRIVATE /SAFESEH:NO)

# i have no fucking clue
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")

## Library Files
target_link_libraries(${EXEC} detours d3d9 d3dx9)
