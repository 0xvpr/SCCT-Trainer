#ifndef _HOOK_HPP
#define _HOOK_HPP

bool Detour(void* hookedFunc, void* myFunc, int length);

void healthDetour(void);

#endif
