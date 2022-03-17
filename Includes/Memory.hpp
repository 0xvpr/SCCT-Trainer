#ifndef MEM_HEADER
#define MEM_HEADER

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif // __cplusplus

namespace memory {

/**
 * Finds the Dynamic Memory Access address of an embedded process.
 *
 * @param:  uintptr_t ptr
 * @param:  unsigned offsets[]
 * @param:  size_t size
 *
 * @return: uintptr_t
**/
[[nodiscard]]
uintptr_t find_dynamic_address(uintptr_t ptr, uint16_t* offsets, size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param:  void destination
 * @param:  void source
 * @param:  size_t size
 *
 * @return: void
**/
[[nodiscard]]
bool patch(void* dst, void* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @param:  void* targetFunc
 * @param:  void* myFunc
 * @param:  size_t size
 *
 * @return: bool
**/
[[nodiscard]]
bool detour(void* targetFunc, void* myFunc, size_t size);

/**
 * Hooks into a function and detours the target function to another function, then jumps back.
 *
 * @param:  void* src
 * @param:  void* dst
 * @param:  size_t size
 *
 * @return: char*
**/
[[nodiscard]]
char* tramp_hook(char* targetFunc, char* myFunc, size_t size);

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
[[nodiscard]]
unsigned char* find_pattern(unsigned char* base_addr, size_t img_size, unsigned char* pattern, size_t pattern_size);

} // namespace memory

#endif // MEM_HEADER
