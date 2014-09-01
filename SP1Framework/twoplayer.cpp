#include "twoplayer.h"

#include "menu.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

void CreateSnake2(int size)
{
	// Create a snake at top right of the map
	for (int i = 0; i < size; i++)
	{
		Vs_P1.push_back(s_Snake());

		Vs_P1[i].CharLocation.X = 98;
		Vs_P1[i].CharLocation.Y = 3-i;

		Vs_P2.push_back(s_Snake());

		Vs_P2[i].CharLocation.X = 1;
		Vs_P2[i].CharLocation.Y = 3-i;
	}
}

void Map2()
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

void GetInput2()
{    
	KeyPressed[E_UP] = isKeyPressed(VK_UP);
	KeyPressed[E_DOWN] = isKeyPressed(VK_DOWN);
	KeyPressed[E_LEFT] = isKeyPressed(VK_LEFT);
	KeyPressed[E_RIGHT] = isKeyPressed(VK_RIGHT);

	KeyPressed2[EP2_W] = isKeyPressed(0x57);
	KeyPressed2[EP2_S] = isKeyPressed(0x53);
	KeyPressed2[EP2_A] = isKeyPressed(0x41);
	KeyPressed2[EP2_D] = isKeyPressed(0x44);
}

int Update2(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	// updating the location of the character based on the key press

	gotoXY(Vs_P1[Vs_P1.size()-1].CharLocation);
	cout << ' ';

	gotoXY(Vs_P2[Vs_P2.size()-1].CharLocation);
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

	// if the player press up and the snake is not moving down, the snake will move up
	if (KeyPressed2[EP2_W] && I_Prev2 != 1 && I_Move2 != 4)
	{
		I_Move2 = 0;
		I_Prev2 = I_Move2;
	}

	// if the player press down and the snake is not moving up, the snake will move down
	else if (KeyPressed2[EP2_S] && I_Prev2 != 0)
	{
		I_Move2 = 1;
		I_Prev2 = I_Move2;
	}

	// if the player press left and the snake is not moving right, the snake will move left
	else if (KeyPressed2[EP2_A] && I_Prev2 != 3)
	{
		I_Move2 = 2;
		I_Prev2 = I_Move2;
	}

	// if the player press right and the snake is not moving left, the snake will move right
	else if (KeyPressed2[EP2_D] && I_Prev2 != 2)
	{
		I_Move2 = 3;
		I_Prev2 = I_Move2;
	}

	// change the coordinates of the snake
	switch(I_Move2)
	{
	case EP2_W:
		for (int i = Vs_P2.size()-1; i > 0 ; i--)
		{
			Vs_P2[i].CharLocation.X = Vs_P2[i-1].CharLocation.X;
			Vs_P2[i].CharLocation.Y = Vs_P2[i-1].CharLocation.Y;
		}
		Vs_P2[0].CharLocation.Y--;
		break;

	case EP2_S:
		for (int i = Vs_P2.size()-1; i > 0 ; i--)
		{
			Vs_P2[i].CharLocation.X = Vs_P2[i-1].CharLocation.X;
			Vs_P2[i].CharLocation.Y = Vs_P2[i-1].CharLocation.Y;
		}
		Vs_P2[0].CharLocation.Y++;
		break;

	case EP2_A:
		for (int i = Vs_P2.size()-1; i > 0 ; i--)
		{
			Vs_P2[i].CharLocation.X = Vs_P2[i-1].CharLocation.X;
			Vs_P2[i].CharLocation.Y = Vs_P2[i-1].CharLocation.Y;
		}
		Vs_P2[0].CharLocation.X--;
		break;

	case EP2_D:
		for (int i = Vs_P2.size()-1; i > 0 ; i--)
		{
			Vs_P2[i].CharLocation.X = Vs_P2[i-1].CharLocation.X;
			Vs_P2[i].CharLocation.Y = Vs_P2[i-1].CharLocation.Y;
		}
		Vs_P2[0].CharLocation.X++;
		break;

	case EP2_NORM:
		for (int i = Vs_P2.size()-1; i > 0 ; i--)
		{
			Vs_P2[i].CharLocation.X = Vs_P2[i-1].CharLocation.X;
			Vs_P2[i].CharLocation.Y = Vs_P2[i-1].CharLocation.Y;
		}
		Vs_P2[0].CharLocation.Y++;
		break;
	}

	CheckCollision2();
	UpdateSnake2();

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

void CheckCollision2()
{
	bool B_P1_Over = false;
	bool B_P2_Over = false;
	for (int i = 1; i < Vs_P1.size(); i++)
	{
		//Check collision for the snake's own body
		if (Vs_P1[0].CharLocation.X == Vs_P1[i].CharLocation.X && Vs_P1[0].CharLocation.Y == Vs_P1[i].CharLocation.Y)
		{
			B_P1_Over = true;
		}
	}

	for (int i = 1; i < Vs_P2.size(); i++)
	{
		if (Vs_P2[0].CharLocation.X == Vs_P2[i].CharLocation.X && Vs_P2[0].CharLocation.Y == Vs_P2[i].CharLocation.Y)
		{
			B_P2_Over = true;
		}
	}

	if (Vs_P1[0].CharLocation.X == Vs_P2[1].CharLocation.X && Vs_P1[0].CharLocation.Y == Vs_P2[1].CharLocation.Y)
	{
		B_P1_Over = true;
	}

	if (Vs_P2[0].CharLocation.X == Vs_P1[1].CharLocation.X && Vs_P2[0].CharLocation.Y == Vs_P1[1].CharLocation.Y)
	{
		B_P2_Over = true;
	}

	if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '1')
	{
		B_P1_Over = true;
	}

	else if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '2')
	{
		B_P1_Over = true;
	}

	else if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '3')
	{
		B_P1_Over = true;
	}

	if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '1')
	{
		B_P2_Over = true;
	}

	else if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '2')
	{
		B_P2_Over = true;
	}

	if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '3')
	{
		B_P2_Over = true;
	}

	if (B_P1_Over == true || B_P2_Over == true)
	{
		GB_GameOver = true;
	}

	if (B_P1_Over == true && B_P2_Over != true)
	{
		for (int i = 0; i < 10; i++)
		{
			gotoXY (Vs_P1[0].CharLocation);
			colour (0xC);
			cout << char(254);
			Sleep(100);

			gotoXY (Vs_P1[0].CharLocation);
			colour (0x7);
			cout << char(254);
			Sleep (100);
		}
	}

	else if (B_P2_Over == true && B_P1_Over != true)
	{
		for (int i = 0; i < 10; i++)
		{
			gotoXY (Vs_P2[0].CharLocation);
			colour (0xC);
			cout << char(254);
			Sleep (100);

			gotoXY (Vs_P2[0].CharLocation);
			colour (0x7);
			cout << char(254);
			Sleep (100);
		}
	}

	else if (B_P1_Over == true && B_P2_Over == true)
	{
		for (int i = 0; i < 10; i++)
		{
			gotoXY (Vs_P1[0].CharLocation);
			colour (0xC);
			cout << char(254);
			
			gotoXY (Vs_P2[0].CharLocation);
			colour (0xC);
			cout << char(254);
			Sleep (100);

			gotoXY (Vs_P1[0].CharLocation);
			colour (0x7);
			cout << char(254);

			gotoXY (Vs_P2[0].CharLocation);
			colour (0x7);
			cout << char(254);
			Sleep (100);
		}
	}
}

