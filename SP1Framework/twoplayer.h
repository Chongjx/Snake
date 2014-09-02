#ifndef _TWOPLAYER_H
#define _TWOPLAYER_H

#include "game.h"
#include <vector>

using std::vector;

void Map2();				// border around the map using 2D array
void GetInput2();			// get input from player
int Update2(double);		// update the game and the state of the game
void Render2();				// renders the current state of the game to the console
void Timer2();				// Time to spawn the special food
void Spawn2();				// spawn food
void SpawnSpecial2();		// spawn special food
void EatSnake2();			// check if the snake eats each other
void CheckCollision2();		// check collision of for the snake
void CreateSnake2(int);		// Create my snake at the intial location
void UpdateSnake2();		// update the snake
void GameOver();			// Display which players win
void GG2();					// reset all the variables to default values

void snakeEatSnake(vector<s_Snake>& s1, vector<s_Snake>& s2);

#endif // _TWOPLAYER_H