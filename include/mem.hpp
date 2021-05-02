#ifndef _MEM_HPP
#define _MEM_HPP

#include <windows.h>

class Memory
{
    public:
        /**
         * Returns the main entry point of a foreign executable.
         *
         * @param: DWORD process_id, const char* modName
         * @rtype: uintptr_t
         */
        static uintptr_t GetModuleBaseAddress(DWORD process_id, const char* modName);

        /**
         * Find Dynamic Memory Address of a foreign process.
         *
         * @param: HANDLE pHandle, uintptr_t ptr, unsigned offsets[], size_t size
         * @rype: uintptr_t
         */
        static uintptr_t FindDMAddress(HANDLE process_handle, uintptr_t ptr, unsigned offsets[], size_t size);

        /**
         * Find Dynamic Memory Address of an embedded process.
         *
         * @param: uintptr_t ptr, unsigned offsets[], size_t size
         * @rype: uintptr_t
         */
        static uintptr_t FindDMAddress(uintptr_t ptr, unsigned offsets[], size_t size);

        /**
         * Get the process ID by using the processes name.
         * 
         * @param: uintptr_t ptr, unsigned offsets[], size_t size
         * @rype: uintptr_t
         */
        static DWORD GetProcessIdByProcessName(const char* process_name);

        /**
         * Detour any given function that has a minimum op length
         * of 5. Anything less will return false.
         * 
         * @param: void* hookedFunc, void* myFunc, size_t size
         * @rype: bool
         */
        static BOOL Hook(BYTE* dst, BYTE* src, size_t size);

        /**
         * Trampoline hooks any given function that has a minimum op length
         * of 5. Anything less will return false.
         * 
         * @param: void* hookedFunc, void* myFunc, size_t size
         * @rype: BYTE*
         */
        static BYTE* TrampolineHook(BYTE* hookedFunc, BYTE* myFunc, size_t size);

        /**
         * Byte replacement from source to destination.
         *
         * @param: BYTE* destination, BYTE* source, size_t size
         * @rype: void
         */
        static void Patch(BYTE* dst, BYTE* src, size_t size);
};

#endif
