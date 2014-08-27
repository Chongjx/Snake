#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool GB_QuitGame;
extern bool GB_GameOver;

struct s_Snake
{
	COORD CharLocation;
};

void Init();			// initialize your variables, allocate memory, etc
void ShutDown();		// do clean up, free memory

enum E_KEY
{
    E_UP,
    E_DOWN,
    E_LEFT,
    E_RIGHT,
    E_NORM,
    E_COUNT
};

enum EP2_KEY
{
    EP2_W,
	EP2_S,
    EP2_A,
    EP2_D,
    EP2_NORM,
    EP2_COUNT
};

void Map();					// border around the map using 2D array
void GetInput();			// get input from player
int Update(double);			// update the game and the state of the game
void Render();				// renders the current state of the game to the console
void Timer();				// Time to spawn the special food
void Spawn();				// spawn food
void SpawnSpecial();		// spawn special food
bool CheckFood();			// check food location
bool CheckSpecialFood();	// check special food location
void CheckCollision();		// check collision of for the snake
void CreateSnake(int);		// create my snake at the intial location
int UpdateSnake();			// update the snake
void ScoreBoard();
void GG();					// reset all the variables to default values

void Map2();					// border around the map using 2D array
void GetInput2();			// get input from player
int Update2(double);			// update the game and the state of the game
void Render2();				// renders the current state of the game to the console
void Timer2();				// Time to spawn the special food
void Spawn2();				// spawn food
void SpawnSpecial2();		// spawn special food
bool CheckFood2();			// check food location
bool CheckSpecialFood2();	// check special food location
void CheckCollision2();		// check collision of for the snake
void CreateSnake2(int);		// Create my snake at the intial location
int UpdateSnake2();			// update the snake
void GG2();					// reset all the variables to default values

#endif // _GAME_H