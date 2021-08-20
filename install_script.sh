#!/usr/bin/bash

target="./build/Release/scctgui.dll"
dest="./bin/"

# Create a conditional clean
rm -fr build/**

powershell.exe -c "cmake -A Win32 -B build"
powershell.exe -c "cmake --build build --config Release"

cp $target $dest