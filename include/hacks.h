#ifndef _HACKS_H
#define _HACKS_H

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>

#define GOD_MODE         0x00000000
#define GHOST_MODE       0x00000001
#define SUPER_WEAPONS    0x00000002
#define DISABLE_ALARMS   0x00000003
#define DISABLE_ENEMIES  0x00000004
#define UNLOCK_ALL_DOORS 0x00000005
#define MAX_MENU_ITEMS   0x00000006

#define DOOR_ALL_ACCESS  0x00000004

#define PLAYER           0x110E8B50
#define DOOR             0x110FDDD8
#define NPC              0x110F88D8

/**
 * Prevents the game from subtracting the player's HP 
 * while also enabling one shot kill for all other NPC's
 *
 * @param  bool bGodMode
 * @return void
 */
void hack_GodMode(bool bGodMode);

/**
 * Prevents the visibility meter from rising above 0.001. 
 *
 * Cameras WILL still see you. Enemies with night vision 
 * Enemies WILL still hear you at 0 threshhold. 
 * 
 * Enemies WILL still drop your ass. 
 *
 * @param  bool bGhostMode
 * @return void
 */
void hack_GhostMode(bool bInvisible);

/**
 * Toggles: rapid fire, infinite ammo (if previously non-zero), 
 * no recoil, no spread, 
 *
 * @param  bool bSuperWeapons
 * @return void 
 */
void hack_SuperWeapons(bool bSuperWeapons);

/**
 * Disable alarms
 *
 * @param  bDisableAlarms
 * @return void
 */
void hack_DisableAlarms(bool bDisableAlarms);

/**
 * Reduces all enemies in the current level's hp 
 * to zero.
 *
 * This WILL break the game's state triggering 
 * mechanics. Toggle as needed to progress in a 
 * mission.
 *
 * @param  bool bDisableEnemies
 * @return (unsigned int)n_entities_changed
 */
unsigned int hack_DisableEnemies(bool bDisableEnemies);

/**
 * Unlock all of the doors in a level. 
 *
 * @param  void 
 * @return (unsigned int)n_doors_unlocked
 */
unsigned int hack_UnlockAllDoors(void);

#endif /* _HACKS_H */
