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

enum SoundType
{
    S_POWERUP,
    S_POWERDOWN,
    S_FOOD,
    S_INTRO,
    S_GAMEOVER,
    S_CHOICE,
    S_COUNT
};

void playGameSound(SoundType);	// contains all the sound

void Map();					// border around the map using 2D array
void GetInput(int numplayers);			// get input from player
int Update(int numplayers, double);		// update the game and the state of the game
void Render(int numplayers);			// renders the current state of the game to the console
void Timer(int numplayers);				// Time to spawn the special food
void Spawn(int numplayers);				// spawn food
void SpawnSpecial(int numplayers);		// spawn special food
void CheckCollision(int numplayers);		// check collision of for the snake
void OneHitsWall();
void OneEatsSelf();
void TwoHitsWall();
void TwoEatsSelf();
void Head2Head();
void P1Lose();
void P2Lose();
void BothLose();
void SnakeEatSnake(vector<s_Snake>& predator, vector<s_Snake>& prey);
void CreateSnake(int numplayers, int size);		// create my snake at the intial location
void EatFood(int numplayers);
void EatSpecialFood(int numplayers);
void ScoreBoard();
void GG(int);					// reset all the variables to default values
void GameOver();
void ClearCustomMap();
void ResetMove(int numplayers);

extern StopWatch g_timer;
extern bool GB_QuitGame;
extern bool GB_GameOver;

#endif // _GAME_H