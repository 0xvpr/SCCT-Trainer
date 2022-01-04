#ifndef _MEM_H
#define _MEM_H

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */
#include <windows.h>
#ifndef __cplusplus
#include <stdint.h>
#include <stdbool.h>
#endif /* __cplusplus */

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  uintptr_t ptr
 * @param:  unsigned offsets[]
 * @param:  size_t size
 *
 * @return: uintptr_t
**/
uintptr_t memory_find_dynamic_address(uintptr_t ptr, uint16_t* offsets, size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param:  void destination
 * @param:  void source
 * @param:  size_t size
 *
 * @return: void
**/
bool memory_patch(void* dst, void* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @param:  void* targetFunc
 * @param:  void* myFunc
 * @param:  size_t size
 *
 * @return: bool
**/
bool memory_detour(void* targetFunc, void* myFunc, size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @param:  void* src
 * @param:  void* dst
 * @param:  size_t size
 *
 * @return: char*
**/
char* memory_tramp_hook(char* targetFunc, char* myFunc, size_t size);

/**
 * Scans a given chunk of data for the given pattern and mask.
 *
 * @param:  base_addr       The base address of where the scan data is from.
 * @param:  img_size        The size of the module.
 * @param:  pattern         The pattern to scan for.
 * @param:  pattern_size    The size of the pattern to scan for.
 *
 * @return: Pointer of the pattern found, 0 otherwise.
**/
unsigned char* memory_find_pattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t pattern_size);

#endif /* _MEM_H */
