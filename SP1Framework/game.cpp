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

bool B_P1_Over = false;
bool B_P2_Over = false;

char **Array_2D;
bool KeyPressed[E_COUNT];
bool KeyPressed2[EP2_COUNT];
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
    snd.loadWave( "powerdown" , "Sounds\\powerdown.wav");
    snd.loadWave( "food" , "Sounds\\food.wav");
    snd.loadWave( "intro" , "Sounds\\intro.wav");
    snd.loadWave( "gameover" , "Sounds\\gameover.wav");
    snd.loadWave( "choice" , "Sounds\\choice.wav");
}

void ResetMove (int numplayers)
{
    I_Move = 4;
    I_Prev = 0;

    if (numplayers == 2)
    {
        I_Move2 = 4;
        I_Prev2 = 0;
    }
}

void playGameSound(SoundType sound)
{
    switch (sound)
    {
    case S_POWERUP :snd.playSound("powerup");
        break;
    case S_POWERDOWN :snd.playSound("powerdown");
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
void CreateSnake(int numplayers, int size)
{
    // Create a snake at top right of the map
    for (int i = 0; i < size; i++)
    {
        Vs_P1.push_back(s_Snake());

        Vs_P1[i].CharLocation.X = 75;
        Vs_P1[i].CharLocation.Y = 3-i;
    }

    if (numplayers == 2)
    {
        for (int i = 0; i < size; i++)
        {
            Vs_P2.push_back(s_Snake());

            Vs_P2[i].CharLocation.X = 25;
            Vs_P2[i].CharLocation.Y = 3-i;
        }
    }
}

void Map()
{
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
}

void GetInput(int numplayers)
{    
    KeyPressed[E_UP] = isKeyPressed(VK_UP);
    KeyPressed[E_DOWN] = isKeyPressed(VK_DOWN);
    KeyPressed[E_LEFT] = isKeyPressed(VK_LEFT);
    KeyPressed[E_RIGHT] = isKeyPressed(VK_RIGHT);

    if (numplayers == 2)
    {
        KeyPressed2[EP2_W] = isKeyPressed(0x57);
        KeyPressed2[EP2_S] = isKeyPressed(0x53);
        KeyPressed2[EP2_A] = isKeyPressed(0x41);
        KeyPressed2[EP2_D] = isKeyPressed(0x44);
    }
}

int Update(int numplayers, double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
    // updating the location of the character based on the key press

    gotoXY(Vs_P1[Vs_P1.size()-1].CharLocation);
    cout << ' ';

    if (numplayers == 2)
    {
        gotoXY(Vs_P2[Vs_P2.size()-1].CharLocation);
        cout << ' ';
    }

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


    if (numplayers == 2)
    {
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
                Vs_P2[i].CharLocation = Vs_P2[i-1].CharLocation;
            }
            Vs_P2[0].CharLocation.Y--;
            break;

        case EP2_S:
            for (int i = Vs_P2.size()-1; i > 0 ; i--)
            {
                Vs_P2[i].CharLocation = Vs_P2[i-1].CharLocation;
            }
            Vs_P2[0].CharLocation.Y++;
            break;

        case EP2_A:
            for (int i = Vs_P2.size()-1; i > 0 ; i--)
            {
                Vs_P2[i].CharLocation = Vs_P2[i-1].CharLocation;
            }
            Vs_P2[0].CharLocation.X--;
            break;

        case EP2_D:
            for (int i = Vs_P2.size()-1; i > 0 ; i--)
            {
                Vs_P2[i].CharLocation = Vs_P2[i-1].CharLocation;
            }
            Vs_P2[0].CharLocation.X++;
            break;

        case EP2_NORM:
            for (int i = Vs_P2.size()-1; i > 0 ; i--)
            {
                Vs_P2[i].CharLocation = Vs_P2[i-1].CharLocation;
            }
            Vs_P2[0].CharLocation.Y++;
            break;
        }

        CheckCollision(2);
        EatFood(2);
        EatSpecialFood(2);
    }

    else
    {
        CheckCollision(1);
        EatFood(1);
        EatSpecialFood(1);
    }

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

void CheckCollision(int numplayers)
{
    OneEatsSelf();
    OneHitsWall();

    if (numplayers == 2)
    {
        SnakeEatSnake(Vs_P1, Vs_P2);
        SnakeEatSnake(Vs_P2, Vs_P1);
        TwoEatsSelf();
        TwoHitsWall();
        Head2Head();

        if (B_P1_Over == true || B_P2_Over == true)
        {
            GB_GameOver = true;

            if (B_P1_Over == true && B_P2_Over != true)
            {
                P1Lose();
            }

            else if (B_P1_Over != true && B_P2_Over == true)
            {
                P2Lose();
            }

            else if (B_P1_Over == true && B_P2_Over == true)
            {
                BothLose();
            }
        }
    }

    else if (numplayers == 1 && B_P1_Over == true)
    {
        GB_GameOver = true;
        P1Lose();
    }
}

void OneEatsSelf()
{
    for (int i = 1; i < Vs_P1.size(); i++)
    {
        if ( Vs_P1[0].CharLocation == Vs_P1[i].CharLocation)
        {
            B_P1_Over = true;
        }
    }
}

void OneHitsWall()
{
    if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '1')
    {
        B_P1_Over = true;
    }

    if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '2')
    {
        B_P1_Over = true;
    }

    if (Array_2D[Vs_P1[0].CharLocation.Y][Vs_P1[0].CharLocation.X] == '3')
    {
        B_P1_Over = true;
    }
}

