#ifndef MEM_HEADER
#define MEM_HEADER

#include <stdint.h>

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
 * @param:  size_t size
 *
 * @return: void
**/
void memory_nop(void* dst, size_t nmemb);

/**
 * Byte replacement from source to destination.
 *
 * @param:  void destination
 * @param:  void source
 * @param:  size_t size
 *
 * @return: void
**/
void memory_patch(void* dst, const void* src, size_t size);

/**
 * Hooks into a function and detours the target function to another function.
 *
 * @param:  void* targetFunc
 * @param:  void* myFunc
 * @param:  size_t size
 *
 * @return: bool
**/
/*__attribute__((always_inline))*/
int memory_detour(void* targetFunc, void(* myFunc)(), size_t size);

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

#endif /* MEM_HEADER */
