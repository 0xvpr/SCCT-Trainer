#ifndef _HACKS_HPP
#define _HACKS_HPP

#include <windows.h>
#include <tlhelp32.h>

#include "entity.hpp"

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
         * @param bool bKillAll
         * @rtype void
         */
        static void KillAll(void);

        /**
         * Reduces your health to zero to simulate death state.
         * Enemies will not shoot (hit you) nor will they sound
         * alarms.
         *
         * @param bool bKillAll, int* previous_health
         * @rtype void
         */
        static void PlayDead(bool bPlayDead, int* previous_health);

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
         * Prevents the sound meter from rising above 0.001.
         *
         * Enemies WILL still hear you at 0 threshhold.
         * WILL still drop your ass.
         *
         * @param bool bSilent
         * @rtype void
         */
        static void Silent(bool bSilent);

        /* Prototype */
        static bool KillEnt(void* pThis, int arg1);
};

#endif
