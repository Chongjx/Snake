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
#include "Framework\sound.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

COORD coord_ConsoleSize;
COORD coord_Block;
COORD coord_Apple;
COORD coord_Special;
COORD coord_Map;

double elapsedTime;
double deltaTime;
double D_FoodTimer;
double D_Time;
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
char **Custom_2D;
bool KeyPressed[E_COUNT];
bool KeyPressed2[EP2_COUNT];
bool KeyPressedMap[E_MAPCOUNT];
Sound snd;
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


    snd.loadWave( "powerup", "Sounds\\powerup.wav");
    snd.loadWave( "food" , "Sounds\\food.wav");
    snd.loadWave( "intro" , "Sounds\\intro.wav");
    snd.loadWave( "gameover" , "Sounds\\gameover.wav");
    snd.loadWave( "choice" , "Sounds\\choice.wav");

}

void playGameSound(SoundType sound)
{
    switch (sound)
    {
        case S_POWERUP :snd.playSound("powerup");
            break;
        case S_FOOD :snd.playSound("food");
            break;
        case S_INTRO :snd.playSound("intro");
            break;
        case S_GAMEOVER :snd.playSound("gameover");
            break;
        case S_CHOICE :snd.playSound("choice");
            break;
    }
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

void CreateMap()
{
	cls();

	ifstream CustomMap;
	CustomMap.open ("Map\\Custom.txt");

	Custom_2D = new char*[40];

	for (int row = 0; row < Height; row++)
	{
		Custom_2D[row] = new char[100];
		for (int col = 0; col < Width; col++)
		{
			CustomMap >> Custom_2D[row][col];
		}
	}

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (Custom_2D[row][col] == '1')
			{
				colour (0x2);
				cout << char(178);
			}

			else
			{
				cout << char(32);
			}
		}
	}

	CustomMap.close();

	cout << endl;
	colour (0x7);
	cout << "1 - Blank ";
	colour (0x2);
	cout << " 2 - " << char(178);
	colour (0x6);
	cout << " 3 - " << char(254);
	colour (0xC);
	cout << " 4 - " << char(219);
	colour (0x7);
	cout << " Enter: Create Map ";

	coord_Block.X = 2;
	coord_Block.Y = 2;

	while (B_Complete == false)
	{
		GetMap();
		UpdateCustom();
		if (B_Complete == false)
		{
			InputBlock();
		}
	}

	Custom_2D[2][2] = '0';

	ofstream CreateMap;
	CreateMap.open ("Map\\Custom.txt");

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			CreateMap << Custom_2D[row][col];
		}
		CreateMap << endl;
	}

	CreateMap.close();

	for ( int row = 0; row < Height; row++)
	{
		delete[] Custom_2D[row];
	}
	delete[] Custom_2D;
}

void UpdateCustom()
{
	// Updating the location of the character based on the key press
	if (KeyPressedMap[E_MAPUP] && coord_Block.Y > 1)
	{
		coord_Block.Y--;
		Sleep(120);
	}

	if (KeyPressedMap[E_MAPLEFT] && coord_Block.X > 1)
	{
		coord_Block.X--;
		Sleep(120);
	}

	if (KeyPressedMap[E_MAPDOWN] && coord_Block.Y < 38)
	{
		coord_Block.Y++;
		Sleep(120);
	}

	if (KeyPressedMap[E_MAPRIGHT] && coord_Block.X < 98)
	{
		coord_Block.X++;
		Sleep(120);
	}

	if (KeyPressedMap[E_MAPESCAPE])
	{
		B_Complete = true;
	}
}

void InputBlock()
{
	gotoXY(coord_Block);
	char C_Block;
	C_Block = getch();
	switch (C_Block)
	{
	case '1':
		{
			Custom_2D[coord_Block.Y][coord_Block.X] = '0';
			cout << char(32);
		} break;
	case '2':
		{
			Custom_2D[coord_Block.Y][coord_Block.X] = '1';
			colour (0x2);
			cout << char(178);
		} break;
	case '3':
		{
			Custom_2D[coord_Block.Y][coord_Block.X] = '2';
			colour (0x6);
			cout << char(254);
		} break;
	case '4':
		{
			Custom_2D[coord_Block.Y][coord_Block.X] = '3';
			colour (0xC);
			cout << char(219);
		} break;
	}
	colour (0xC);
}

