#ifndef _MEM_H
#define _MEM_H

#include <windows.h>
#include <stdint.h>


/**
 * Returns the main entry point of a foreign executable.
 *
 * @param: DWORD process_id, const char* modName
 * @rtype: uintptr_t
 */
 uintptr_t GetModuleBaseAddress(DWORD process_id, const char* modName);

/**
 * Find Dynamic Memory Address of a foreign process.
 *
 * @param: HANDLE pHandle, uintptr_t ptr, unsigned offsets[], size_t size
 * @rype: uintptr_t
 */
 uintptr_t FindDMAddress_detached(HANDLE process_handle, uintptr_t ptr, unsigned offsets[], size_t size);

/**
 * Find Dynamic Memory Address of an embedded process.
 *
 * @param: uintptr_t ptr, unsigned offsets[], size_t size
 * @rype: uintptr_t
 */
 uintptr_t FindDMAddress_attached(uintptr_t ptr, unsigned offsets[], size_t size);

/**
 * Get the process ID by using the processes name.
 * 
 * @param: uintptr_t ptr, unsigned offsets[], size_t size
 * @rype: uintptr_t
 */
 DWORD GetProcessIdByProcessName(const char* process_name);

/**
 * Detour any given function that has a minimum op length
 * of 5. Anything less will return false.
 * 
 * @param: void* hookedFunc, void* myFunc, size_t size
 * @rype: bool
 */
 BOOL Hook(BYTE* dst, BYTE* src, size_t size);

/**
 * Trampoline hooks any given function that has a minimum op length
 * of 5. Anything less will return false.
 * 
 * @param: void* hookedFunc, void* myFunc, size_t size
 * @rype: BYTE*
 */
 BYTE* TrampolineHook(BYTE* hookedFunc, BYTE* myFunc, size_t size);

/**
 * Byte replacement from source to destination.
 *
 * @param: BYTE* destination, BYTE* source, size_t size
 * @rype: void
 */
 void Patch(BYTE* dst, BYTE* src, size_t size);

#endif
