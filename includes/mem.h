#ifndef MEM_H_
#define MEM_H_

#include <stdint.h>
#include <windows.h>


uintptr_t FindDMAAddress_detached(HANDLE process_handle, uintptr_t ptr, unsigned int offsets[], size_t size);

uintptr_t FindDMAAddress_attached(uintptr_t ptr, unsigned int offsets[], size_t size);

uintptr_t GetModuleBaseAddress(DWORD process_id, const char* modName);

DWORD GetProcessIdByProcessName(const char* process_name);

void Patch(char* dst, char* src, size_t size);

#endif
