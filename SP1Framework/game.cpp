// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define Height 40
#define Width 100

char level[Height][Width];

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
bool gameover = false;
COORD consoleSize;
COORD position;
COORD apple;
COORD scoreplace;
int foodspawned = 0;
int score;
int current = 0;
WORD chosencolour[] = {0x7};

vector<snake> body;

int move = 5;
int prev = 0;

void init()
{
	// Set precision for floating point output
	cout << std::fixed << std::setprecision(3);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = 100;
	consoleSize.Y = 40;

	elapsedTime = 0.0;

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
	keyPressed[K_UP] = isKeyPressed(VK_UP);
	keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

int update(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	// Updating the location of the character based on the key press

	gotoXY(body[body.size()-1].charLocation);
	cout << ' ';

	// if the player press up and the snake is not moving down, the snake will move up
	if (keyPressed[K_UP] && prev != 2 && move != 5)
	{
		move = 1;
		prev = move;
	}

	// if the player press left and the snake is not moving right, the snake will move left
	else if (keyPressed[K_LEFT] && prev != 4)
	{
		move = 3;
		prev = move;
	}

	// if the player press down and the snake is not moving up, the snake will move down
	else if (keyPressed[K_DOWN] && prev != 1)
	{
		move = 2;
		prev = move;
	}

	// if the player press right and the snake is not moving left, the snake will move right
	else if (keyPressed[K_RIGHT] && prev != 3)
	{
		move = 4;
		prev = move;
	}

	// change the coordinates of the snake
	switch(move)
	{
	case up:
		for (int i = body.size()-1; i > 0 ; i--)
		{
			body[i].charLocation.X = body[i-1].charLocation.X;
			body[i].charLocation.Y = body[i-1].charLocation.Y;
		}
		body[0].charLocation.Y--;
		checkcollision();
		break;

	case down:
		for (int i = body.size()-1; i > 0 ; i--)
		{
			body[i].charLocation.X = body[i-1].charLocation.X;
			body[i].charLocation.Y = body[i-1].charLocation.Y;
		}
		body[0].charLocation.Y++;
		checkcollision();
		break;

	case left:
		for (int i = body.size()-1; i > 0 ; i--)
		{
			body[i].charLocation.X = body[i-1].charLocation.X;
			body[i].charLocation.Y = body[i-1].charLocation.Y;
		}
		body[0].charLocation.X--;
		checkcollision();
		break;

	case right:
		for (int i = body.size()-1; i > 0 ; i--)
		{
			body[i].charLocation.X = body[i-1].charLocation.X;
			body[i].charLocation.Y = body[i-1].charLocation.Y;
		}
		body[0].charLocation.X++;
		checkcollision();
		break;

	case norm:
		for (int i = body.size()-1; i > 0 ; i--)
		{
			body[i].charLocation.X = body[i-1].charLocation.X;
			body[i].charLocation.Y = body[i-1].charLocation.Y;
		}
		body[0].charLocation.Y++;
		checkcollision();
		break;
	}

	current = updatesnake();

	if (current <= 100)
	{
		return 500;
	}

	else if (current <= 200)
	{
		return 400;
	}

	else if ( current <= 400)
	{
		return 200;
	}

	else if ( current > 500)
	{
		return 100;
	}
}

void render()
{
	colour(chosencolour[0]);

	//render the game

	//render test screen code (not efficient at all)
	/*const WORD colors[] =   {
	0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	for (int i = 0; i < 12; ++i)
	{
	gotoXY(3*i,i+1);
	colour(colors[i]);
	std::cout << "WOW";
	}*/

	// render time taken to calculate this frame
	/*gotoXY(90, 0);
	colour(0x1A);
	cout << 1.0 / deltaTime << "fps" << endl;

	gotoXY(0, 0);
	colour(0x59);
	cout << elapsedTime << "secs" << endl;*/

	// render the snake
	gotoXY(body[0].charLocation);
	cout << char(254);

	gotoXY(12, 40);
	cout << score;

	// set the cursor location at the top of the screen
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition (hOut, position);
}

void map()
{
	// create a 2D array that will store the location of the snake and the food
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (col == 0 && (row != 0 && row != Height - 1))
			{
				level[row][col] = char(221);
			}

			else if (row == 0)
			{
				level[row][col] = char(220);
			}

			else if (col == Width - 1 && (row != 0 && row != Height - 1))
			{
				level[row][col] = char(222);
			}

			else if (row == Height - 1)
			{
				level[row][col] = char(223);
			}
		}
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			cout << level[row][col];
		}
	}

	scoreplace.X = 0;
	scoreplace.Y = 46;

	gotoXY(scoreplace);
	cout << "Your score: ";
}

