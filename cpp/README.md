# Splinter Cell Chaos Theory Trainer

## Things Are Changing
The Repository has been translated from C to C++ for extensions of the project's current  
capabilities. This means future support for Directx9 for anyone who is willing to put in the time.

## Table of Contents
  - [Demonstration](#demonstration)
  - [Overview](#overview)
  - [What I Learned](#what-i-learned)
  - [How it works](#how-it-works)
  - [Known issues](#known-issues)
  - [Goals](#Goals)

### Demonstration ( NEEDS UPDATE )
embed YouTube or place gif.

<<<<<<< HEAD
## Overview
=======
## Overview ( NEEDS UPDATE )
>>>>>>> b4e5fbbd3d1135537f00b149288d30e3ac916757
This is a repository for a Splinter Cell Chaos Theory DLL that I originally built entirely in C.  
The only compiler I used throughout the project was mingw's <code>i686-w64-mingw32-gcc</code>  
compiler.  

I challenged myself to exclusively use <code>nvim</code> as my only 'IDE' if you will. I did not like the fact  
that most programmers on Windows seem to be confined to only being familiar with the <code>Visual Studio</code> ecosystem.

The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with cross platform compilation from Linux (Ubuntu 20.04 LTS)  
to Windows (10 Pro Insider Preview Build 21318.rs_prerelease.210216-1530).

### What I Learned ( NEEDS UPDATE )
While cross compiling from Linux to Windows using <code>i686-win64-mingw32-gcc</code> isn't very well  
documented, it is certainly doable (with serious effort). It took a bit of research just to get the compiler to compile  
all of the various non-standard 'MSVC-isms' that are included in <code>Windows.h</code> and <code>tlhelp32.h</code>.

Another issue was that, since I exclusively edited the project in <code>nvim</code>, I had a ton of problems  
getting [YouCompleteMe](https://github.com/ycm-core/YouCompleteMe) to properly recognize that I was using Windows headers and give me  
auto-completion options.  

I eventually decided that I was better off just using [CoC](https://github.com/neoclide/coc.nvim) for my auto-completion desires.  
It was a hassle setting up the <code>compile_flags.txt</code> file to stop breaking [CoC](https://github.com/neoclide/coc.nvim) due to too many  
errors but I eventually got it working and I use it for most of my projects in both C & C++.

I originally planned to hook directx9 for an in-game GUI but getting mingw's ld to recognize  
<code>detours.h</code> was more work that it was really worth so it was abandoned. It seems that C++  
is much better suited for these types of tasks.

### How it works ( NEEDS UPDATE )
Compiling the source & header files with the <code>-shared</code> option will yield an injectable DLL file.  
Use any DLL injector that you are comfortable with to inject the file into the <code>splintercell3.exe</code> process.  
a resize-able console will pop up letting you know what hacks are available as well as their respective status.

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

### Goals
 - [x] Find reliable weapon pointer <i>(patched March 12, 2021)</i>
 - [ ] Find reliable entity_list pointer
 - [ ] ~~Find reliable player_health pointer~~ <i>(removed - unnecessary)</i>
 - [x] ~~Find 'Death' __thiscall~~ <i>(removed - unnecessary)</i>
 - [x] Find a way to prevent PolterGheist from breaking the game <i>(patched May 5, 2021)</i>
 - [ ] ~~Find reliable 'in game' boolean (or other explicit distinction)~~ <i>(removed - unnecessary)</i>
