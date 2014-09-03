#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "Framework\console.h"
#include "Framework\sound.h"
#include "game.h"
#include "menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stringstream;

int I_Gamemode = 0;
int I_Map;

bool B_Complete = false;
COORD coord_Block;

char **Custom_2D;

bool KeyPressedMap[E_MAPCOUNT];

WORD ChosenColour[] = {0x7};
WORD ChosenColour2[] = {0x7};

void GetInputMenu()
{
	char C_Choice;
	char C_Game;
	C_Choice = getch();

	switch(C_Choice)
	{
	case '1': // create a new function that ask the user to choose the gamemode he want
		cls();
        playGameSound(S_CHOICE);
		GameAscii();
		C_Game = getch();
		if (C_Game == '1')
		{   
            playGameSound(S_CHOICE);
			MapOptions();
			FlushInput();
			cls();
			ColourOptions();
			FlushInput();
			cls();
			Sleep(120);
			Game1();
			break;
		}
		else if (C_Game == '2')
		{
            playGameSound(S_CHOICE);
			MapOptions();
			FlushInput();
			cls();
			ColourOptions2();
			FlushInput();
			cls();
			Sleep(120);
			Game2();
			FlushInput();
			break;
		}
		else
		{
			break;
		}
		Sleep(200);
		break;
	case '2':	Instruction();
        playGameSound(S_CHOICE);
		C_Choice;
		C_Choice = getch();
		if (C_Choice != 27)
		{
            playGameSound(S_CHOICE);
		}
		else
		{
            playGameSound(S_CHOICE);
		}
		Sleep(200);
		break;
	case '3':
        playGameSound(S_CHOICE);
        HighScore();
		C_Choice;
		C_Choice = getch();
		if (C_Choice != 27)
		{
            playGameSound(S_CHOICE);
		}
		else
		{
            playGameSound(S_CHOICE);
		}
		Sleep(200);
		break;
	case '4':
		{
			if (B_Complete == true)
			{
				ClearCustomMap();
			}
            playGameSound(S_CHOICE);
			QuitGame();
		}
		break;
		Sleep(150);
	}
}

void MainMenu()
{
	cls();
	colour(0x2);
	ifstream Snake;
	string S_Snake;
	Snake.open("AsciiArt\\Snake.txt");
	while(!Snake.eof())
	{
		getline(Snake,S_Snake);
		cout << S_Snake << endl;
	}
	Sleep (200);
}

void Instruction()
{
	cls();
	ifstream Instruction;
	string S_Instruction;
	Instruction.open("AsciiArt\\Instructions.txt");
	while(!Instruction.eof())
	{
		getline(Instruction , S_Instruction);
		cout << S_Instruction << endl;
	}
	cout << endl;
}

void Score()
{
	COORD coord_Score;
	
	coord_Score.X = 0;
	coord_Score.Y = 40;

	gotoXY(coord_Score);
	cout << "Your score: ";
}

void HighScore()
{
	cls();
	ifstream HighScore;
	string S_HighScore;
	HighScore.open("AsciiArt\\HighScore.txt");
	while(!HighScore.eof())
	{
		getline(HighScore,S_HighScore);
		cout << S_HighScore << endl;
	}
	cout << endl;
	DisplayHighScore();
	cout << "                             Press the any key to return to the main menu!" << endl;
	cout << endl;
}

void DisplayHighScore()
{
	ifstream DisplayScore;
	ifstream DisplayName;
	string S_DisplayScore;
	string S_DisplayName;

	DisplayScore.open("Highscore\\CageScore.txt");
	DisplayName.open("Highscore\\CageName.txt");
	cout << endl << endl;
	cout << "                                            CAGE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "                                               " << S_DisplayName << "  " << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\ChristmasScore.txt");
	DisplayName.open("Highscore\\ChristmasName.txt");
	cout << endl << endl;
	cout << "                                            CHRISTMAS HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore,S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "                                               " << S_DisplayName << "  " << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\GardenScore.txt");
	DisplayName.open("Highscore\\GardenName.txt");
	cout << endl << endl;
	cout << "                                            GARDEN HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "                                               " << S_DisplayName << "  " << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\MazeScore.txt");
	DisplayName.open("Highscore\\MazeName.txt");
	cout << endl << endl;
	cout << "                                            MAZE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "                                              " << S_DisplayName << "  " << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\MineScore.txt");
	DisplayName.open("Highscore\\MineName.txt");
	cout << endl << endl;
	cout << "                                            MINE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "                                              " << S_DisplayName << "  " << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();
}

