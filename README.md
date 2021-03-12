# Splinter Cell Chaos Theory Trainer
  
## Overview:
This is a repository for a Splinter Cell Chaos Theory DLL that I built entirely in C.  
The only compiler I used throughout the project was mingw's <code>i686-w64-mingw32-gcc</code>  
compiler.  

I challenged myself to exclusively use <code>nvim</code> as my only 'IDE' if you will. I did not like  
the fact that most programmers on Windows seem to be confined to only being familiar  
with the <code>Visual Studio</code> ecosystem.

The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with cross platform compilation from Linux (Ubuntu 20.04 LTS)  
to Windows (10 Pro Insider Preview Build 21318.rs_prerelease.210216-1530).

## Table of Contents
  - [Demonstration](#demonstration)
  - [What I Learned](#what-i-learned)
  - [How it works](#how-it-works)
  - [Known issues](#known-issues)
  - [Goals](#Goals)
  
### Demonstration
embed YouTube or place gif.

### What I Learned
While cross compiling from Linux to Windows using <code>i686-win64-mingw32-gcc</code> isn't very well  
documented, it is certainly doable. It took a bit of research just to get the compiler to compile  
all of the various non-standard 'MS-isms' that are included in <code>Windows.h</code> and <code>tlhelp32.h</code>.

Another issue was that, since I exclusively edited the project in <code>nvim</code>, I had a ton of problems  
getting [YouCompleteMe](https://github.com/ycm-core/YouCompleteMe) to properly recognize that I was using Windows headers and give me  
auto-completion options.  

I eventually decided that I was better off just using [CoC](https://github.com/neoclide/coc.nvim) for my auto-completion desires.  
It was a hassle setting up the <code>compile_flags.txt</code> file to stop breaking [CoC](https://github.com/neoclide/coc.nvim) due to too many  
errors but I eventually got it working and I use it for most of my projects in both C & C++.

I originally planned to hook directx9 for an in-game GUI but getting mingw's ld to recognize  
<code>detours.h</code> was too much work that it was really worth so it was abandoned. It seems  
that C++ is much better suited for these types of tasks.

### How it works
Compiling the source & header files with the <code>-shared</code> option will yield an injectable DLL file.  
Use any DLL injector that you are comfortable with to inject the file into the <code>splintercell3.exe</code>.  
If the file was compile with the <code>#define DEBUG</code> define located in <code>main.c</code> set to 1, a console will  
launch when the DLL is successfully injected.

The hacks written are:
- Press <code>N</code> to toggle NoRecoil
- Press <code>I</code> to toggle PolterGheist (Invisibilty & Dead Silence)
- Press <code>G</code> to toggle PlayDead (Reduce player health to 0 without killing player)
- Press <code>Shift + K</code> to make all enemies in a level play dead.
- Press <code>Shift + T</code> to teleport to the last aim-down-sight (ADS) location.

### Known issues
I could not find a reliable 'in game' boolean value or other explicit distinction that would  
prevent the user from attempting to execute the code in places that would crash the game.  

These locations include:
- Main menu
- Multi-player menu
- All Multi-player modes
- Loading screen
- Mission select screen
- Special cases such as trying to teleport without first equipping weapon

### Goals
 - [x] Find reliable weapon pointer.
 - [ ] Find reliable entity_list pointer.
 - [ ] Find reliable player_health pointer.
 - [ ] Find 'Death' __stdcall (__thiscall maybe?).
 - [ ] Find a way to prevent PolterGheist from crashing the game.
 - [ ] Find reliable 'in game' boolean (or other explicit distinction).
