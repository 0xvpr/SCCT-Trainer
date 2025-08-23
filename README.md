# Splinter Cell Chaos Theory Trainer
## Overview & Demonstration
The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with the Directx9c API.

My continuing efforts on the project will involve completing the following [Goals](#Goals)

### Timeline
- August 18th, 2021
  - Project started
- August 18th, 2021
  - Switch from C to C++ (11)
- August 18th, 2021
  - Project completed (ish)
- August 20th, 2021
  - Switch from CPP to C    
- December 9th, 2021
  - Project revisited
- December 7th, 2022
  - Project revisited
- August 17th, 2025
  - Project revisited AGAIN

<img src="./resources/demo.gif"/>
Demonstration of God Mode, Disable Alarms, and Disable Enemies.  
Activated cheats are highlighted in the top left in green.

## Table of Contents
- [How It Works](#how-it-works)
- [Build Instructions](#build-instructions)
- [Known Issues](#known-issues)
- [Goals](#Goals)

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
```bash
# TODO
```

## Known Issues
If the user presses F3 while the menu is minimized, it will reset position.

## Goals
- Improving the rendering capabilities of the GUI (adding text and images)
- Fix the menu resize bug.
- Create an SDK for the game for modding efforts.
- Provide design schemas and diagrams for reversed classes, objects, functions, and assets.
