#ifndef ASSEMBLY_HEADER
#define ASSEMBLY_HEADER

/* Hacking Functions */
void health_detour(void);

/* Hooking Functions */
void* hook_end_scene(void* pDevice);

/* Drawing Functions */
void drawing_draw_border_box(int x, int y, int w, int h, int thickness, unsigned color, void* d3dDevice);
void drawing_draw_filled_rect(int x, int y, int w, int h, unsigned color, void* d3dDevice);

#endif /* ASSEMBLY_HEADER */
