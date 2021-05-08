#ifndef _HOOK_H
#define _HOOK_H


bool Detour(void* hookedFunc, void* myFunc, int length);

void healthDetour(void);

#endif
