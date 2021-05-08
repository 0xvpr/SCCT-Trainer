#ifndef _HACKS_HPP
#define _HACKS_HPP

#include <windows.h>
#include <tlhelp32.h>

extern uintptr_t module_base_addr;
extern unsigned int total_doors_unlocked;

class Hacks
{
    public:
        /**
         * Reduces all enemies in the current level's hp 
         * to zero.
         *
         * This WILL break the game's state triggering 
         * mechanics. Toggle as needed to progress in a 
         * mission.
         *
         * @param  bool bAfterlife
         * @return (unsigned int)n_entities_changed
         */
        static unsigned int Afterlife(bool bAfterlife);

        /**
         * Prevents the game from subtracting the player's HP 
         * while also enabling one shot kill for all other NPC's
         *
         * @param  bool bGodMode
         * @return void
         */
        static void GodMode(bool bGodMode);

        /**
         * Toggles: rapid fire, infinite ammo (if previously non-zero), 
         * no recoil, no spread, 
         *
         * @param  bool bGodGun
         * @return void 
         */
        static void GodGun(bool bGodGun);

        /**
         * Prevents the visibility meter from rising above 0.001. 
         *
         * Cameras WILL still see you. Enemies with night vision 
         * Enemies WILL still hear you at 0 threshhold. 
         * 
         * Enemies WILL still drop your ass. 
         *
         * @param  bool bPolterGheist
         * @return void
         */
        static void PolterGheist(bool bInvisible);

        /**
         * Disable alarms
         *
         * @param  bDisableAlarms
         * @return void
         */
        static void DisableAlarms(bool bDisableAlarms);

        /**
         * Unlock all of the doors in a level. 
         *
         * @param  void 
         * @return (unsigned int)n_doors_unlocked
         */
        static unsigned int UnlockAllDoors(void);
};


#endif
