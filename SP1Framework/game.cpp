// This is the main file for the game logic and function
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
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

COORD coord_ConsoleSize;

double elapsedTime;
double deltaTime;
double D_FoodTimer;
double D_Time;
COORD coord_Apple;
COORD coord_Special;
int I_Score;
int I_Food;
int I_Special;
int I_Move;
int I_Prev;
int I_Move2;
int I_Prev2;
int I_Current;
int I_Bonus;

char **Array_2D;
bool KeyPressed[E_COUNT];
bool KeyPressed2[EP2_COUNT];
vector<s_Snake> Vs_P1;
vector<s_Snake> Vs_P2;
WORD ChosenColour[];
WORD ChosenColour2[];

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

	srand(time(0));

	colour(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	I_Food = 0;
	I_Special = 0;
	I_Score = 0;
	I_Move = 4;
	I_Prev = 0;
	I_Move2 = 4;
	I_Prev2 = 0;
	I_Current = 0;
	D_FoodTimer = 10.00000;
	D_Time = 0.00000;
}

void ShutDown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

// for 1 player till line 500
void CreateSnake(int size)
{
	// Create a snake at top right of the map
	for (int i = 0; i < size; i++)
	{
		Vs_P1.push_back(s_Snake());

		Vs_P1[i].CharLocation.X = 98;
		Vs_P1[i].CharLocation.Y = 3-i;
	}
}

void Map()
{
	COORD coord_Score;

	ifstream PrintMap;
	switch(I_Map)
	{
	case 1:
		{
			PrintMap.open("Map\\Cage.txt");
		} break;
	case 2:
		{
			PrintMap.open("Map\\Christmas.txt");
		} break;
	case 3:
		{
			PrintMap.open("Map\\Garden.txt");
		} break;
	case 4:
		{
			PrintMap.open("Map\\Maze.txt");
		} break;
	case 5:
		{
			PrintMap.open("Map\\Mine.txt");
		} break;
	}

	Array_2D = new char*[40];

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
				colour (0x2);
				cout << char(178);
			}

			else if (Array_2D[row][col] == '2')
			{
				colour (0x6);
				cout << char(254);
			}

			else if (Array_2D[row][col] == '3')
			{
				colour (0xC);
				cout << char(219);
			}

			else
			{
				cout << char(32);
			}
		}
	}
	//Score for player 1
	coord_Score.X = 0;
	coord_Score.Y = 40;

	gotoXY(coord_Score);
	cout << "Your score: ";

	PrintMap.close();
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
	// updating the location of the character based on the key press

	gotoXY(Vs_P1[Vs_P1.size()-1].CharLocation);
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
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation.X = Vs_P1[i-1].CharLocation.X;
			Vs_P1[i].CharLocation.Y = Vs_P1[i-1].CharLocation.Y;
		}
		Vs_P1[0].CharLocation.Y--;
		break;

	case E_DOWN:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation.X = Vs_P1[i-1].CharLocation.X;
			Vs_P1[i].CharLocation.Y = Vs_P1[i-1].CharLocation.Y;
		}
		Vs_P1[0].CharLocation.Y++;
		break;

	case E_LEFT:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation.X = Vs_P1[i-1].CharLocation.X;
			Vs_P1[i].CharLocation.Y = Vs_P1[i-1].CharLocation.Y;
		}
		Vs_P1[0].CharLocation.X--;
		break;

	case E_RIGHT:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation.X = Vs_P1[i-1].CharLocation.X;
			Vs_P1[i].CharLocation.Y = Vs_P1[i-1].CharLocation.Y;
		}
		Vs_P1[0].CharLocation.X++;
		break;

	case E_NORM:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation.X = Vs_P1[i-1].CharLocation.X;
			Vs_P1[i].CharLocation.Y = Vs_P1[i-1].CharLocation.Y;
		}
		Vs_P1[0].CharLocation.Y++;
		break;
	}

	CheckCollision();
	UpdateSnake();

	if (I_Current == 2)
	{
		return 500;
	}

	else if (I_Current == 1)
	{
		return 200;
	}

	else if (I_Current == 0)
	{
		return 800;
	}
}

void CheckCollision()
{
	for (int i = 1; i < Vs_P1.size(); i++)
	{
		if ( Vs_P1[0].CharLocation.X == Vs_P1[i].CharLocation.X && Vs_P1[0].CharLocation.Y == Vs_P1[i].CharLocation.Y)
		{
			GB_GameOver = true;
		}
	}

	if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '1')
	{
		GB_GameOver = true;
	}

	if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '2')
	{
		GB_GameOver = true;
	}

	if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '3')
	{
		GB_GameOver = true;
	}

	if (GB_GameOver == true)
	{
		for ( int i = 0; i < 10; i++)
		{
			gotoXY (Vs_P1[0].CharLocation);
			colour (0xC);
			cout << char(254);
			Sleep (100);

			gotoXY (Vs_P1[0].CharLocation);
			colour (0x7);
			cout << char(254);
			Sleep (100);
		}

		Sleep(1000);
	}
}

