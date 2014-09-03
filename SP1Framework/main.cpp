// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "Framework\console.h"
#include "game.h"
#include "menu.h"

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool GB_QuitGame = false;     // Set to true if you want to quit the game
bool GB_GameOver = false;
const unsigned char FPS = 5; // FPS of this game

void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	Init();				// initialize your variables
	int I_Refresh = 1;
    playGameSound(S_INTRO);
	while(!GB_QuitGame)
	{
		MainMenu();
		GetInputMenu();
	}
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
void Game1()
{
	int I_Current = 500;
	colour (0x2);
	Map();
	Score();
	g_timer.startTimer();	// Start timer to calculate how long it takes to render this frame
	CreateSnake(1,3);
	while (!GB_GameOver)      // run this loop until user wants to quit
	{
		GetInput(1);							// get keyboard input
		I_Current = Update(1, g_timer.getElapsedTime());	// update the game
		Render(1);							 // render the graphics output to screen
		g_timer.waitUntil(I_Current/FPS);		 // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
	colour(0x2);
	if (I_Map != 6)
	{
		ScoreBoard();
	}
	GG(1);
}

void Game2()
{
	int I_Current = 500;
	colour (0x2);
	Map();
	g_timer.startTimer();	// Start timer to calculate how long it takes to render this frame
	CreateSnake(2, 3);
	while (!GB_GameOver)      // run this loop until user wants to quit
	{
		GetInput(2);							// get keyboard input
		I_Current = Update(2, g_timer.getElapsedTime());	// update the game
		Render(2);						// render the graphics output to screen
		g_timer.waitUntil(I_Current/FPS);		 // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
	GameOver();
	GG(2);
}