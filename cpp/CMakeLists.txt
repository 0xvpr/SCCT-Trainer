cmake_minimum_required(VERSION 3.8)

project("Splinter Cell 3 Hacks")

set(EXEC "sp3")
set(CMAKE_CXX_STANDARD 17)

## Sources
file(GLOB SOURCES src/*.cpp src/*.c)

## Includes
include_directories(include)

## Output DLL
add_library(${EXEC} SHARED ${SOURCES})

## Output DIR
#set_target_properties(${EXEC}
#					  PROPERTIES
#					  CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
#					  CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
#					  CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
#)

## Library Files
target_link_libraries(${EXEC} Winmm)
