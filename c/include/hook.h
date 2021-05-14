#ifndef _HOOK_H
#define _HOOK_H

#include <stdbool.h>

bool Detour(void* hookedFunc, void* myFunc, int length);

void healthDetour(void);

#endif
