#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>
#include "Framework\console.h"
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
int I_Frame = 0;

int I_Map;

WORD ChosenColour[] = {0x7};
WORD ChosenColour2[] = {0x7};

int GetInputMenu()
{
	char C_Choice;
	char C_Game;
	C_Choice = getch();

	switch(C_Choice)
	{
	case '1': // create a new function that ask the user to choose the gamemode he wants
		cls();
		GameAscii();
		C_Game = getch();
		if (C_Game == '1')
		{
			MapOptions();
			cls();
			ColourOptions();
			cls();
			Game1();
			MainMenu();
		}
		else if (C_Game == '2')
		{
			MapOptions();
			cls();
			ColourOptions2();
			cls();
			Game2();
			MainMenu();
		}
		else if (C_Game == '3')
		{
			MainMenu();
		}
		Sleep(200);
		break;
	case '2':	Instruction();
		C_Choice;
		C_Choice = getch();
		if (C_Choice != 27)
		{
			MainMenu();
		}
		else
		{
			MainMenu();
		}
		Sleep(200);
		break;
	case '3':	HighScore();
		C_Choice;
		C_Choice = getch();
		if (C_Choice != 27)
		{
			MainMenu();
		}
		else
		{
			MainMenu();
		}
		Sleep(200);
		break;
	case '4':
		{
			QuitGame();
		}
		break;
		Sleep(150);
		return I_Frame;
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
	cout << endl << endl << endl << endl << endl;
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

void MapOptions()
{
	cls();
    ifstream MapOptions;
    string S_MapOptions;
    MapOptions.open("AsciiArt\\MapOptions.txt");
    while(!MapOptions.eof())
    {
        getline(MapOptions,S_MapOptions);
        cout << S_MapOptions << endl;
    }


	char C_Maps;
	C_Maps = getch();

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
		} break;
	default :
		{
			I_Map = 1;
		} break;
	}
}

void CreateMap()
{
	colour (0x7);
	cout << "0 - Blank" << endl;
	colour (0x2);
	cout << "1 - " << char(178);
	colour (0x6);
	cout << "2 - " << char(254);
	colour (0xC);
	cout << "3 - " << char(219);
	

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
	C_Colour = getch();
	switch (C_Colour - 48)
	{
		case BLUE: colour(0x9); ChosenColour[0] = 0x9;
			break;
		case CYAN: colour(0xB); ChosenColour[0] = 0xB;
			break;
		case PURPLE: colour(0xD); ChosenColour[0] = 0xD;
			break;
		case YELLOW: colour(0xE); ChosenColour[0] = 0xE;
			break;
	}
}

void ColourOptions2()
{
	ifstream Player1;
    ifstream Player2;
    ifstream Blue;
    ifstream Blue2;
    ifstream Cyan;
    ifstream Cyan2;
    ifstream Purple;
    ifstream Purple2;
    ifstream Yellow;
    ifstream Yellow2;
    ifstream CYC;
    ifstream CYC2;
    string S_Player1;
    string S_Player2;
    string S_Blue;
    string S_Blue2;
    string S_Cyan;
    string S_Cyan2;
    string S_Purple;
    string S_Purple2;
    string S_Yellow;
    string S_Yellow2;
    string S_CYC;
    string S_CYC2;
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
	C_Colour = getch();
	switch (C_Colour - 48)
	{
		case BLUE: colour(0x9); ChosenColour[0] = 0x9;
			break;
		case CYAN: colour(0xB); ChosenColour[0] = 0xB;
			break;
		case PURPLE: colour(0xD); ChosenColour[0] = 0xD;
			break;
		case YELLOW: colour(0xE); ChosenColour[0] = 0xE;
			break;
	}

    cls();
	colour (0x2);
	Player2.open("AsciiArt\\Player2.txt");
    while(!Player2.eof())
    {
        getline(Player2,S_Player2);
        cout << S_Player2 << endl;
    }
	colour(0x9);
	Blue2.open("AsciiArt\\Blue.txt");
    while(!Blue2.eof())
    {
        getline(Blue2,S_Blue2);
        cout << S_Blue2 << endl;
    }
	colour(0xB);
	Cyan2.open("AsciiArt\\Cyan.txt");
    while(!Cyan2.eof())
    {
        getline(Cyan2,S_Cyan2);
        cout << S_Cyan2 << endl;
    }
	colour(0xD);
	Purple2.open("AsciiArt\\Purple.txt");
    while(!Purple2.eof())
    {
        getline(Purple2,S_Purple2);
        cout << S_Purple2 << endl;
    }
	colour(0xE);
	Yellow2.open("AsciiArt\\Yellow.txt");
    while(!Yellow2.eof())
    {
        getline(Yellow2,S_Yellow2);
        cout << S_Yellow2 << endl;
    }
	colour(0x2);
	CYC2.open("AsciiArt\\CYC.txt");
    while(!CYC2.eof())
    {
        getline(CYC2,S_CYC2);
        cout << S_CYC2 << endl;
    }
	C_Colour = '0';
	C_Colour = getch();
	switch (C_Colour - 48)
	{
		case BLUE: colour(0x9); ChosenColour2[0] = 0x9;
			break;
		case CYAN: colour(0xB); ChosenColour2[0] = 0xB;
			break;
		case PURPLE: colour(0xD); ChosenColour2[0] = 0xD;
			break;
		case YELLOW: colour(0xE); ChosenColour2[0] = 0xE;
			break;
	}
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