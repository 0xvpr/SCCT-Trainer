cmake_minimum_required(VERSION 3.8)

project("sp3")
set(EXEC sp3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_library(${EXEC} SHARED ${SOURCES})