void TwoEatsSelf()
{
    for (int i = 1; i < Vs_P2.size(); i++)
    {
        if (Vs_P2[0].CharLocation == Vs_P2[i].CharLocation)
        {
            B_P2_Over = true;
        }
    }
}

void TwoHitsWall()
{
    if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '1')
    {
        B_P2_Over = true;
    }

    if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '2')
    {
        B_P2_Over = true;
    }

    if (Array_2D[Vs_P2[0].CharLocation.Y][Vs_P2[0].CharLocation.X] == '3')
    {
        B_P2_Over = true;
    }
}

void Head2Head()
{
	if (Vs_P1[0].CharLocation == Vs_P2[1].CharLocation)
	{
		B_P1_Over = true;
	}

	if (Vs_P1[0].CharLocation == Vs_P2[0].CharLocation)
	{
		B_P1_Over = true;
	}

	if (Vs_P2[0].CharLocation == Vs_P1[1].CharLocation)
	{
		B_P2_Over = true;
	}

	if (Vs_P2[0].CharLocation == Vs_P1[0].CharLocation)
	{
		B_P2_Over = true;
	}
}

void P1Lose()
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

void P2Lose()
{
	playGameSound(S_GAMEOVER);
	for ( int i = 0; i < 10; i++)
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
	Sleep(1000);
}

void BothLose()
{
     playGameSound(S_GAMEOVER);
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
	Sleep(1000);
}

void EatFood(int numplayers)
{
    bool B_FoodEaten = false;

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

    if (numplayers == 2)
    {
        if (Vs_P2[0].CharLocation == coord_Apple)
        {
            playGameSound(S_FOOD);
            B_FoodEaten = true;
            I_Food = 0;
            Vs_P2.push_back(s_Snake());

            Vs_P2[Vs_P2.size()-1].CharLocation = Vs_P2[Vs_P2.size()-2].CharLocation;

            Array_2D[coord_Apple.Y][coord_Apple.X] = '0';
        }

        if (B_FoodEaten == false && I_Food == 0)
        {
            Spawn(2);
            I_Food++;
        }
    }

    else if (numplayers == 1 && B_FoodEaten == false && I_Food == 0)
    {
        Spawn(1);
        I_Food++;
    }
}

