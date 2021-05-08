#ifndef _UTILS_HPP
#define _UTILS_HPP

extern bool bGodGun;
extern bool bGodMode;
extern bool bAfterlife;
extern bool bPolterGheist;
extern bool bDisableAlarms;

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
