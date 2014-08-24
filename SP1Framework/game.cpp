// This is the main file for the game logic and function
//
//
#include "game.h"
#include "menu.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

#define Height 40
#define Width 100

double elapsedTime;
double deltaTime;
COORD coord_ConsoleSize;
COORD coord_Apple;
int I_Food = 0;
int I_Score;
int I_Current;
int I_Move;
int I_Prev;
char **Array_2D;
bool KeyPressed[E_COUNT];

WORD ChosenColour[] = {0x7};

vector<s_Snake> Vs_Body;

void Init()
{
	// Set precision for floating point output
	cout << std::fixed << std::setprecision(3);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	coord_ConsoleSize.X = 100;
	coord_ConsoleSize.Y = 40;

	elapsedTime = 0.0;

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	I_Move = 4;
	I_Prev = 0;
}

void ShutDown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void GetInput()
{    
	KeyPressed[E_UP] = isKeyPressed(VK_UP);
	KeyPressed[E_DOWN] = isKeyPressed(VK_DOWN);
	KeyPressed[E_LEFT] = isKeyPressed(VK_LEFT);
	KeyPressed[E_RIGHT] = isKeyPressed(VK_RIGHT);
}

int Update(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	// Updating the location of the character based on the key press

	gotoXY(Vs_Body[Vs_Body.size()-1].CharLocation);
	cout << ' ';

	// if the player press up and the snake is not moving down, the snake will move up
	if (KeyPressed[E_UP] && I_Prev != 1 && I_Move != 4)
	{
		I_Move = 0;
		I_Prev = I_Move;
	}

	// if the player press down and the snake is not moving up, the snake will move down
	else if (KeyPressed[E_DOWN] && I_Prev != 0)
	{
		I_Move = 1;
		I_Prev = I_Move;
	}

	// if the player press left and the snake is not moving right, the snake will move left
	else if (KeyPressed[E_LEFT] && I_Prev != 3)
	{
		I_Move = 2;
		I_Prev = I_Move;
	}

	// if the player press right and the snake is not moving left, the snake will move right
	else if (KeyPressed[E_RIGHT] && I_Prev != 2)
	{
		I_Move = 3;
		I_Prev = I_Move;
	}

	// change the coordinates of the snake
	switch(I_Move)
	{
	case E_UP:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.Y--;
		CheckCollision();
		break;

	case E_DOWN:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.Y++;
		CheckCollision();
		break;

	case E_LEFT:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.X--;
		CheckCollision();
		break;

	case E_RIGHT:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.X++;
		CheckCollision();
		break;

	case E_NORM:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.Y++;
		CheckCollision();
		break;
	}

	I_Current = UpdateSnake();

	if (I_Current <= 100)
	{
		return 500;
	}

	else if (I_Current <= 200)
	{
		return 400;
	}

	else if (I_Current <= 400)
	{
		return 200;
	}

	else if (I_Current > 500)
	{
		return 100;
	}
}

void Render()
{
	colour(ChosenColour[0]);

	//render the game

	// render the snake
	gotoXY(Vs_Body[0].CharLocation);
	cout << char(254);

	gotoXY(12, 40);
	cout << I_Score;

	COORD coord_Position;
	// set the cursor location at the top of the screen
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	coord_Position.X = 0;
	coord_Position.Y = 0;
	SetConsoleCursorPosition (hOut, coord_Position);
}

void Map()
{
	COORD coord_Scoreplace;
	// create a 2D array that will store the location of the snake and the food
	ifstream PrintMap;

	Array_2D = new char*[40];

	PrintMap.open("Map\\Original.txt");

	for (int row = 0; row < Height; row++)
	{
		Array_2D[row] = new char[100];
		for (int col = 0; col < Width; col++)
		{
			{
				PrintMap >> Array_2D[row][col];
			}
		}
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (Array_2D[row][col] == '1')
			{
				cout << char(178);
			}

			else
			{
				cout << char(32);
			}
		}
	}

	coord_Scoreplace.X = 0;
	coord_Scoreplace.Y = 45;

	gotoXY(coord_Scoreplace);
	cout << "Your score: ";

	PrintMap.close();
}

void CreateSnake(int size)
{
	// Create a snake at the center of the map
	for (int i = 0; i < size; i++)
	{
		Vs_Body.push_back(s_Snake());

		Vs_Body[i].CharLocation.X = coord_ConsoleSize.X/2;
		Vs_Body[i].CharLocation.Y = coord_ConsoleSize.Y/4 - i;
	}
}

