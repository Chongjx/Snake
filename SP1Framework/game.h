#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

//g_ global
//b_boolean
//i_int
//f_float
//s_ static
//c _ constant
extern StopWatch g_timer;
extern bool g_bQuitGame;
extern bool gameover;

struct snake
{
	COORD charLocation;
};

enum ECOLOR
{
	E_LIGHT_BLUE = 1,
	RED,
	PINK,
	YELLOW,
	COLOR_MAX 
};

enum EKEY
{
    E_UP,
    E_DOWN,
    E_LEFT,
    E_RIGHT,
    E_ESCAPE,
    E_COUNT
};

enum direction
{
	E_DIRECTION_UP = 1,
	down,
	left,
	right,
	norm
};

enum ESQUENCE
{
	E_MAINMENU,
	GAME,
	INSTRUCTION,
	HIGHSCORE,
	EXIT,
	MAX_STATES
};

void init();					// initialize your variables, allocate memory, etc
void getInput();				// get input from player
int update(double dt);			// update the game and the state of the game
void render();					// renders the current state of the game to the console
void shutdown();				// do clean up, free memory
void map();						// border around the map using 2D array
void spawn();					// random food spawn
void gameLoop();				// The loop
void hiscore(int);				// Highscore system
void checkcollision();

void MainMenu();				// Main menu screen
void Instruction();				// Into the instruction for user
void game();					// Into the game
void highscore();				// Into the highscore
void quitGame();				// Quit the game
void createsnake(int size);		// Create my snake at the intial location
int updatesnake();
void gg();
void colourOptions();
void options();

#endif // _GAME_H