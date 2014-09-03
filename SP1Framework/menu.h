#ifndef _MENU_H
#define _MENU_H

#include "Framework\timer.h"
#include <string>

using std::string;

extern WORD ChosenColour[];
extern WORD ChosenColour2[];

extern int I_Map;
extern bool B_Complete;

enum E_Colours
{
	BLUE = 1,
	CYAN,
	PURPLE,
	YELLOW,
	MAX
};

enum E_Map
{
    E_MAPUP,
    E_MAPDOWN,
    E_MAPLEFT,
    E_MAPRIGHT,
	E_MAPESCAPE,
    E_MAPCOUNT
};

void UpdateCustom();			// update the custom map
void GetMap();					// move the user coord to the respective location
void InputBlock();				// get the user input for the custom map

void MainMenu();
void Instruction();
void GameAscii();
void Game1();
void Score();
void Game2();
void HighScore();
void DisplayHighScore();
void QuitGame();
void ColourOptions();
void ColourOptions2();
void MapOptions();
void CreateMap();
void HiScore(int, string);
void GetInputMenu();
void CallMenu();
void FlushInput();

#endif // _MENU_H