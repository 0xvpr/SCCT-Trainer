#ifndef _HACKS_HPP
#define _HACKS_HPP

#include <windows.h>
#include <tlhelp32.h>

extern uintptr_t module_base_addr;

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
         * @return void
         */
        static void Afterlife(bool bAfterlife);

        /**
         * Prevents the game from subtracting the player's HP 
         * while also enabling one shot kill for all other NPC's
         *
         * @param  bool bUnlimitedHealth
         * @return void
         */
        static void GodMode(bool bGodMode);

        /**
         * Toggles No Recoil 
         *
         * @param  bool bNoRecoil 
         * @return void 
         */
        static void GodGun(bool bNoRecoil);

        /**
         * Prevents the visibility meter from rising above 0.001. 
         *
         * Cameras WILL still see you. Enemies with night vision 
         * Enemies WILL still hear you at 0 threshhold. 

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
         * @return void 
         */
        static void UnlockAllDoors(void);
};


#endif