void snakeEatSnake(vector<s_Snake>& predator, vector<s_Snake>& prey)
{
	for (int i = 2; i < prey.size(); i++)
	{
		//checks if the predator eats the prey
		if (predator[0].CharLocation == prey[i].CharLocation)
		{
			int cutLength = prey.size() - i - 1;

			// increase the predator length
			predator.insert(predator.end(), cutLength, predator.back());

			// cut off the prey

			for (int x = 0; x < cutLength; x++)
			{
				gotoXY (prey.back().CharLocation);
				cout << ' ';
				prey.pop_back();				
			}
			break;
		}
	}
}

void UpdateSnake2()
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

		Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
	}

	if (Vs_P2[0].CharLocation.X == coord_Apple.X && Vs_P2[0].CharLocation.Y == coord_Apple.Y)
	{
		Beep (1045, 100);
		B_FoodEaten = true;
		I_Food = 0;
		Vs_P2.push_back(s_Snake());

		Vs_P2[Vs_P2.size()-1].CharLocation.X = Vs_P2[Vs_P2.size()-2].CharLocation.X;
		Vs_P2[Vs_P2.size()-1].CharLocation.Y = Vs_P2[Vs_P2.size()-2].CharLocation.Y;

		Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
	}

	snakeEatSnake(Vs_P1, Vs_P2);
	snakeEatSnake(Vs_P2, Vs_P1);

	//for (int i = 2; i < Vs_P2.size(); i++)
	//{
	//	if ( Vs_P1[0].CharLocation.X == Vs_P2[i].CharLocation.X && Vs_P1[0].CharLocation.Y == Vs_P2[i].CharLocation.Y)
	//	{
	//		int I_Length = Vs_P2.size();

	//		for (int x = i; x < I_Length; x++)
	//		{
	//			// increase the S1 length 
	//			Vs_P1.push_back(s_Snake());

	//			//Vs_P1[Vs_P1.size()-1].CharLocation.X = Vs_P1[Vs_P1.size()-2].CharLocation.X;
	//			//Vs_P1[Vs_P1.size()-1].CharLocation.Y = Vs_P1[Vs_P1.size()-2].CharLocation.Y;
	//			Vs_P2.back() = Vs_P1[Vs_P1.size()-2];

	//			//
	//			gotoXY (Vs_P2.back().CharLocation);
	//			cout << ' ';
	//			Vs_P2.pop_back();				
	//		}
	//		
	//		break;
	//	}
	//}

	//for (int i = 2; i < Vs_P1.size(); i++)
	//{
	//	if ( Vs_P2[0].CharLocation.X == Vs_P1[i].CharLocation.X && Vs_P2[0].CharLocation.Y == Vs_P1[i].CharLocation.Y)
	//	{
	//		int I_Length = Vs_P1.size();

	//		for (int x = i; x < I_Length; x++)
	//		{
	//			Vs_P2.push_back(s_Snake());

	//			Vs_P2[Vs_P2.size()-1].CharLocation.X = Vs_P2[Vs_P2.size()-2].CharLocation.X;
	//			Vs_P2[Vs_P2.size()-1].CharLocation.Y = Vs_P2[Vs_P2.size()-2].CharLocation.X;

	//			gotoXY (Vs_P1[Vs_P1.size()-1].CharLocation);
	//			cout << ' ';

	//			Vs_P1.erase(Vs_P1.begin() + (Vs_P1.size()-1));
	//		}
	//		break;
	//	}
	//}

	if (B_FoodEaten == false && I_Food == 0)
	{
		Spawn2();
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

		if (elapsedTime > D_Time)
		{
			D_Time += elapsedTime + 10.00000;
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

	if (Vs_P2[0].CharLocation.X == coord_Special.X && Vs_P2[0].CharLocation.Y == coord_Special.Y)
	{
		Beep (1046, 100);
		Beep (1046, 100);
		Beep (1046, 100);
		B_SpecialFoodEaten = true;
		I_Special = 0;
		Vs_P2.push_back(s_Snake());

		Vs_P2[Vs_P2.size()-1].CharLocation.X = Vs_P2[Vs_P2.size()-2].CharLocation.X;
		Vs_P2[Vs_P2.size()-1].CharLocation.Y = Vs_P2[Vs_P2.size()-2].CharLocation.Y;

		if (elapsedTime > D_Time)
		{
			D_Time += elapsedTime + 10.00000;
		}

		if (I_Bonus = 0)
		{
			I_Current = 1;
		}

		else
		{
			I_Current = 0;
		}

		Array_2D[coord_Special.Y][coord_Special.X] = '0';
	}

	if (B_SpecialFoodEaten != true && I_Special == 0)
	{
		I_Special++;
	}

	if (D_Time - elapsedTime < -1.0000)
	{
		I_Current = 2;
	}
}

void Spawn2()
{
	bool B_CheckLocation = false;

	while (B_CheckLocation == false)
	{
		coord_Apple.X = rand() % 99 + 1;
		coord_Apple.Y = rand() % 39 + 1;

		if (Array_2D[coord_Apple.Y][coord_Apple.X] != '0')
		{
			B_CheckLocation = false;
		}

		else
		{
			B_CheckLocation = true;
		}

		for (int i = 0; i < Vs_P1.size(); i++)
		{
			if (coord_Apple.X == Vs_P1[i].CharLocation.X && coord_Apple.Y == Vs_P1[i].CharLocation.Y)
			{
				B_CheckLocation = false;
			}
		}

		for (int i = 0; i < Vs_P2.size(); i++)
		{
			if (coord_Apple.X == Vs_P2[i].CharLocation.X && coord_Apple.Y == Vs_P2[i].CharLocation.Y)
			{
				B_CheckLocation = false;
			}
		}
	}

	Array_2D[coord_Apple.Y][coord_Apple.X] = '4';
	gotoXY (coord_Apple);
	colour (0x7);
	cout << char(3);
}

void Render2()
{
	Timer2();

	// render the game
	for (int i = 0 ; i < Vs_P1.size(); i++)
	{
		colour (ChosenColour[0]);
		gotoXY (Vs_P1[i].CharLocation);
		cout << char(254);
	}

	for (int i = 0; i < Vs_P2.size(); i++)
	{
		colour (ChosenColour2[0]);
		gotoXY (Vs_P2[i].CharLocation);
		cout << char(254);
	}

	COORD coord_Position;
	// set the cursor location at the top of the screen
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	coord_Position.X = 0;
	coord_Position.Y = 0;
	SetConsoleCursorPosition (hOut, coord_Position);
}

void Timer2()
{
	if (elapsedTime > D_FoodTimer)
	{
		SpawnSpecial2();
		D_FoodTimer += 10.00000;
	}

	if (D_FoodTimer - elapsedTime < 0.5000)
	{
		gotoXY (coord_Special);
		cout << ' ';
		Array_2D[coord_Special.Y][coord_Special.X] = '0';
	}
}

void SpawnSpecial2()
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

		for ( int i = 0; i < Vs_P2.size(); i++)
		{
			if (coord_Special.X == Vs_P2[i].CharLocation.X && coord_Special.Y == Vs_P2[i].CharLocation.Y)
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

void GG2()
{
	cls();
	/*if ( Vs_P1.size() > Vs_P2.size())
	{
		cout << "Player 1 wins!" << endl;
		Sleep(1000);
	}

	else if ( Vs_P2.size() > Vs_P1.size())
	{
		cout << "Player 2 wins!" << endl;
		Sleep(1000);
	}

	else
	{
		cout << "Its a draw!" << endl;
		Sleep(1000);
	}*/

	I_Move = 4;
	I_Prev = 0;
	I_Move2 = 4;
	I_Prev2 = 0;
	I_Current = 2;
	I_Food = 0;
	I_Special = 0;
	D_Time = 0.00000;
	Vs_P1.erase(Vs_P1.begin(), Vs_P1.begin()+Vs_P1.size());
	Vs_P2.erase(Vs_P2.begin(), Vs_P2.begin()+Vs_P2.size());
	GB_GameOver = false;

	ChosenColour[0] = (0x7);
	ChosenColour2[0] = (0x7);

	for ( int row = 0; row < Height; row++)
	{
		delete[] Array_2D[row];
	}
	delete[] Array_2D;
}