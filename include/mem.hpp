#ifndef MEM_H_
#define MEM_H_

#include <cstdint>
#include <windows.h>

class Memory
{
    public:
        /*
         * Returns the main entry point of a foreign executable.
         */
        uintptr_t static GetModuleBaseAddress(DWORD process_id, const char* modName);

        /*
         * Find Dynamic Memory Address of a foreign process.
         */
        uintptr_t static FindDMAddress(HANDLE process_handle, uintptr_t ptr, unsigned offsets[], size_t size);

        /*
         * Find Dynamic Memory Address of an embedded process.
         */
        uintptr_t static FindDMAddress(uintptr_t ptr, unsigned int offsets[], size_t size);

        /*
         * Get the process ID by using the processes name.
         */
        DWORD static GetProcessIdByProcessName(const char* process_name);

        /*
         * Detour any given function that has a minimum op length
         * of 5. Anything less will return false.
         */
        bool static Hook(void* hookedFunc,void* myFunc, int length);

        /*
         * Byte replacement from source to destination.
         */
        void static Patch(BYTE* dst, BYTE* src, size_t size);
};

#endif