void UpdateSnake()
{
	bool B_FoodEaten = false;
	bool B_SpecialFoodEaten = false;

	if (Vs_P1[0].CharLocation.X == coord_Apple.X && Vs_P1[0].CharLocation.Y == coord_Apple.Y)
	{
		Beep (1045, 100);
		B_FoodEaten = true;
		I_Food = 0;
		Vs_P1.push_back(s_Snake());

		Vs_P1[Vs_P1.size()-1].CharLocation.X = Vs_P1[Vs_P1.size()-2].CharLocation.X;
		Vs_P1[Vs_P1.size()-1].CharLocation.Y = Vs_P1[Vs_P1.size()-2].CharLocation.Y;

		I_Score += 10;
		Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
	}

	if (B_FoodEaten != true && I_Food == 0)
	{
		Spawn();
		I_Food++;
	}

	if (Vs_P1[0].CharLocation.X == coord_Special.X && Vs_P1[0].CharLocation.Y == coord_Special.Y)
	{
		Beep (1046, 100);
		Beep (1046, 100);
		Beep (1046, 100);
		B_SpecialFoodEaten = true;
		I_Special = 0;
		Vs_P1.push_back(s_Snake());

		Vs_P1[Vs_P1.size()-1].CharLocation.X = Vs_P1[Vs_P1.size()-2].CharLocation.X;
		Vs_P1[Vs_P1.size()-1].CharLocation.Y = Vs_P1[Vs_P1.size()-2].CharLocation.Y;

		I_Score += 20;

		if (elapsedTime > D_Time)
		{
			D_Time += elapsedTime + 10;
		}

		if (I_Bonus == 0)
		{
			I_Current = 0;
		}

		else
		{
			I_Current = 1;
		}

		Array_2D[coord_Special.Y][coord_Special.X] = '0';
	}

	if (B_SpecialFoodEaten != true && I_Special == 0)
	{
		I_Special++;
	}

	if (D_Time - elapsedTime < -1.000)
	{
		I_Current = 2;
	}
}

void Spawn()
{
	bool B_CheckLocation = false;

	while (B_CheckLocation == false)
	{
		coord_Apple.X = rand() % 99 + 1;
		coord_Apple.Y = rand() % 39 + 1;

		for (int i = 0; i < Vs_P1.size(); i++)
		{
			if (coord_Apple.X == Vs_P1[i].CharLocation.X && coord_Apple.Y == Vs_P1[i].CharLocation.Y)
			{
				B_CheckLocation = false;
			}

			else if (Array_2D[coord_Apple.Y][coord_Apple.X] != '0')
			{
				B_CheckLocation = false;
			}

			else
			{
				B_CheckLocation = true;
			}
		}
	}

	Array_2D[coord_Apple.Y][coord_Apple.X] = '4';
	gotoXY (coord_Apple);
	colour (0x7);
	cout << char(3);
}

void Render()
{
	Timer();
	colour (ChosenColour[0]);
	// render the game

	gotoXY (Vs_P1[0].CharLocation);
	cout << char(254);

	gotoXY (12, 40);
	cout << I_Score;

	COORD coord_Position;
	// set the cursor location at the top of the screen
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	coord_Position.X = 0;
	coord_Position.Y = 0;
	SetConsoleCursorPosition (hOut, coord_Position);
}

void Timer()
{
	if (elapsedTime > D_FoodTimer)
	{
		SpawnSpecial();
		D_FoodTimer += 10.00000;
	}

	if (D_FoodTimer - elapsedTime < 0.5000)
	{
		gotoXY (coord_Special);
		cout << ' ';
		Array_2D[coord_Special.Y][coord_Special.X] = '0';
	}
}

void SpawnSpecial()
{
	bool B_CheckLocation = false;

	while (B_CheckLocation == false)
	{
		coord_Special.X = rand() % 99 + 1;
		coord_Special.Y = rand() % 39 + 1;

		if (Array_2D[coord_Special.Y][coord_Special.X] != '0')
		{
			B_CheckLocation = false;
		}

		else
		{
			B_CheckLocation = true;
		}
		for ( int i = 0; i < Vs_P1.size(); i++)
		{
			if (coord_Special.X == Vs_P1[i].CharLocation.X && coord_Special.Y == Vs_P1[i].CharLocation.Y)
			{
				B_CheckLocation = false;
			}
		}
	}

	Array_2D[coord_Special.Y][coord_Special.X] = '5';

	I_Bonus = rand() % 2;

	if (I_Bonus == 0)
	{
		gotoXY (coord_Special);
		colour (0xF);
		cout << char(31);
	}

	else if (I_Bonus == 1)
	{
		gotoXY (coord_Special);
		colour (0xF);
		cout << char(30);
	}
}

void ScoreBoard()
{
	cls();
	string S_Name;
	cout << "                    Enter your name: ";
	getline (cin, S_Name);
	cout << endl;

	HiScore(I_Score, S_Name);
}

void GG()
{
	I_Move = 4;
	I_Prev = 0;
	I_Current = 2;
	I_Score = 0;
	I_Food = 0.00000;
	I_Special = 0;
	D_Time = 0;
	Vs_P1.erase(Vs_P1.begin(), Vs_P1.begin()+Vs_P1.size());
	GB_GameOver = false;

	for ( int row = 0; row < Height; row++)
	{
		delete[] Array_2D[row];
	}
	delete[] Array_2D;
}