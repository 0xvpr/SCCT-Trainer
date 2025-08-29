#ifndef   PATCHES_HEADER
#define   PATCHES_HEADER

#include <cstdint>
#include <array>

namespace patches {
    const std::array<std::uint8_t, 6> health_original = {
        0x2B, 0xC2,                              // sub eax, edx
        0x89, 0x03,                              // mov dword ptr [ebx], eax
        0x8B, 0xD8                               // mov ebx, eax
    };

    
    constexpr std::array<std::uint8_t, 6> visibility_original = {
        0x8B, 0x86, 0x18, 0x15, 0x00, 0x00       // mov eax, dword ptr [esi + 0x1518]
    };  
    constexpr std::array<std::uint8_t, 6> visibility_patch = {
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90,                                    // nop
        0x90                                     // nop
    };


    constexpr std::array<std::uint8_t, 2> noise_original = {
        0x3B, 0xF8                               // cmp edi, eax
    };
    constexpr std::array<std::uint8_t, 2> noise_patch = {
        0x39, 0xC0                               // cmp eax, eax
    };


    constexpr std::array<std::uint8_t, 2> main_ammo_original = {
        0x4B,                                    // dec ebx
        0x4F                                     // dec edi
    }; 
    constexpr std::array<std::uint8_t, 2> main_ammo_patch=  {
        0x90,                                    // nop
        0x90                                     // nop
    };


    constexpr std::array<std::uint8_t, 14> shotgun_ammo_original = {
        0x49,                                    // dec ecx
        0x89, 0x8F, 0x1C, 0x04, 0x00, 0x00,      // mov dword ptr [esi + 0x454], eax
        0x8B, 0x8F, 0xFC, 0x03, 0x00, 0x00,      // mov eax, dword ptr [esi + 0x45C]
        0x48                                     // dec eax
    };
    constexpr std::array<std::uint8_t, 14> shotgun_ammo_patch = {
        0x90,                                    // nop
        0x89, 0x8F, 0x1C, 0x04, 0x00, 0x00,      // mov dword ptr [esi + 0x454], eax
        0x8B, 0x8F, 0xFC, 0x03, 0x00, 0x00,      // mov eax, dword ptr [esi + 0x45C]
        0x90                                     // nop
    };


    constexpr std::array<std::uint8_t, 14> sniper_ammo_original = {
        0x48,                                    // dec eax
        0x89, 0x86, 0x54, 0x04, 0x00, 0x00,      // mov dword ptr [esi + 0x454], eax
        0x8B, 0x86, 0x5C, 0x04, 0x00, 0x00,      // mov eax, dword  ptr [esi + 0x45C]
        0x48                                     // dec eax
    };
    constexpr std::array<std::uint8_t, 14> sniper_ammo_patch = {
        0x90,                                     // nop
        0x89, 0x86, 0x54, 0x04, 0x00, 0x00,       // mov [esi + 0x454], eax
        0x8B, 0x86, 0x5C, 0x04, 0x00, 0x00,       // mov eax, [esi + 0x45C]
        0x90                                      // nop
    };


    constexpr std::array<std::array<std::uint8_t, 6>, 6> recoil_originals = {{
        {{ 0xD9, 0x9E, 0x2C, 0x05, 0x00, 0x00 }}, // fstp dword ptr [esi + 0x52C]
        {{ 0xD9, 0x9E, 0x2C, 0x05, 0x00, 0x00 }}, // fstp dword ptr [esi + 0x52C]
        {{ 0xD9, 0x9E, 0x2C, 0x05, 0x00, 0x00 }}, // fstp dword ptr [esi + 0x52C]
        {{ 0xD9, 0x9E, 0x30, 0x05, 0x00, 0x00 }}, // fstp dword ptr [esi + 0x530]
        {{ 0x89, 0x96, 0x30, 0x05, 0x00, 0x00 }}, // mov  dword ptr [esi + 0x530], edx
        {{ 0x89, 0x8E, 0x34, 0x05, 0x00, 0x00 }}  // mov  dword ptr [esi + 0x534], ecx
    }};
    constexpr std::array<std::array<std::uint8_t, 6>, 6> recoil_patches = {{
        {{ 0x89, 0x8E, 0x2C, 0x05, 0x00, 0x00 }}, // mov dword ptr [esi + 0x52C], ecx
        {{ 0x89, 0x8E, 0x2C, 0x05, 0x00, 0x00 }}, // mov dword ptr [esi + 0x52C], ecx
        {{ 0x89, 0x8E, 0x2C, 0x05, 0x00, 0x00 }}, // mov dword ptr [esi + 0x52C], ecx
        {{ 0x89, 0x8E, 0x30, 0x05, 0x00, 0x00 }}, // mov dword ptr [esi + 0x530], ecx
        {{ 0x89, 0x8E, 0x30, 0x05, 0x00, 0x00 }}, // mov dword ptr [esi + 0x530], ecx
        {{ 0x89, 0xBE, 0x34, 0x05, 0x00, 0x00 }}  // mov dword ptr [esi + 0x534], edi
    }};  


    constexpr std::array<std::uint8_t, 2> rapid_fire_original = {
        0x75, 0x47                                // jne short 0x47
    };
    constexpr std::array<std::uint8_t, 2> rapid_fire_patch = {
        0x90,                                     // nop
        0x90                                      // nop
    };

    constexpr std::array<std::uint8_t, 6> alarm_original = {
        0x0F, 0x85, 0x35, 0x03, 0x00, 0x00        // jne 0x33b
    };
    constexpr std::array<std::uint8_t, 6> alarm_patch = { 
        0xE9, 0x36, 0x03, 0x00, 0x00,             // jmp 0x33b
        0x90                                      // nop
    };
} // namespace patches

#endif /* PATCHES_HEADER */
