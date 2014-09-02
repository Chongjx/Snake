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
};

void UpdateCustom();
void GetMap();
void InputBlock();

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
void CreateMap();
void HiScore(int, string);
int GetInputMenu();

#endif // _MENU_H