#ifndef HACKS_HEADER
#define HACKS_HEADER

#include "Render.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif // __cplusplus

using render::HackItem;

constexpr uint16_t GOD_MODE         = 0;
constexpr uint16_t GHOST_MODE       = 1;
constexpr uint16_t SUPER_WEAPONS    = 2;
constexpr uint16_t DISABLE_ALARMS   = 3;
constexpr uint16_t DISABLE_ENEMIES  = 4;
constexpr uint16_t UNLOCK_ALL_DOORS = 5;
constexpr uint16_t MAX_MENU_ITEMS   = 6;

constexpr uint32_t DOOR_ALL_ACCESS  = 4;

constexpr uint32_t PLAYER           = 0x110E8B50;
constexpr uint32_t DOOR             = 0x110FDDD8;
constexpr uint32_t NPC              = 0x110F88D8;

namespace hacks {

/**
 * Prevents the game from subtracting the player's HP 
 * while also enabling one shot kill for all other NPC's
 *
 * @param  bool bGodMode
 * @return void
 */
void GodMode(HackItem& item);

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
void GhostMode(HackItem& item);

/**
 * Toggles: rapid fire, infinite ammo (if previously non-zero), 
 * no recoil, no spread, 
 *
 * @param  bool bSuperWeapons
 * @return void 
 */
void SuperWeapons(HackItem& item);

/**
 * Disable alarms
 *
 * @param  bDisableAlarms
 * @return void
 */
void DisableAlarms(HackItem& item);

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
[[nodiscard]]
uint16_t DisableEnemies(HackItem& item);

/**
 * Unlock all of the doors in a level. 
 *
 * @param  void 
 * @return (unsigned int)n_doors_unlocked
 */
[[nodiscard]]
uint16_t UnlockAllDoors(HackItem& item);

} // namespace hacks

#endif // HACKS_HEADER
