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
        static void UnlimitedHealth(bool bUnlimitedHealth);

        /**
         * Prevents the game from subtracting from both: the player's 
         * current magazine, and the player's total ammunition for all 
         * weapons.
         *
         * @param  bool bUnlimitedAmmo
         * @return void
         */
        static void UnlimitedAmmo(bool bUnlimitedAmmo);

        /**
         * Prevents the visibility meter from rising above 0.001. 
         *
         * Cameras WILL still see you. Enemies with night vision 
         * WILL still drop your ass. 
         *
         * @param  bool bInvisible 
         * @return void
         */
        static void Invisibilty(bool bInvisible);

        /**
         * Prevents the sound meter from rising above 0.001. 
         *
         * Enemies WILL still hear you at 0 threshhold. 
         * WILL still drop your ass. 
         *
         * @param  bool bSilent 
         * @return void
         */
        static void Silent(bool bSilent);

        /**
         * Toggles No Recoil 
         *
         * @param  bool bNoRecoil 
         * @return void 
         */
        static void NoRecoil(bool bNoRecoil);

        /**
         * Unlock all of the doors in a level. 
         *
         * @param  void 
         * @return void 
         */
        static void UnlockAllDoors(void);
};

#endif
