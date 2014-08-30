#ifndef _MENU_H
#define _MENU_H

#include "Framework\timer.h"
#include <string>

using std::string;

extern WORD ChosenColour[];
extern WORD ChosenColour2[];

enum E_Colours
{
	BLUE = 1,
	CYAN,
	PURPLE,
	YELLOW,
};

enum E_Squence
{
	E_MAINMENU,
	E_GAME,
	E_INSTRUCTION,
	E_HIGHSCORE,
	E_EXIT,
	MAX_STATES
};

void MainMenu();
void Instruction();
void GameAscii();
void Game1();
void Game2();
void HighScore();
void DisplayHighScore();
void QuitGame();
void ColourOptions();
void ColourOptions2();
void MapOptions();
void MapOptions2();
void HiScore(int, string);
int GetInputMenu();

extern int I_Map;

#endif // _MENU_H