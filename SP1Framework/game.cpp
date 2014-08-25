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
COORD coord_Special;
int I_Food = 0;
int I_Special = 0;
int I_Score;
int I_Current;
int I_Move;
int I_Prev;
int I_FoodTimer = 10;
char **Array_2D;
bool KeyPressed[E_COUNT];

///Player2
int I_Food2 = 0;
int I_Score2;
int I_Current2;
int I_Move2;
int I_Prev2;
bool KeyPressed2[E_COUNT2];

WORD ChosenColour[] = {0x7};
WORD ChosenColour2[] = {0xC};

vector<s_Snake> Vs_Body;
vector<s_Snake2> Vs_Body2;

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
	I_Move2 = 4;
	I_Prev2 = 0;
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
		break;

	case E_DOWN:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.Y++;
		break;

	case E_LEFT:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.X--;
		break;

	case E_RIGHT:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.X++;
		break;

	case E_NORM:
		for (int i = Vs_Body.size()-1; i > 0 ; i--)
		{
			Vs_Body[i].CharLocation.X = Vs_Body[i-1].CharLocation.X;
			Vs_Body[i].CharLocation.Y = Vs_Body[i-1].CharLocation.Y;
		}
		Vs_Body[0].CharLocation.Y++;
		break;
	}

	CheckCollision();
	// Player 2
	// Updating the location of the character based on the key press

	gotoXY(Vs_Body2[Vs_Body2.size()-1].CharLocation2);
	cout << ' ';

	// if the player press up and the snake is not moving down, the snake will move up
	if (KeyPressed2[E_W] && I_Prev2 != 1 && I_Move2 != 4)
	{
		I_Move2 = 0;
		I_Prev2 = I_Move2;
	}

	// if the player press down and the snake is not moving up, the snake will move down
	else if (KeyPressed2[E_S] && I_Prev2 != 0)
	{
		I_Move2 = 1;
		I_Prev2 = I_Move2;
	}

	// if the player press left and the snake is not moving right, the snake will move left
	else if (KeyPressed2[E_A] && I_Prev2 != 3)
	{
		I_Move2 = 2;
		I_Prev2 = I_Move2;
	}

	// if the player press right and the snake is not moving left, the snake will move right
	else if (KeyPressed2[E_D] && I_Prev2 != 2)
	{
		I_Move2 = 3;
		I_Prev2 = I_Move2;
	}

	// change the coordinates of the snake
	switch(I_Move2)
	{
	case E_W:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y--;
		break;

	case E_S:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y++;
		break;

	case E_A:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.X--;
		break;

	case E_D:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.X++;
		break;

	case E_NORM2:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y++;
		break;
	}

	CheckCollision2();

	I_Current = UpdateSnake();
	UpdateSnake2();

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
    Timer();
	colour(ChosenColour[0]);

	//render the game

	// render the snake Player 1
	gotoXY(Vs_Body[0].CharLocation);
	cout << char(254);

	gotoXY(12, 40);
	cout << I_Score;

	colour(ChosenColour2[0]);
	//Render player 2
	gotoXY(Vs_Body2[0].CharLocation2);
	cout << char(254);

	gotoXY(82, 40);
	cout << I_Score2;

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
	COORD coord_Scoreplace2;
	// create a 2D array that will store the location of the snake and the food
	ifstream PrintMap;

	PrintMap.open("Map\\Cage.txt");



<<<<<<< 145d61782c8c190b56c35eb3f0d6abbd369da252
	Array_2D = new char*[40];
=======
	PrintMap.open("Map\\Cage.txt");
>>>>>>> 58b6b6c21c0bc19f437f1e9d0d145b28437fb9c9

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
	//Score for player 1
	coord_Scoreplace.X = 0;
	coord_Scoreplace.Y = 45;
	//Score for player 2
	coord_Scoreplace2.X = 82;
	coord_Scoreplace2.Y = 45;

	gotoXY(coord_Scoreplace);
	cout << "Your score: ";

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
        Array_2D[coord_Apple.Y][coord_Apple.X] = '2';
		gotoXY (coord_Apple);
		colour(0x7);
		cout << char(3);
	}
	
}