void createsnake(int size)
{
	// Create a snake at the center of the map
	for (int i = 0; i < size; i++)
	{
		body.push_back(snake());

		body[i].charLocation.X = consoleSize.X/2;
		body[i].charLocation.Y = consoleSize.Y/4 - i;
	}
}

void spawn()
{
	srand(time(0));
	apple.X = rand() % 99 + 1;
	apple.Y = rand() % 39 + 1;

	for ( int i = 0; i < body.size(); i++)
	{
		if ( apple.X == body[i].charLocation.X && apple.Y == body[i].charLocation.Y || apple.X == 0 || apple.Y == 0 || apple.X == Width - 1 || apple.Y == Height - 1)
		{
			apple.X = rand() % 99 + 1;
			apple.Y = rand() % 39 + 1;
		}
	}

	gotoXY (apple);
	colour(0x1);
	cout << char(3);
}

int updatesnake()
{
	bool foodeaten = false;

	if (body[0].charLocation.X == apple.X && body[0].charLocation.Y == apple.Y)
	{
		Beep (1046, 100);
		foodeaten = true;
		foodspawned = 0;
		body.push_back(snake());

		body[body.size()-1].charLocation.X = body[body.size()-2].charLocation.X;
		body[body.size()-1].charLocation.Y = body[body.size()-2].charLocation.X;
		score += 10;
	}

	if (foodeaten != true && foodspawned == 0)
	{
		spawn();
		foodspawned++;
	}

	return score;
}

void checkcollision()
{
	for ( int i = 1; i < body.size(); i++)
	{
		if (body[0].charLocation.X == body[i].charLocation.X && body[0].charLocation.Y == body[i].charLocation.Y)
		{
			gameover = true;
		}
	}

	if (body[0].charLocation.X == 0 || body[0].charLocation.X == Width - 1 || body[0].charLocation.Y == 0 || body[0].charLocation.Y == Height - 1)
	{
		gameover = true;
	}
}

void colourOptions()
{
	int color = 0;

	colour(0xB);
	cout << "						1) OOOOOO" << endl;
	colour(0xC);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x7);
	cout << "					Choose your colour: ";
	cin >> color;
	cout << "						You have chosen ";
	switch (color)
	{
		case LIGHT_BLUE: colour(0xB); chosencolour[0] = 0xB;
			break;
		case RED: colour(0xC); chosencolour[0] = 0xC;
			break;
		case PINK: colour(0xD); chosencolour[0] = 0xD;
			break;
		case YELLOW: colour(0xE); chosencolour[0] = 0xE;
			break;
	}
	cout << "OOOOOO" << endl;
	colour(0x7);
}

void highscore()
{
	colour(0x02);
	cls();
	cout <<	   "                         _   _ ___ ____ _   _ ____   ____ ___  ____  _____ " << endl;
	cout <<    "                        | | | |_ _/ ___| | | / ___| / ___/ _ \\|  _ \\| ____|" << endl;
	cout <<    "                        | |_| || | |  _| |_| \\___ \\| |  | | | | |_) |  _|  " << endl;
	cout <<    "                        |  _  || | |_| |  _  |___) | |__| |_| |  _ <| |___ " << endl;
	cout <<    "                        |_| |_|___\\____|_| |_|____/ \\____\\___/|_| \\_\\_____|" << endl;
	cout << endl;
	hiscore(score);
	cout <<    "						Press the UP key to return to the main menu!" << endl;
	cout << endl;
}

void gg()
{
	move = 5;
	prev = 0;
	body.erase(body.begin(), body.begin()+body.size());
	score = 0;
	foodspawned = 0;
	gameover = false;
	current = 0;
}