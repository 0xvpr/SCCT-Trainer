#ifndef HACKS_H_
#define HACKS_H_

#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

#include "entity.h"


void KillAll(bool bKillAll);

void PlayDead(bool bPlayDead, uint64_t* previous_health);

void Invisibilty(bool bInvisible);

void NoRecoil(bool bNoRecoil);

void TeleportToADS(void);

void Silent(bool bSilent);

#endif