void SpawnSpecial()
{
    bool B_CheckLocation = false;
    
    while(B_CheckLocation == false)
    {
        B_CheckLocation = CheckSpecialFood();
    }

    if (B_CheckLocation == true)
    {
        Array_2D[coord_Special.Y][coord_Special.X] = '3';
        gotoXY (coord_Special);
        colour(0x7);
        cout << char(36);
    }
}

bool CheckFood()
{
	bool B_Check;
	srand(time(0));
	coord_Apple.X = rand() % 99 + 1;
	coord_Apple.Y = rand() % 39 + 1;
	//Player 1
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
<<<<<<< 145d61782c8c190b56c35eb3f0d6abbd369da252
	}

	// Player 2
	for ( int i = 0; i < Vs_Body2.size(); i++)
	{
		if (coord_Apple.X == Vs_Body2[i].CharLocation2.X && coord_Apple.Y == Vs_Body2[i].CharLocation2.Y)
		{
			B_Check = false;
		}

		else if ( Array_2D[coord_Apple.Y][coord_Apple.X] == '1')
		{
			B_Check = false;
		}

=======

        else if ( Array_2D[coord_Apple.Y][coord_Apple.X] == '3')
        {
            B_Check = false;
        }
	
>>>>>>> 58b6b6c21c0bc19f437f1e9d0d145b28437fb9c9
		else
		{
			B_Check = true;
		}
	}

	return B_Check;
}

