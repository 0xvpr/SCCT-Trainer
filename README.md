# Splinter Cell Chaos Theory Trainer
### Timeline
- Project started: 03/12/2021
- First release: 03/14/2021 
- Final Revision: 05/14/2021

## Table of Contents
- [Demonstration](#demonstration)
- [Overview](#overview)
- [What I Learned](#what-i-learned)
- [How it works](#how-it-works)
- [Known issues](#known-issues)
- [Goals](#Goals)
- [Build Instructions](#build-instructions)
    - [Windows](#building-for-windows)
        - [CMake](#building-with-cmake)
        - [Make](#building-with-make)
        - [WSL](#building-with-wsl)
        - [Python](#building-with-script)
    - [Linux (Debian)](#building-in-linux)
        - [MinGW](#building-with-mingw)

### Demonstration ( NEEDS UPDATE )
embed YouTube or place gif.

## Overview
This is a repository for a Splinter Cell Chaos Theory DLL that I originally built entirely  
in <b>C (ISO C99)</b>. The only compiler that I used throughout the beginning of the project  
was mingw's <code>i686-w64-mingw32-gcc</code> compiler. I later added support for the Windows version  
of MinGW-gcc as well.

The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with cross platform compilation from Linux (wsl Ubuntu 20.04 LTS)  
to Windows*.

### What I Learned
<b>Visual C++ lets you get away with a lot of programming fuckery.</b>

Switching to converting the old MVSC++ code back to C99 was a pain because of the amount of  
errors that Visual Studio handled silently on its own. It was an enlightening experience.

While cross compiling from Linux to Windows using <code>i686-win64-mingw32-gcc</code> isn't as well  
documented as VisualC++ is, it is certainly doable (with serious effort). It took a bit of  
research just to get the compiler to compile all of the various non-standard 'MS-isms' that  
are included in <code>Windows.h</code> and <code>tlhelp32.h</code>.

I originally planned to hook DirectX for an internally hooked GUI, but getting mingw's ld  
to recognize <code>detours.h</code> was more work that it was really worth so it was abandoned.  
It seems that C++ is much better suited for these types of tasks anyway, so the C++ version  
supports it.

### How it works
Use any DLL injector that you are comfortable with to inject the file into the <code>splintercell3.exe</code> process.  
If you don't have a DLL injector, you can use mine <a href="https://github.com/malikrbooker/Vipers-DLL-Injector-2/releases/latest">here</a>.  
A resize-able console will pop up letting you know what hacks are available as well as their respective status.

The hacks written are:
- Press <code>Numpad 1</code> to toggle God Mode
- Press <code>Numpad 2</code> to toggle Ghost Mode
- Press <code>Numpad 3</code> to toggle Super Gun
- Press <code>Numpad 4</code> to toggle alarms
- Press <code>Numpad 5</code> to toggle enemies
- Press <code>Numpad 6</code> to unlock all doors

### Known issues
~~I could not find a reliable 'in game' boolean value or other explicit distinction that would  
prevent the user from attempting to execute the code in places that would crash the game.~~ <i>circumvented</i>

These locations include:
- ~~Special cases such as trying to teleport without first equipping weapon~~ <i>(patched May 05, 2021)</i>
- ~~Special cases such as trying to toggle no recoil without first equipping weapon~~ <i>(patched May 05, 2021)</i>

The entity list is also extremely illusive. Sometimes functions that include the EntityList Object end 
up returning NULL due to its random nature. The hacks that rely on the EntityList Object tend to work  
less reliably as multiple levels are completed.

### Goals
 - [x] Find reliable weapon pointer <i>(patched March 12, 2021)</i>
 - [x] ~~Find 'Death' __thiscall~~ <i>(removed - unnecessary)</i>
 - [x] Find a way to prevent PolterGheist from breaking the game <i>(patched May 5, 2021)</i>
 - [ ] Find reliable entity_list pointer
 - [ ] ~~Find reliable player_health pointer~~ <i>(removed - unnecessary)</i>
 - [ ] ~~Find reliable 'in game' boolean (or other explicit distinction)~~ <i>(removed - unnecessary)</i>

## Build Instructions
### Building in Windows
1. install MinGW
2. add MinGW/bin to path
3. open Powershell in project directory
```
$ make.exe
```

#### With CMake
- Visual Studio 2019
    1. open the project folder in Visual Studio 2019
    2. ctrl + shift + b
- Powershell
    1. open Powershell in project directory
    ```
    $ cmake -G "Visual Studio 2019" -A Win32 -B "build"
    $ cmake --build "build" --config "Release"
    ```

#### With Make
```
$ make
```

#### With WSL
```
$ sudo apt install mingw-w64
$ make
```

#### With Python
```
python3 build.py
```

### Building in Linux
```
$ make
```

#### References
*Windows - <i>10 Pro Insider Preview Build 21318.rs_prerelease.210216-1530)</i>