void Spawn()
{
	bool B_CheckLocation = false;

	while(B_CheckLocation == false)
	{
		B_CheckLocation = CheckFood();
	}

	if (B_CheckLocation == true)
	{
		gotoXY (coord_Apple);
		colour(0x7);
		cout << char(3);
	}
}

bool CheckFood()
{
	bool B_Check;
	srand(time(0));
	coord_Apple.X = rand() % 99 + 1;
	coord_Apple.Y = rand() % 39 + 1;
	
	for ( int i = 0; i < Vs_Body.size(); i++)
	{
		if (coord_Apple.X == Vs_Body[i].CharLocation.X && coord_Apple.Y == Vs_Body[i].CharLocation.Y)
		{
			B_Check = false;
		}

		else if ( Array_2D[coord_Apple.Y][coord_Apple.X] == '1')
		{
			B_Check = false;
		}
	
		else
		{
			B_Check = true;
		}
	}

	return B_Check;
}

int UpdateSnake()
{
	bool B_FoodEaten = false;

	if (Vs_Body[0].CharLocation.X == coord_Apple.X && Vs_Body[0].CharLocation.Y == coord_Apple.Y)
	{
		Beep (1046, 100);
		B_FoodEaten = true;
		I_Food = 0;
		Vs_Body.push_back(s_Snake());

		Vs_Body[Vs_Body.size()-1].CharLocation.X = Vs_Body[Vs_Body.size()-2].CharLocation.X;
		Vs_Body[Vs_Body.size()-1].CharLocation.Y = Vs_Body[Vs_Body.size()-2].CharLocation.X;
		I_Score += 10;
	}

	if (B_FoodEaten != true && I_Food == 0)
	{
		Spawn();
		I_Food++;
	}

	return I_Score;
}

void CheckCollision()
{
	for ( int i = 1; i < Vs_Body.size(); i++)
	{
		if (Vs_Body[0].CharLocation.X == Vs_Body[i].CharLocation.X && Vs_Body[0].CharLocation.Y == Vs_Body[i].CharLocation.Y)
		{
			GB_GameOver = true;
		}
	}

	if (Vs_Body[0].CharLocation.X == 0 || Vs_Body[0].CharLocation.X == Width - 1)
	{
		GB_GameOver = true;
	}

	else if (Vs_Body[0].CharLocation.Y == 0 || Vs_Body[0].CharLocation.Y == Height - 1)
	{
		GB_GameOver = true;
	}

	if ( GB_GameOver == true)
	{
		gotoXY(Vs_Body[0].CharLocation);
		{
			colour(0xC);
			cout << char(254);
			Sleep(1000);
		}
	}
}

void ColorOptions()
{
	int I_Color = 0;

	colour(0xB);
	cout << "						1) OOOOOO" << endl;
	colour(0xA);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x7);
	cout << "					Choose your colour: ";
	cin >> I_Color;
	cout << "						You have chosen ";
	switch (I_Color)
	{
	case E_LIGHTBLUE: colour(0xB); 
		ChosenColour[0] = 0xB;
		break;
	case E_GREEN: colour(0xA);
		ChosenColour[0] = 0xC;
		break;
	case E_PINK: colour(0xD);
		ChosenColour[0] = 0xD;
		break;
	case E_YELLOW: colour(0xE);
		ChosenColour[0] = 0xE;
		break;
	default : colour(0x7);
		ChosenColour[0] = 0x7;
		break;
	}
	cout << "OOOOOO" << endl;
	colour(0x7);
}

void HighScore()
{
	colour(0x02);
	cls();
	cout <<	   "                         _   _ ___ ____ _   _ ____   ____ ___  ____  _____ " << endl;
	cout <<    "                        | | | |_ _/ ___| | | / ___| / ___/ _ \\|  _ \\| ____|" << endl;
	cout <<    "                        | |_| || | |  _| |_| \\___ \\| |  | | | | |_) |  _|  " << endl;
	cout <<    "                        |  _  || | |_| |  _  |___) | |__| |_| |  _ <| |___ " << endl;
	cout <<    "                        |_| |_|___\\____|_| |_|____/ \\____\\___/|_| \\_\\_____|" << endl;
	cout << endl;
	HiScore(I_Score);
	cout <<    "				Press the UP key to return to the main menu!" << endl;
	cout << endl;
}

void GG()
{
	I_Move = 4;
	I_Prev = 0;
	I_Current = 0;
	I_Score = 0;
	I_Food = 0;
	Vs_Body.erase(Vs_Body.begin(), Vs_Body.begin()+Vs_Body.size());
	GB_GameOver = false;

	for ( int row = 0; row < Height; row++)
	{
		delete[] Array_2D[row];
	}
	delete[] Array_2D;
}