void Map()
{
	COORD coord_Score;

	if (B_Complete == false)
	{
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

		PrintMap.close();
	}

	else if (B_Complete == true)
	{
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
		case 6:
			{
				PrintMap.open("Map\\Custom.txt");
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

		PrintMap.close();
	}

	//Score for player 1
	coord_Score.X = 0;
	coord_Score.Y = 40;

	gotoXY(coord_Score);
	cout << "Your score: ";
}

void GetInput()
{    
	KeyPressed[E_UP] = isKeyPressed(VK_UP);
	KeyPressed[E_DOWN] = isKeyPressed(VK_DOWN);
	KeyPressed[E_LEFT] = isKeyPressed(VK_LEFT);
	KeyPressed[E_RIGHT] = isKeyPressed(VK_RIGHT);
}

void GetMap()
{
	KeyPressedMap[E_MAPUP] = isKeyPressed(VK_UP);
	KeyPressedMap[E_MAPDOWN] = isKeyPressed(VK_DOWN);
	KeyPressedMap[E_MAPLEFT] = isKeyPressed(VK_LEFT);
	KeyPressedMap[E_MAPRIGHT] = isKeyPressed(VK_RIGHT);
	KeyPressedMap[E_MAPESCAPE] = isKeyPressed(VK_RETURN);
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
			Vs_P1[i].CharLocation = Vs_P1[i-1].CharLocation;
		}
		Vs_P1[0].CharLocation.Y--;
		break;

	case E_DOWN:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation = Vs_P1[i-1].CharLocation;
		}
		Vs_P1[0].CharLocation.Y++;
		break;

	case E_LEFT:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation = Vs_P1[i-1].CharLocation;
		}
		Vs_P1[0].CharLocation.X--;
		break;

	case E_RIGHT:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation = Vs_P1[i-1].CharLocation;
		}
		Vs_P1[0].CharLocation.X++;
		break;

	case E_NORM:
		for (int i = Vs_P1.size()-1; i > 0 ; i--)
		{
			Vs_P1[i].CharLocation = Vs_P1[i-1].CharLocation;
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
		if ( Vs_P1[0].CharLocation == Vs_P1[i].CharLocation)
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
        playGameSound(S_GAMEOVER);
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

	if (Vs_P1[0].CharLocation == coord_Apple)
	{
        playGameSound(S_FOOD);
		B_FoodEaten = true;
		I_Food = 0;
		Vs_P1.push_back(s_Snake());

		Vs_P1[Vs_P1.size()-1].CharLocation = Vs_P1[Vs_P1.size()-2].CharLocation;

		I_Score += 10;
		Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
	}

	if (B_FoodEaten != true && I_Food == 0)
	{
		Spawn();
		I_Food++;
	}

	if (Vs_P1[0].CharLocation == coord_Special)
	{
		playGameSound(S_POWERUP);
		B_SpecialFoodEaten = true;
		I_Special = 0;
		Vs_P1.push_back(s_Snake());

		Vs_P1[Vs_P1.size()-1].CharLocation = Vs_P1[Vs_P1.size()-2].CharLocation;

		I_Score += 20;

		if (elapsedTime > D_Time)
		{
			elapsedTime = 0.00000;
			D_FoodTimer = 0.00000;
			D_Time += elapsedTime + 5;
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
			if (coord_Apple == Vs_P1[i].CharLocation)
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
			if (coord_Special == Vs_P1[i].CharLocation)
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
	string S_Name ="";
	cout << endl;
	cout << "                                             Enter your name: ";
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

bool operator ==(COORD const& lhs, COORD const& rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

void ClearCustomMap()
{
	ifstream OriginalMap;
	ofstream YourMap;
	string S_OriginalMap;

	OriginalMap.open("Map\\Cage.txt");
	YourMap.open ("Map\\Custom.txt");

	while (!OriginalMap.eof())
	{
		getline (OriginalMap, S_OriginalMap);
		YourMap << S_OriginalMap << endl;
	}

	OriginalMap.close();
	YourMap.close();
}