void EatSpecialFood(int numplayers)
{
    bool B_SpecialFoodEaten = false;

    if (Vs_P1[0].CharLocation == coord_Special)
    {
        if (I_Bonus == 0)
        {     
            playGameSound(S_POWERDOWN);
            I_Current = 0;
        }

        else 
        {
            playGameSound(S_POWERUP);
            I_Current = 1;
        }

        B_SpecialFoodEaten = true;
        I_Special = 0;
        Vs_P1.push_back(s_Snake());

        Vs_P1[Vs_P1.size()-1].CharLocation = Vs_P1[Vs_P1.size()-2].CharLocation;

        I_Score += 20;

        if (elapsedTime > D_Time)
        {
            elapsedTime = 0.00000;
            D_FoodTimer = 0.00000;
            D_Time += 5;
        }
        Array_2D[coord_Special.Y][coord_Special.X] = '0';
    }

    if (numplayers == 2)
    {
        if (Vs_P2[0].CharLocation == coord_Special)
        {
            if (I_Bonus == 0)
            {
                playGameSound(S_POWERDOWN);
                I_Current = 0;
            }

            else 
            {
                playGameSound(S_POWERUP);
                I_Current = 1;
            }
            B_SpecialFoodEaten = true;
            I_Special = 0;
            Vs_P2.push_back(s_Snake());

            Vs_P2[Vs_P2.size()-1].CharLocation = Vs_P2[Vs_P2.size()-2].CharLocation;

            if (elapsedTime > D_Time)
            {
                elapsedTime = 0.00000;
                D_FoodTimer = 0.00000;
                D_Time += 5;
            }

            Array_2D[coord_Special.Y][coord_Special.X] = '0';
        }
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

void SnakeEatSnake(vector<s_Snake>& predator, vector<s_Snake>& prey)
{
    for (int i = 2; i < prey.size(); i++)
    {
        //checks if the predator eats the prey
        if (predator[0].CharLocation == prey[i].CharLocation)
        {
            // SOUND
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

void Spawn(int numplayers)
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
            if (coord_Apple == Vs_P1[i].CharLocation)
            {
                B_CheckLocation = false;
            }
        }

        if (numplayers == 2)
        {
            for (int i = 0; i < Vs_P2.size(); i++)
            {
                if (coord_Apple == Vs_P2[i].CharLocation)
                {
                    B_CheckLocation = false;
                }
            }
        }
    }

    Array_2D[coord_Apple.Y][coord_Apple.X] = '4';
    gotoXY (coord_Apple);
    colour (0x7);
    cout << char(3);
}

void SpawnSpecial(int numplayers)
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

        if (numplayers == 2)
        {
            for ( int i = 0; i < Vs_P2.size(); i++)
            {
                if (coord_Special == Vs_P2[i].CharLocation)
                {
                    B_CheckLocation = false;
                }
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

void Render(int numplayers)
{
    // render the game
    Timer(numplayers);

    for (int i = 0 ; i < Vs_P1.size(); i++)
    {
        colour (ChosenColour[0]);
        gotoXY (Vs_P1[i].CharLocation);
        cout << char(254);
    }

    if (numplayers == 2)
    {
        for (int i = 0; i < Vs_P2.size(); i++)
        {
            colour (ChosenColour2[0]);
            gotoXY (Vs_P2[i].CharLocation);
            cout << char(254);
        }
    }

    if (numplayers == 1)
    {
        gotoXY (12, 40);
        cout << I_Score;
    }

    COORD coord_Position;
    // set the cursor location at the top of the screen
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    coord_Position.X = 0;
    coord_Position.Y = 0;
    SetConsoleCursorPosition (hOut, coord_Position);
}

void Timer(int numplayers)
{
    if (elapsedTime > D_FoodTimer)
    {
        SpawnSpecial(numplayers);
        D_FoodTimer += 10.00000;
    }

    if (D_FoodTimer - elapsedTime < 0.5000)
    {
        gotoXY (coord_Special);
        cout << ' ';
        Array_2D[coord_Special.Y][coord_Special.X] = '0';
    }
}

void ScoreBoard()
{
    cls();
    string S_Name ="";
    cout << endl;
    cout << "                                        Enter your name: ";
    FlushInput();
    getline (cin, S_Name);
    cout << endl;

    HiScore(I_Score, S_Name);
}

void GameOver()
{
    cls();
    colour (0xC);
    if (B_P1_Over != true && B_P2_Over == true)
    {
        ifstream P1wins;
        string S_P1wins;
        P1wins.open ("AsciiArt\\Player1Wins.txt");
        while(!P1wins.eof())
        {
            getline (P1wins, S_P1wins);
            cout << S_P1wins << endl;
        }
        Sleep(2000);
        P1wins.close();
    }

    else if (B_P2_Over != true && B_P1_Over == true)
    {
        ifstream P2wins;
        string S_P2wins;
        P2wins.open ("AsciiArt\\Player2Wins.txt");
        while(!P2wins.eof())
        {
            getline (P2wins, S_P2wins);
            cout << S_P2wins << endl;
        }
        Sleep(2000);
        P2wins.close();
    }

    else if (B_P2_Over == true && B_P1_Over == true)
    {
        if (Vs_P1.size() > Vs_P2.size())
        {
            ifstream P1wins;
            string S_P1wins;
            P1wins.open ("AsciiArt\\Player1Wins.txt");
            while(!P1wins.eof())
            {
                getline (P1wins, S_P1wins);
                cout << S_P1wins << endl;
            }
            Sleep(2000);
            P1wins.close();
        }

        else if (Vs_P2.size() > Vs_P1.size())
        {
            ifstream P2wins;
            string S_P2wins;
            P2wins.open ("AsciiArt\\Player2Wins.txt");
            while(!P2wins.eof())
            {
                getline (P2wins, S_P2wins);
                cout << S_P2wins << endl;
            }
            Sleep(2000);
            P2wins.close();
        }

        else
        {
            ifstream Draw;
            string S_Draw;
            Draw.open ("AsciiArt\\Draw.txt");
            while(!Draw.eof())
            {
                getline (Draw, S_Draw);
                cout << S_Draw << endl;
            }
            Sleep(2000);
            Draw.close();
        }
    }
}

void GG(int numplayers)
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
    B_P1_Over = false;

    if (numplayers == 2)
    {
        I_Move2 = 4;
        I_Prev2 = 0;
        Vs_P2.erase(Vs_P2.begin(), Vs_P2.begin()+Vs_P2.size());
        B_P2_Over = false;
    }

    ChosenColour[0] = (0x7);
    ChosenColour2[0] = (0x7);

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