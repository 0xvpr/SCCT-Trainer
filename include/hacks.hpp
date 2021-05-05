#ifndef _HACKS_HPP
#define _HACKS_HPP

#include <windows.h>
#include <tlhelp32.h>


class Hacks
{
    public:
        /**
         * Reduces all enemies in the current level's hp 
         * to zero.
         *
         * This WILL break the game's state triggering
         * mechanics.
         *
         * @param void
         * @rtype void
         */
        static void Afterlife(bool bAfterlife);

        /**
         * Prevents the visibility meter from rising above 0.001. 
         *
         * Cameras WILL still see you. Enemies with night vision 
         * WILL still drop your ass. 
         *
         * @param bool bInvisible 
         * @rtype void
         */
        static void Invisibilty(bool bInvisible);

        /**
         * Prevents the sound meter from rising above 0.001. 
         *
         * Enemies WILL still hear you at 0 threshhold. 
         * WILL still drop your ass. 
         *
         * @param bool bSilent 
         * @rtype void
         */
        static void Silent(bool bSilent);

        /**
         * Toggles No Recoil 
         *
         * @param bool bNoRecoil 
         * @rtype void 
         */
        static void NoRecoil(bool bNoRecoil);

        /**
         * Teleports player to last Aim Down Sight Location. 
         * If weapon was never drawn, the game will instantly 
         * crash. 
         *
         * @param void 
         * @rtype void 
         */
        static void TeleportToADS(void);

        /**
         * Unlock all of the doors in a level. 
         *
         * @param void 
         * @rtype void 
         */
        static void UnlockAllDoors(void);

        /**
         * Use __thiscall to kill entities and properly destroy them. 
         * 
         * @param int* pThis, int source
         * @rtype void
         */
        static bool KillEnt(void* pThis, int source);
};

#endif
