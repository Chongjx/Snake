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
extern bool GB_QuitGame;
extern bool GB_GameOver;

struct s_Snake
{
	COORD CharLocation;
};

enum E_KEY
{
    E_UP,
    E_DOWN,
    E_LEFT,
    E_RIGHT,
    E_NORM,
    E_COUNT
};

void Init();					// initialize your variables, allocate memory, etc
void GetInput();				// get input from player
int Update(double);			// update the game and the state of the game
void Render();					// renders the current state of the game to the console
void ShutDown();				// do clean up, free memory
void Map();						// border around the map using 2D array
bool CheckFood();
void Spawn();					// random food spawn
void GameLoop();				// The loop
void CheckCollision();

void CreateSnake(int);		// Create my snake at the intial location
int UpdateSnake();
void GG();
// Player 2
struct s_Snake2
{
	COORD CharLocation2;
};

enum E_KEY2
{
    E_W,
    E_S,
    E_A,
    E_D,
    E_NORM2,
    E_COUNT2
};

void Init2();					// initialize your variables, allocate memory, etc
void GetInput2();				// get input from player
int Update2(double);			// update the game and the state of the game
void ShutDown2();				// do clean up, free memory
bool CheckFood2();
void GameLoop2();				// The loop
void CheckCollision2();

void CreateSnake2(int);		// Create my snake at the intial location
int UpdateSnake2();
void GG2();

#endif // _GAME_H