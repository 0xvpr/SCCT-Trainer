#ifndef _UTILS_HPP
#define _UTILS_HPP

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
void __displayMenu(const char* text);

/**
 * Destroys the menu and deactivates all cheats before 
 * detaching itself from the main process.
 *
 * @param  void
 * @return void
 */
void __deactivate(void);


#endif
