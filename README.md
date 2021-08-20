# Splinter Cell Chaos Theory Trainer
### Timeline
- Project started:      08/18/2021
- Switch from C to CPP: 08/18/2021
- Project completed:    08/19/2021
- Switch from CPP to C: 08/20/2021

## Overview & Demonstration
The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with the Directx9c API.  

<img src="./resources/demo.gif"/>
Demonstration of God Mode, Disable Alarms, and Disable Enemies.  
Activated cheats are highlighted in the top left in green.

## Table of Contents
- [What I Learned](#what-i-learned)
- [How It Works](#how-it-works)
- [Build Instructions](#build-instructions)
- [Known Issues](#known-issues)
- [Goals](#Goals)

## What I Learned
Splinter Cell Chaos Theory has a unique Directx API structure. Text can  
not be drawn, and most sprites, tools, and images can only be half drawn  
and are very poorly rendered when they are drawn.

There are more things that can be done but I've concluded that it's not  
worth the effort.

## How It Works
Use any DLL injector that you are comfortable with to inject the file into  
the <code>splintercell3.exe</code> process. 

Once the DLL is injected, you will have access to the following Hacks:
- Numpad 1: God Mode
- Numpad 2: Ghost Mode
- Numpad 3: Super Weapons
- Numpad 4: Disable Alarms
- Numpad 5: Disable Enemies
- Numpad 6: Unlock All Doors

## Build Instructions
- WSL
    1. install cmake for windows
    ```
    $ ./install_script.sh
    ```
- CMake
    1. install cmake for windows
    - Visual Studio 2019
        1. open the project folder in Visual Studio 2019
        2. ctrl + shift + b
    - Powershell
        1. open Powershell in project directory
        ```
        $ cmake -G "Visual Studio 2019" -A Win32 -B "build"
        $ cmake --build "build" --config "Release"
        ```

## Known Issues
If the user presses F3 while the menu is minimized, it will reset position.

## Goals
- [ ] ~~Find out how to draw text~~
