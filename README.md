# Splinter Cell Chaos Theory Trainer
  
### Overview:
This is a repository for a Splinter Cell Chaos Theory DLL that I built entirely in C.  
The only compiler I used throughout the project was mingw's i686-w64-mingw32-gcc compiler.  

The main purpose of this project was to get familiar with the C language while also  
familiarizing myself with cross platform compilation from Linux (Ubuntu 20.04 LTS)  
to Windows (10 Pro Insider Preview Build 21318.rs_prerelease.210216-1530).

### Table of Contents
  - [Demonstration](#demonstration)
  - [What I Learned](#what-i-learned)
  - [How it works](#how-it-works)
  - [Known issues](#known-issues)
  - [Goals](#Goals)
  
  
  
#### Demonstration
embed youtube or place gif.

#### What I Learned
While cross compiling from Linux to Windows using <code>i686-win64-mingw32-gcc</code> isn't very well documented, it is  
certainly doable. It took a bit of research just to get the compiler to compile  
all of the various non-standard 'MS-isms' that are included in <code>windows.h</code> and <code>tlhelp32.h</code>.

Another issue was that I exclusively edited the project in <code>nvim</code>


#### How it works
It doesn't... from time to time at least.

#### Known issues
The game is 15 years old and I'm having trouble defeating it.

#### Goals
 - [x] Find reliable weapon pointer
 - [ ] Find reliable entity_list pointer
 - [ ] Find reliable player_health pointer
 - [ ] Find 'Death' __stdcall (__thiscall maybe?).
 - [ ] Find a way to prevent PolterGheist from crashing the game.
