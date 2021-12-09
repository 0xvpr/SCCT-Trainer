#ifndef _MEM_H
#define _MEM_H

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Find Dynamic Memory Address of an embedded process.
 *
 * @param: uintptr_t ptr, unsigned offsets[], size_t size
 * @rype: uintptr_t
 */
uintptr_t FindDynamicAddress(uintptr_t ptr, unsigned offsets[], size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param: BYTE* destination, BYTE* source, size_t size
 * @rype: void
 */
void Patch(BYTE* dst, BYTE* src, size_t size);

/**
 * TODO: finish comments
 */
bool Detour(void* hookedFunc, void* myFunc, int length);

/**
 * TODO: finish comments
 */
void healthDetour(void);

/**
 * TODO: finish comments
 */
bool Hook(char* src, char* dst, int len);

/**
 * TODO: finish comments
 */
char* TrampHook(char* src, char* dst, unsigned int len);

#endif /* _MEM_H */
