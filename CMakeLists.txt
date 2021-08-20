cmake_minimum_required(VERSION 3.6)

project("SCCT GUI")

set(EXEC "scctgui")
set(CMAKE_C_STANDARD 17)

## Sources
file(GLOB SOURCES src/*.c)

## Includes
include_directories(include)
include_directories("C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")

## Library
link_directories("C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib/x86")

## Output DLL
add_library(${EXEC} SHARED ${SOURCES})

target_link_libraries(${EXEC} d3d9 d3dx9)