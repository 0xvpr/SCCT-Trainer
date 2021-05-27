#ifndef _UTILS_H
#define _UTILS_H

#include <stdbool.h>

extern bool bGodMode;
extern bool bGhostMode;
extern bool bSuperWeapons;
extern bool bDisableAlarms;
extern bool bDisableEnemies;

extern unsigned int total_doors_unlocked;

/**
 * Displays menu and prints the supplied text at 
 * the bottom of the menu.
 *
 * @param  const char* text
 * @return void
 */
void utils_DisplayMenu(const char* text);

/**
 * Destroys the menu and deactivates all cheats before 
 * detaching itself from the main process.
 *
 * @param  void
 * @return void
 */
void utils_Deactivate(void);


#endif
