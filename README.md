# Splinter Cell Chaos Theory Trainer
### Timeline
- Project started:      08/18/2021
- Switch from C to CPP: 08/18/2021
- Project completed:    08/19/2021
- Switch from CPP to C: 08/20/2021
- Project revisited:    12/09/2021
- Project revisited:    03/17/2022
- Switch from C to CPP: 03/17/2022

## Overview & Demonstration
The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with the Directx9c API.  

This time around, I've learned more about using compilers and linkers as well as  
more things about C++ in general. (most of the C++ features will not be used anyway)

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
MinGW-w64's LD is terribly documented.

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

## Build Instructions (Debian)
#### Toolchain
```bash
sudo ./install-toolchain.sh # Modify it as you please before executing
```
#### Build
```bash
make # defaults to both release and debug builds
```

## Known Issues
If the user presses F3 while the menu is minimized, it will reset position.
