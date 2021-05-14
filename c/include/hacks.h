#ifndef _HACKS_H
#define _HACKS_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

extern uintptr_t module_base_addr;
extern unsigned int total_doors_unlocked;

/**
 * Prevents the game from subtracting the player's HP 
 * while also enabling one shot kill for all other NPC's
 *
 * @param  bool bGodMode
 * @return void
 */
 void hacks_GodMode(bool bGodMode);

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
 void hacks_GhostMode(bool bInvisible);

/**
 * Toggles: rapid fire, infinite ammo (if previously non-zero), 
 * no recoil, no spread, 
 *
 * @param  bool bSuperWeapons
 * @return void 
 */
 void hacks_SuperWeapons(bool bSuperWeapons);

/**
 * Disable alarms
 *
 * @param  bDisableAlarms
 * @return void
 */
 void hacks_DisableAlarms(bool bDisableAlarms);

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
 unsigned int hacks_DisableEnemies(bool bDisableEnemies);

/**
 * Unlock all of the doors in a level. 
 *
 * @param  void 
 * @return (unsigned int)n_doors_unlocked
 */
 unsigned int hacks_UnlockAllDoors(void);


#endif
