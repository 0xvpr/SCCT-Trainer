<h1 align="center">Splinter Cell Chaos Theory Trainer</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Windows--x86-supported-00B140"/>
  <a href="https://mit-license.org/"/>
    <img src="https://img.shields.io/badge/License-MIT-00B140"/>
  </a>
  <img src="https://img.shields.io/github/actions/workflow/status/0xvpr/scct-trainer/docker_build.yml?label=Build"/>
</p>
<br>

### Timeline
- Project started:      08/18/2021
- Switch from C to CPP: 08/18/2021
- Project completed:    08/19/2021
- Switch from CPP to C: 08/20/2021
- Project revisited:    12/09/2021
- Project revisited:    12/07/2022
- Project revisited:    05/26/2023

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
#### Using WSL2 + Docker (Recommended Method)
```bash
make docker-container && make docker-build
```
#### Using own host (not recommended)
```bash
## if you need nasm and x86_64-w64-mingw32-gcc/ld and nasm
## run uncomment the following two lines
# sudo apt update && sudo apt upgrade -y --no-install-recommends
# sudo apt install make build-essential mingw-w64-common mingw-w64-i686-dev mingw-w64-tools mingw-w64 nasm
make # defaults to only make release build -> lib/sp3.dll
```

## Known Issues
If the user presses F3 while the menu is minimized, it will reset position.