void HiScore(int I_PlayerScore, string S_Name)
{
	//Highscore
	int A_Store[5] = {0};
	int I_Temp = 0;

	vector<int> VI_Score;
	vector<int> VI_Replace;
	ifstream PrintScore;
	ofstream NewScore;
	string S_Data;

	int I_StoreScore = 0;
	//Player Name
	string A_StoreName[5] = {" "};
	string S_Temp = " ";

	vector<string> VS_Name;
	ifstream PrintName;
	ofstream NewName;
	string S_DataName;

	int I_StoreName = 0;

	cout << "					Your score is : " << I_PlayerScore << endl;
	cout << endl;

	switch(I_Map)
	{
	case 1: 
		{
			PrintScore.open ("Highscore\\CageScore.txt");
			PrintName.open ("Highscore\\CageName.txt");
		} break;
	case 2:
		{
			PrintScore.open ("Highscore\\ChristmasScore.txt");
			PrintName.open ("Highscore\\ChristmasName.txt");
		} break;
	case 3:
		{
			PrintScore.open ("Highscore\\GardenScore.txt");
			PrintName.open ("Highscore\\GardenName.txt");
		} break;
	case 4:
		{
			PrintScore.open ("Highscore\\MazeScore.txt");
			PrintName.open ("Highscore\\MazeName.txt");
		} break;
	case 5:
		{
			PrintScore.open ("Highscore\\MineScore.txt");
			PrintName.open ("Highscore\\MineName.txt");
		} break;
	}

	//Storing Score into Array

	while(getline(PrintScore, S_Data) && I_StoreScore != 5)
	{
		stringstream ss(S_Data);
		while ( ss >> A_Store[I_StoreScore] )
		{
			VI_Replace.push_back(A_Store[I_StoreScore]);
			I_StoreScore++;
		}
	}

	//Storing Name into Array
	while(getline(PrintName, S_DataName) && I_StoreName !=5)
	{
		A_StoreName[I_StoreName] = S_DataName;
		I_StoreName++;
	}

	for (int x = 0; x < 5; x++)
	{
		if(I_PlayerScore >= A_Store[x])
		{
			VI_Score.push_back(I_PlayerScore);
			VS_Name.push_back(S_Name);
			for(int j = x; j < VI_Replace.size();j++)
			{
				I_Temp = A_Store[j];
				S_Temp = A_StoreName[j];
				VI_Score.push_back(I_Temp);
				VS_Name.push_back(S_Temp);
				if(VI_Score.size() == 5)
				{
					break;
				}
			}
		}
		else
		{
			VI_Score.push_back(A_Store[x]);
			VS_Name.push_back(A_StoreName[x]);
		}
	}

	VI_Replace.erase(VI_Replace.begin(),VI_Replace.begin()+5);

	PrintScore.close();
	PrintName.close();

	switch(I_Map)
	{
	case 1: 
		{
			NewScore.open ("Highscore\\CageScore.txt");
			NewName.open ("Highscore\\CageName.txt");
		} break;
	case 2:
		{
			NewScore.open ("Highscore\\ChristmasScore.txt");
			NewName.open ("Highscore\\ChristmasName.txt");
		} break;
	case 3:
		{
			NewScore.open ("Highscore\\GardenScore.txt");
			NewName.open ("Highscore\\GardenName.txt");
		} break;
	case 4:
		{
			NewScore.open ("Highscore\\MazeScore.txt");
			NewName.open ("Highscore\\MazeName.txt");
		} break;
	case 5:
		{
			NewScore.open ("Highscore\\MineScore.txt");
			NewName.open ("Highscore\\MineName.txt");
		} break;
	}

	for(int p = 0; p < 5; p++)
	{
		NewScore << VI_Score[p] << endl;
		NewName << VS_Name[p] << endl;
	}

	VI_Score.erase(VI_Score.begin(),VI_Score.begin()+5);
	VS_Name.erase(VS_Name.begin(),VS_Name.begin()+5);

	NewScore.close();
	NewName.close();

	switch(I_Map)
	{
	case 1: 
		{
			PrintScore.open ("Highscore\\CageScore.txt");
			PrintName.open ("Highscore\\CageName.txt");
		} break;
	case 2:
		{
			PrintScore.open ("Highscore\\ChristmasScore.txt");
			PrintName.open ("Highscore\\ChristmasName.txt");
		} break;
	case 3:
		{
			PrintScore.open ("Highscore\\GardenScore.txt");
			PrintName.open ("Highscore\\GardenName.txt");
		} break;
	case 4:
		{
			PrintScore.open ("Highscore\\MazeScore.txt");
			PrintName.open ("Highscore\\MazeName.txt");
		} break;
	case 5:
		{
			PrintScore.open ("Highscore\\MineScore.txt");
			PrintName.open ("Highscore\\MineName.txt");
		} break;
	}

	while(!PrintScore.eof())
	{
		getline(PrintScore, S_Data);
		getline(PrintName, S_DataName);
		cout << "					" << S_DataName << "	" << S_Data << endl;
		Sleep (1000);
	}

	PrintScore.close();
	PrintName.close();
}

