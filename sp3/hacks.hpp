#ifndef HACKS_HEADER
#define HACKS_HEADER

#include <cstdint>

constexpr std::uint32_t GOD_MODE         = 0x00000000;
constexpr std::uint32_t GHOST_MODE       = 0x00000001;
constexpr std::uint32_t SUPER_WEAPONS    = 0x00000002;
constexpr std::uint32_t DISABLE_ALARMS   = 0x00000003;
constexpr std::uint32_t DISABLE_ENEMIES  = 0x00000004;
constexpr std::uint32_t UNLOCK_ALL_DOORS = 0x00000005;
constexpr std::uint32_t MAX_MENU_ITEMS   = 0x00000006;

constexpr std::uint32_t DOOR_ALL_ACCESS  = 0x00000004;

constexpr std::uint32_t PLAYER           = 0x110E8B50;
constexpr std::uint32_t DOOR             = 0x110FDDD8;
constexpr std::uint32_t NPC              = 0x110F88D8;

namespace hacks {

/**
 * @brief        Enables or disables "God Mode" for the player.
 *
 * @description  When enabled, the player will not lose health, while all NPCs 
 *               can be defeated in a single hit. This effectively grants the 
 *               player invulnerability and offensive superiority.
 *
 * @param[in]    state (bool) Set to true to enable God Mode, false to disable it.
 *
 * @return       void
**/
void god_mode(bool state);

/**
 * @brief        Prevents the visibility meter from rising above 0.001. 
 *
 * @description  Cameras WILL still see you.
 *               Enemies with night vision may still see you.
 *               Enemies WILL still hear you at 0 threshhold. 
 *
 * @param[in]    state (bool) Set to true to enable Ghost Mode, false to disable it.
 *
 * @return void
**/
void ghost_mode(bool state);

/**
 * Toggles: rapid fire, infinite ammo (if previously non-zero), 
 * no recoil, no spread, 
 *
 * @param  bool state
 * @return void 
 */
void super_weapons(bool state);

/**
 * Disable alarms
 *
 * @param  bDisableAlarms
 * @return void
 */
void disable_alarms(bool state);

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
unsigned int disable_enemies(bool state);

/**
 * Unlock all of the doors in a level. 
 *
 * @param  void 
 * @return (unsigned int)n_doors_unlocked
 */
unsigned int unlock_all_doors();

} // namespace hacks

#endif /* HACKS_HEADER */