bool CheckSpecialFood()
{
    bool B_Check;
	srand(time(0));
	coord_Special.X = rand() % 99 + 1;
	coord_Special.Y = rand() % 39 + 1;

    for ( int i = 0; i < Vs_Body.size(); i++)
    {
        if (coord_Special.X == Vs_Body[i].CharLocation.X && coord_Special.Y == Vs_Body[i].CharLocation.Y)
		{
			B_Check = false;
		}

		else if ( Array_2D[coord_Special.Y][coord_Special.X] == '1')
		{
			B_Check = false;
		}

        else if ( Array_2D[coord_Special.Y][coord_Special.X] == '2')
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
    bool B_SpecialFood = false;

	if (Vs_Body[0].CharLocation.X == coord_Apple.X && Vs_Body[0].CharLocation.Y == coord_Apple.Y)
	{
		Beep (1046, 100);
		B_FoodEaten = true;
		I_Food = 0;
		Vs_Body.push_back(s_Snake());

		Vs_Body[Vs_Body.size()-1].CharLocation.X = Vs_Body[Vs_Body.size()-2].CharLocation.X;
		Vs_Body[Vs_Body.size()-1].CharLocation.Y = Vs_Body[Vs_Body.size()-2].CharLocation.X;
		I_Score += 10;
        Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
	}

    if (Vs_Body[0].CharLocation.X == coord_Special.X && Vs_Body[0].CharLocation.Y == coord_Special.Y)
    {
        Beep (1046, 100);
		B_SpecialFood = true;
        I_Special = 0;
		Vs_Body.push_back(s_Snake());

		Vs_Body[Vs_Body.size()-1].CharLocation.X = Vs_Body[Vs_Body.size()-2].CharLocation.X;
		Vs_Body[Vs_Body.size()-1].CharLocation.Y = Vs_Body[Vs_Body.size()-2].CharLocation.X;
        Array_2D[coord_Special.Y][coord_Special.X] = '0';
    }

	if (B_FoodEaten != true && I_Food == 0)
	{
		Spawn();
		I_Food++;
	}

    if (B_SpecialFood != true && I_Special == 0)
    {
        I_Special++;
    }
	return I_Score;
}

void Timer()
{
    if (elapsedTime > I_FoodTimer)
    {
        SpawnSpecial();
        I_FoodTimer += 10;
    }

    if (I_FoodTimer - elapsedTime < 2)
    {
        gotoXY(coord_Special);
        cout << ' ';
        Array_2D[coord_Special.Y][coord_Special.X] = '0';
    }

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

	if (Array_2D[Vs_Body[0].CharLocation.Y][Vs_Body[0].CharLocation.X] == '1')
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
    //int I_Choice = 0;
<<<<<<< 145d61782c8c190b56c35eb3f0d6abbd369da252
    string S_Color[4] = {"Blue", "Green", "Pink", "Yellow"};
	int I_Color = 0;

    for (int i = 0; i < 4; ++i)
=======
    //string S_Color[4] = {"Blue", "Green", "Pink", "Yellow"};
	int I_Color = 0;

    /*for (int i = 0; i < 4; ++i)
>>>>>>> 58b6b6c21c0bc19f437f1e9d0d145b28437fb9c9
    {
        if (i == I_Color)
        {
            cout << "                    " << char(16) << S_Color[i] << endl;
        }
        else
        {
            colour(0x03);
            cout << "                    " << char(16) << S_Color[i] << endl;
        }
    }

    while(true)
    {
        if (GetAsyncKeyState(VK_UP) != 0)
        {
            I_Color -= 1;
            if (I_Color == -1)
            {
                I_Color = 3;
            }
            break;
        }

        else if(GetAsyncKeyState(VK_DOWN) != 0)
        {
            I_Color += 1;
            if (I_Color == 4)
            {
                I_Color = 0;
            }
            break;
        }

        else if (GetAsyncKeyState(VK_RETURN) != 0)
        {
            switch(I_Color)
            {
                case E_LIGHTBLUE:
                    {
                    colour(0xB);
                    ChosenColour[0] = 0xB;
                    }break;
                case E_GREEN:
                    {
                        colour(0xA);
                        ChosenColour[0] = 0xA;
                    }break;
                case E_PINK:
                    {
                        colour(0xD);
                        ChosenColour[0] = 0xD;
                    }break;
                case E_YELLOW:
                    {
                        colour(0xE);
                        ChosenColour[0] = 0xE;
                    }break;
                default:
                    {
                        colour(0xE);
                        ChosenColour[0] = 0xE;
                    } break;
            }
        }
    }
    Sleep(150);
<<<<<<< 145d61782c8c190b56c35eb3f0d6abbd369da252
    cout << "OOOOOO" << endl;
=======
    cout << "OOOOOO" << endl;*/


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
>>>>>>> 58b6b6c21c0bc19f437f1e9d0d145b28437fb9c9
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
    I_Special = 0;
	Vs_Body.erase(Vs_Body.begin(), Vs_Body.begin()+Vs_Body.size());
	GB_GameOver = false;

	for ( int row = 0; row < Height; row++)
	{
		delete[] Array_2D[row];
	}
	delete[] Array_2D;
}
//Player 2==================================================================================

void GetInput2()
{    
	KeyPressed2[E_W] = isKeyPressed(0x57);
	KeyPressed2[E_S] = isKeyPressed(0x53);
	KeyPressed2[E_A] = isKeyPressed(0x41);
	KeyPressed2[E_D] = isKeyPressed(0x44);
}


int Update2(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	// Updating the location of the character based on the key press

	gotoXY(Vs_Body2[Vs_Body2.size()-1].CharLocation2);
	cout << ' ';

	// if the player press up and the snake is not moving down, the snake will move up
	if (KeyPressed2[E_W] && I_Prev2 != 1 && I_Move2 != 4)
	{
		I_Move2 = 0;
		I_Prev2 = I_Move2;
	}

	// if the player press down and the snake is not moving up, the snake will move down
	else if (KeyPressed2[E_S] && I_Prev2 != 0)
	{
		I_Move2 = 1;
		I_Prev2 = I_Move2;
	}

	// if the player press left and the snake is not moving right, the snake will move left
	else if (KeyPressed2[E_A] && I_Prev2 != 3)
	{
		I_Move2 = 2;
		I_Prev2 = I_Move2;
	}

	// if the player press right and the snake is not moving left, the snake will move right
	else if (KeyPressed2[E_D] && I_Prev2 != 2)
	{
		I_Move2 = 3;
		I_Prev2 = I_Move2;
	}

	// change the coordinates of the snake
	switch(I_Move2)
	{
	case E_W:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y--;
		break;

	case E_S:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y++;
		break;

	case E_A:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.X--;
		break;

	case E_D:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.X++;
		break;

	case E_NORM2:
		for (int i = Vs_Body2.size()-1; i > 0 ; i--)
		{
			Vs_Body2[i].CharLocation2.X = Vs_Body2[i-1].CharLocation2.X;
			Vs_Body2[i].CharLocation2.Y = Vs_Body2[i-1].CharLocation2.Y;
		}
		Vs_Body2[0].CharLocation2.Y++;
		break;
	}

	CheckCollision2();

	I_Current2 = UpdateSnake2();

	if (I_Current2 <= 100)
	{
		return 500;
	}

	else if (I_Current2 <= 200)
	{
		return 400;
	}

	else if (I_Current2 <= 400)
	{
		return 200;
	}

	else if (I_Current2 > 500)
	{
		return 100;
	}
}

void CreateSnake2(int size)
{
	// Create a snake at the center of the map
	for (int i = 0; i < size; i++)
	{
		Vs_Body2.push_back(s_Snake2());

		Vs_Body2[i].CharLocation2.X = coord_ConsoleSize.X/4;
		Vs_Body2[i].CharLocation2.Y = coord_ConsoleSize.Y/4 - i;
	}
}

bool CheckFood2()
{
	bool B_Check2;
	srand(time(0));
	coord_Apple.X = rand() % 99 + 1;
	coord_Apple.Y = rand() % 39 + 1;
	
	for ( int i = 0; i < Vs_Body2.size(); i++)
	{
		if (coord_Apple.X == Vs_Body2[i].CharLocation2.X && coord_Apple.Y == Vs_Body2[i].CharLocation2.Y)
		{
			B_Check2 = false;
		}

		else if ( Array_2D[coord_Apple.Y][coord_Apple.X] == '1')
		{
			B_Check2 = false;
		}
	
		else
		{
			B_Check2 = true;
		}
	}

	return B_Check2;
}

int UpdateSnake2()
{
	bool B_FoodEaten2 = false;

	if (Vs_Body2[0].CharLocation2.X == coord_Apple.X && Vs_Body2[0].CharLocation2.Y == coord_Apple.Y)
	{
		Beep (1046, 100);
		B_FoodEaten2 = true;
		I_Food2 = 0;
		Vs_Body2.push_back(s_Snake2());

		Vs_Body2[Vs_Body2.size()-1].CharLocation2.X = Vs_Body2[Vs_Body2.size()-2].CharLocation2.X;
		Vs_Body2[Vs_Body2.size()-1].CharLocation2.Y = Vs_Body2[Vs_Body2.size()-2].CharLocation2.X;
		I_Score2 += 10;
	}

	if (B_FoodEaten2 != true && I_Food2 == 0)
	{
		Spawn();
		I_Food2++;
	}

	return I_Score2;
}

void CheckCollision2()
{
	for ( int i = 1; i < Vs_Body2.size(); i++)
	{
		if (Vs_Body2[0].CharLocation2.X == Vs_Body2[i].CharLocation2.X && Vs_Body2[0].CharLocation2.Y == Vs_Body2[i].CharLocation2.Y)
		{
			GB_GameOver = true;
		}
	}

	if (Array_2D[Vs_Body2[0].CharLocation2.Y][Vs_Body2[0].CharLocation2.X] == '1')
	{
		GB_GameOver = true;
	}

	if ( GB_GameOver == true)
	{
		gotoXY(Vs_Body2[0].CharLocation2);
		{
			colour(0xC);
			cout << char(254);
			Sleep(1000);
		}
	}
}

void GG2()
{
	I_Move2 = 4;
	I_Prev2 = 0;
	I_Current2 = 0;
	I_Score2 = 0;
	I_Food2 = 0;
	Vs_Body2.erase(Vs_Body2.begin(), Vs_Body2.begin()+Vs_Body2.size());
	GB_GameOver = false;
}