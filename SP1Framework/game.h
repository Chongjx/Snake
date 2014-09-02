#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <vector>

using std::vector;

#define Height 40
#define Width 100

struct s_Snake
{
	COORD CharLocation;
};

bool operator ==(COORD const& lhs, COORD const& rhs);

void Init();			// initialize your variables, allocate memory, etc

enum E_Map
{
    E_MAPUP,
    E_MAPDOWN,
    E_MAPLEFT,
    E_MAPRIGHT,
	E_MAPESCAPE,
    E_MAPCOUNT
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

enum EP2_KEY
{
    EP2_W,
	EP2_S,
    EP2_A,
    EP2_D,
    EP2_NORM,
    EP2_COUNT
};

void UpdateCustom();
void GetMap();
void InputBlock();
void Map();					// border around the map using 2D array
void GetInput();			// get input from player
int Update(double);			// update the game and the state of the game
void Render();				// renders the current state of the game to the console
void Timer();				// Time to spawn the special food
void Spawn();				// spawn food
void SpawnSpecial();		// spawn special food
void CheckCollision();		// check collision of for the snake
void CreateSnake(int);		// create my snake at the intial location
void UpdateSnake();			// update the snake
void ScoreBoard();
void GG();					// reset all the variables to default values
void ClearCustomMap();

extern StopWatch g_timer;
extern bool GB_QuitGame;
extern bool GB_GameOver;
extern double elapsedTime;
extern double deltaTime;
extern COORD coord_Apple;
extern COORD coord_Special;
extern int I_Food;
extern int I_Special;
extern int I_Move;
extern int I_Prev;
extern int I_Current;
extern int I_Bonus;
extern double D_FoodTimer;
extern double D_Time;
extern char **Array_2D;
extern bool KeyPressed[E_COUNT];
extern vector<s_Snake> Vs_P1;

extern int I_Move2;
extern int I_Prev2;
extern bool KeyPressed2[EP2_COUNT];
extern vector<s_Snake> Vs_P2;

#endif // _GAME_H