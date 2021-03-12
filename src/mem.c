#include <windows.h>
#include <tlhelp32.h>


DWORD GetProcessIdByProcessName(const char* process_name)
{
	PROCESSENTRY32 process_entry = { sizeof(PROCESSENTRY32) };
	HANDLE processes_snapshot;
	DWORD process_id = 0;

	processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(processes_snapshot, &process_entry))
	{
		do
		{
			if (!strcmp(process_entry.szExeFile, process_name))
			{
				process_id = process_entry.th32ProcessID;
				break;
			}
		} while (Process32Next(processes_snapshot, &process_entry));
	}

	CloseHandle(processes_snapshot);

	return process_id;
}

uintptr_t GetModuleBaseAddress(DWORD process_id, const char* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE processess_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
	if (processess_snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(processess_snapshot, &modEntry))
		{
			do
			{
				if (!strcmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(processess_snapshot, &modEntry));

		}

	}
	
	CloseHandle(processess_snapshot);
	return modBaseAddr;
}

uintptr_t FindDMAAddress_detached(HANDLE process_handle, uintptr_t ptr, unsigned int offsets[], size_t size)
{
	uintptr_t addr = ptr;

	for (size_t i = 0; i < size; i++)
	{
		ReadProcessMemory(process_handle, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}

	return addr;
}

uintptr_t FindDMAAddress_attached(uintptr_t ptr, unsigned int offsets[], size_t size)
{
	uintptr_t addr = ptr;
	for (size_t i = 0; i < size; i++)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}

	return addr;
}

void Patch(char* dst, char* src, size_t size)
{
		DWORD old_protect;

		VirtualProtect(dst, size, PAGE_EXECUTE_WRITECOPY, &old_protect);
		memcpy(dst, src, size); 
		VirtualProtect(dst, size, old_protect, NULL);
}