void QuitGame()
{
	cls();
	ifstream QuitGame;
	string S_QuitGame;
	QuitGame.open("AsciiArt\\QuitGame.txt");
	while(!QuitGame.eof())
	{
		getline(QuitGame,S_QuitGame);
		cout << S_QuitGame << endl;
	}
	cout << "                                      ";
	exit(0);
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

	colour (0x2);
}

void GetMap()
{
	KeyPressedMap[E_MAPUP] = isKeyPressed(VK_UP);
	KeyPressedMap[E_MAPDOWN] = isKeyPressed(VK_DOWN);
	KeyPressedMap[E_MAPLEFT] = isKeyPressed(VK_LEFT);
	KeyPressedMap[E_MAPRIGHT] = isKeyPressed(VK_RIGHT);
	KeyPressedMap[E_MAPESCAPE] = isKeyPressed(VK_RETURN);
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

void MapOptions()
{
	cls();
	char C_Maps;
	bool B_ValidInput = false;

	if (B_Complete == false)
	{
		ifstream MapOptions;
		string S_MapOptions;
		MapOptions.open("AsciiArt\\MapOptions.txt");
		while(!MapOptions.eof())
		{
			getline(MapOptions,S_MapOptions);
			cout << S_MapOptions << endl;
		}
		
		while (B_ValidInput == false)
		{
			C_Maps = getch();

			if (C_Maps >= '1' && C_Maps <= '6')
			{
				B_ValidInput = true;
			}
		}

		switch(C_Maps)
		{
		case '1':
			{
				I_Map = 1;
			} break;
		case '2':
            {
				I_Map = 2;
			} break;
		case '3':
			{
				I_Map = 3;
			} break;
		case '4':
			{
				I_Map = 4;
			} break;
		case '5':
			{
				I_Map = 5;
			} break;
		case '6':
			{
				CreateMap();
				I_Map = 6;
			} break;
		default :
			{
				I_Map = 1;
			} break;
		}
		B_ValidInput = false;
	}
	
	else if (B_Complete == true)
	{
		ifstream MapOptions;
		string S_MapOptions;
		MapOptions.open("AsciiArt\\NewMapOptions.txt");
		while(!MapOptions.eof())
		{
			getline(MapOptions,S_MapOptions);
			cout << S_MapOptions << endl;
		}

		while (B_ValidInput == false)
		{
			C_Maps = getch();

			if (C_Maps >= '1' && C_Maps <= '7')
			{
				B_ValidInput = true;
			}
		}

	switch(C_Maps)
	{
		case '1':
			{
				playGameSound(S_CHOICE);
				I_Map = 1;
			} break;
		case '2':
			{
				playGameSound(S_CHOICE);
				I_Map = 2;
			} break;
		case '3':
			{
				playGameSound(S_CHOICE);
				I_Map = 3;
			} break;
		case '4':
			{
				playGameSound(S_CHOICE);
				I_Map = 4;
			} break;
		case '5':
			{
				playGameSound(S_CHOICE);
				I_Map = 5;
			} break;
		case '6':
			{
				I_Map = 6;
			} break;
		case '7':
			{
				B_Complete = false;
				ClearCustomMap();
				CreateMap();
			} break;
		default :
			{
				playGameSound(S_CHOICE);
				I_Map = 1;
			} break;
		}
		B_ValidInput = false;
    }
}

void ColourOptions()
{
	ifstream Player1;
	ifstream Blue;
	ifstream Cyan;
	ifstream Purple;
	ifstream Yellow;
	ifstream CYC;
	string S_Player1;
	string S_Blue;
	string S_Cyan;
	string S_Purple;
	string S_Yellow;
	string S_CYC;
	Player1.open("AsciiArt\\Player1.txt");
	while(!Player1.eof())
	{
		getline(Player1,S_Player1);
		cout << S_Player1 << endl;
	}
	colour(0x9);
	Blue.open("AsciiArt\\Blue.txt");
	while(!Blue.eof())
	{
		getline(Blue,S_Blue);
		cout << S_Blue << endl;
	}
	colour(0xB);
	Cyan.open("AsciiArt\\Cyan.txt");
	while(!Cyan.eof())
	{
		getline(Cyan,S_Cyan);
		cout << S_Cyan << endl;
	}
	colour(0xD);
	Purple.open("AsciiArt\\Purple.txt");
	while(!Purple.eof())
	{
		getline(Purple,S_Purple);
		cout << S_Purple << endl;
	}
	colour(0xE);
	Yellow.open("AsciiArt\\Yellow.txt");
	while(!Yellow.eof())
	{
		getline(Yellow,S_Yellow);
		cout << S_Yellow << endl;
	}
	colour(0x2);
	CYC.open("AsciiArt\\CYC.txt");
	while(!CYC.eof())
	{
		getline(CYC,S_CYC);
		cout << S_CYC << endl;
	}
	char C_Colour = '0';
	bool B_ValidInput = false;
	while (B_ValidInput == false)
	{
		C_Colour = getch();

		if (C_Colour >= '1' && C_Colour <= '4')
		{
			B_ValidInput = true;
		}
	}
	switch (C_Colour - 48)
	{
		case BLUE: playGameSound(S_CHOICE); colour(0x9); ChosenColour[0] = 0x9;
			break;
		case CYAN: playGameSound(S_CHOICE); colour(0xB); ChosenColour[0] = 0xB;
			break;
		case PURPLE: playGameSound(S_CHOICE); colour(0xD); ChosenColour[0] = 0xD;
			break;
		case YELLOW: playGameSound(S_CHOICE); colour(0xE); ChosenColour[0] = 0xE;
			break;
        default: playGameSound(S_CHOICE); colour(0xB); ChosenColour[0] = 0xB;
            break;

	}
	B_ValidInput = false;
	Player1.close();
	Blue.close();
	Cyan.close();
	Purple.close();
	Yellow.close();
	CYC.close();
}

void ColourOptions2()
{
	ifstream Player;
	ifstream Blue;
	ifstream Cyan;
	ifstream Purple;
	ifstream Yellow;
	ifstream CYC;
	string S_Player;
	string S_Blue;
	string S_Cyan;
	string S_Purple;
	string S_Yellow;
	string S_CYC;

	Player.open("AsciiArt\\Player1.txt");
	while(!Player.eof())
	{
		getline(Player,S_Player);
		cout << S_Player << endl;
	}

	colour(0x9);
	Blue.open("AsciiArt\\Blue.txt");
	while(!Blue.eof())
	{
		getline(Blue,S_Blue);
		cout << S_Blue << endl;
	}

	colour(0xB);
	Cyan.open("AsciiArt\\Cyan.txt");
	while(!Cyan.eof())
	{
		getline(Cyan,S_Cyan);
		cout << S_Cyan << endl;
	}

	colour(0xD);
	Purple.open("AsciiArt\\Purple.txt");
	while(!Purple.eof())
	{
		getline(Purple,S_Purple);
		cout << S_Purple << endl;
	}

	colour(0xE);
	Yellow.open("AsciiArt\\Yellow.txt");
	while(!Yellow.eof())
	{
		getline(Yellow,S_Yellow);
		cout << S_Yellow << endl;
	}

	colour(0x2);
	CYC.open("AsciiArt\\CYC.txt");
	while(!CYC.eof())
	{
		getline(CYC,S_CYC);
		cout << S_CYC << endl;
	}

	char C_Colour = '0';
	bool B_ValidInput = false;
	while (B_ValidInput == false)
	{
		C_Colour = getch();

		if (C_Colour >= '1' && C_Colour <= '4')
		{
			B_ValidInput = true;
		}
	}
	switch (C_Colour - 48)
	{
		case BLUE: playGameSound(S_CHOICE); colour(0x9); ChosenColour[0] = 0x9;
			break;
		case CYAN: playGameSound(S_CHOICE); colour(0xB); ChosenColour[0] = 0xB;
			break;
		case PURPLE: playGameSound(S_CHOICE); colour(0xD); ChosenColour[0] = 0xD;
			break;
		case YELLOW: playGameSound(S_CHOICE); colour(0xE); ChosenColour[0] = 0xE;
			break;
        default: playGameSound(S_CHOICE); colour(0xB); ChosenColour[0] = 0xB;
            break;
	}
	B_ValidInput = false;
	Player.close();
	Blue.close();
	Cyan.close();
	Purple.close();
	Yellow.close();
	CYC.close();
	S_Player = "";
	S_Blue = "";
	S_Cyan = "";
	S_Purple = "";
	S_Yellow = "";
	S_CYC = "";

	cls();
	colour (0x2);
	Player.open("AsciiArt\\Player2.txt");
	while(!Player.eof())
	{
		getline(Player, S_Player);
		cout << S_Player << endl;
	}

	colour(0x9);
	Blue.open("AsciiArt\\Blue.txt");
	while(!Blue.eof())
	{
		getline(Blue, S_Blue);
		cout << S_Blue << endl;
	}

	colour(0xB);
	Cyan.open("AsciiArt\\Cyan.txt");
	while(!Cyan.eof())
	{
		getline(Cyan, S_Cyan);
		cout << S_Cyan << endl;
	}

	colour(0xD);
	Purple.open("AsciiArt\\Purple.txt");
	while(!Purple.eof())
	{
		getline(Purple, S_Purple);
		cout << S_Purple << endl;
	}
	colour(0xE);

	Yellow.open("AsciiArt\\Yellow.txt");
	while(!Yellow.eof())
	{
		getline(Yellow, S_Yellow);
		cout << S_Yellow << endl;
	}
	colour(0x2);

	CYC.open("AsciiArt\\CYC.txt");
	while(!CYC.eof())
	{
		getline(CYC, S_CYC);
		cout << S_CYC << endl;
	}

	C_Colour = '0';
	while (B_ValidInput == false)
	{
		C_Colour = getch();

		if (C_Colour >= '1' && C_Colour <= '4')
		{
			B_ValidInput = true;
		}
	}
	switch (C_Colour - 48)
	{
		case BLUE: playGameSound(S_CHOICE); colour(0x9); ChosenColour2[0] = 0x9;
			break;
		case CYAN: playGameSound(S_CHOICE); colour(0xB); ChosenColour2[0] = 0xB;
			break;
		case PURPLE: playGameSound(S_CHOICE); colour(0xD); ChosenColour2[0] = 0xD;
			break;
		case YELLOW: playGameSound(S_CHOICE); colour(0xE); ChosenColour2[0] = 0xE;
			break;
        default: playGameSound(S_CHOICE); colour(0xB); ChosenColour2[0] = 0xB;
            break;
	}
	B_ValidInput = false;
	Player.close();
	Blue.close();
	Cyan.close();
	Purple.close();
	Yellow.close();
	CYC.close();
}

void GameAscii()
{
	ifstream Players;
	string S_Players;
	Players.open("AsciiArt\\Players.txt");
	while(!Players.eof())
	{
		getline(Players,S_Players);
		cout << S_Players << endl;
	}
}

void CallMenu()
{
	MainMenu();
	GetInputMenu();
}

void FlushInput()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hIn);
}