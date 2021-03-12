#ifndef OFFSETS_H_
#define OFFSETS_H_

unsigned int weapon_offsets[3]      = { 0x84, 0x6E0, 0x434 };
unsigned int entity_list_offsets[2] = { 0x78, 0x5E4 };
unsigned int cam_offsets[2]         = { 0xC8, 0x7CC };
unsigned int player_hp_offsets[1]   = { 0x84 };

size_t weapon_offsets_size			= sizeof(weapon_offsets) / sizeof(int);
size_t entity_list_offsets_size		= sizeof(entity_list_offsets) / sizeof(int);
size_t player_hp_offsets_size		= sizeof(player_hp_offsets_size) / sizeof(int);
size_t cam_offsets_size				= sizeof(weapon_offsets) / sizeof(int);

#endif
