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
	string S_Menu[4] = {"  /|   \\\n   |    |      _____          _____  __   __\n   |    |     |_____] |      |_____|   \\_/\n   |    |     |       |_____ |     |    |\n  ---  /" , //"PLAY" Ascii Art.
		"  __   \\\n /  \\   |     _____ __   _ _______ _______  ______ _     _ _______ _______ _____  _____  __   _\n    /   |       |   | \\  | |______    |    |_____/ |     | |          |      |   |     | | \\  |\n   /    |     __|__ |  \\_| ______|    |    |    \\_ |_____| |_____     |    __|__ |_____| |  \\_|\n  /__  /" ,//"INSTRUCTION" Ascii Art.
		"  __   \\\n /  \\   |     _     _ _____  ______ _     _  _____   _____   _____   ______  ______\n    /   |     |_____|   |   |  ____ |_____| |_____  |       |     | |_____/ |______\n    \\   |     |     | __|__ |_____| |     |  _____| |_____  |_____| |    \\_ |______\n \\__/  /" , //"HIGHSCORE" Ascii Art.
		"  ___  \\\n |      |      ______ _     _ _____ _______\n |___   |     |______  \\___/    |      |\n     |  |     |______ _/   \\_ __|__    |\n  ___| /"}; //"EXIT" Ascii Art.
	int I_Choice = 0;
	colour(0x2);
	cout <<     "                       ******************************************************" << endl;
	cout <<     "                       *   ______                       __                  *" << endl;
	cout <<     "                       *  /      \\                     |  \\                 *" << endl;
	cout <<     "                       * |  SSSSSS\\ _______    ______  | kk   __   ______   *" << endl;
	cout <<     "                       * | SS___\\SS|       \\  |      \\ | kk  /  \\ /      \\  *" << endl;
	cout <<     "                       *  \\SS    \\ | nnnnnnn\\  \\aaaaaa\\| kk_/  kk|  eeeeee\\ *" << endl;
	cout <<     "                       *  _\\SSSSSS\\| nn  | nn /      aa| kk   kk | ee    ee *" << endl;
	cout <<     "                       * |  \\__| SS| nn  | nn|  aaaaaaa| kkkkkk\\ | eeeeeeee *" << endl;
	cout <<     "                       *  \\SS    SS| nn  | nn \\aa    aa| kk  \\kk\\ \\ee     \\ *" << endl;
	cout <<     "                       *   \\SSSSSS  \\nn   \\nn  \\aaaaaaa \\kk   \\kk  \\eeeeeee *" << endl; 
	cout <<     "                       *                                                    *" << endl;
	cout <<     "                       ******************************************************" << endl;

	for (int i = 0; i < 4; ++i)
	{
		if (i == I_Choice)
		{
			colour(0x2);
			cout << S_Menu[i] << endl;
		}
		else
		{
			colour(0x2);
			cout << S_Menu[i] << endl;
		}
	}
	Sleep (200);
}

void Instruction()
{
	cls();
	cout << endl << endl << endl << endl << endl;
	cout << "                        _           _                   _   _                  " << endl;
	cout << "                       (_)_ __  ___| |_ _ __ _   _  ___| |_(_) ___  _ __  ___  " << endl;
	cout << "                       | | '_ \\/ __| __| '__| | | |/ __| __| |/ _ \\| '_ \\/ __| " << endl;
	cout << "                       | | | | \\__ \\ |_| |  | |_| | (__| |_| | (_) | | | \\__ \\ " << endl;
	cout << "                       |_|_| |_|___/\\__|_|   \\__,_|\\___|\\__|_|\\___/|_| |_|___/ " << endl << endl;
	cout << "                                             How to play?" << endl << endl;
	cout << "                       Use the arrow keys to direct the movement of the snake."<< endl; 
	cout << "                   Eat more food produced randomly in the map to progress further."<< endl;
	cout << "                       The game gets more challenging as the snake gets longer."<< endl; 
	cout << "             However,the snake will die if it touches its own body or touches the walls."<< endl << endl;
	cout << "                             Press any key to return to the main menu!" << endl;
}

void HighScore()
{
	cls();
	cout << "                         _   _ ___ ____ _   _ ____   ____ ___  ____  _____ " << endl;
	cout << "                        | | | |_ _/ ___| | | / ___| / ___/ _ \\|  _ \\| ____|" << endl;
	cout << "                        | |_| || | |  _| |_| \\___ \\| |  | | | | |_) |  _|  " << endl;
	cout << "                        |  _  || | |_| |  _  |___) | |__| |_| |  _ <| |___ " << endl;
	cout << "                        |_| |_|___\\____|_| |_|____/ \\____\\___/|_| \\_\\_____|" << endl;
	cout << endl;
	DisplayHighScore();
	cout << "			Press the any key to return to the main menu!" << endl;
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
	cout << "				    CAGE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\ChristmasScore.txt");
	DisplayName.open("Highscore\\ChristmasName.txt");
	cout << endl << endl;
	cout << "				    CHRISTMAS HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore,S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\GardenScore.txt");
	DisplayName.open("Highscore\\GardenName.txt");
	cout << endl << endl;
	cout << "				    GARDEN HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\MazeScore.txt");
	DisplayName.open("Highscore\\MazeName.txt");
	cout << endl << endl;
	cout << "				    MAZE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
	}
	Sleep(500);

	DisplayScore.close();
	DisplayName.close();

	DisplayScore.open("Highscore\\MineScore.txt");
	DisplayName.open("Highscore\\MineName.txt");
	cout << endl << endl;
	cout << "				    MINE HIGHSCORES" << endl << endl;
	while(!DisplayScore.eof())
	{
		getline(DisplayScore, S_DisplayScore);
		getline(DisplayName, S_DisplayName);
		cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
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
	cout << endl << endl << endl << endl << endl << endl;
	cout << "                          _____ _   _    _    _   _ _  __ __   _____  _   _ " << endl;
	cout << "                         |_   _| | | |  / \\  | \\ | | |/ / \\ \\ / / _ \\| | | |" << endl;
	cout << "                           | | | |_| | / _ \\ |  \\| | ' /   \\ V / | | | | | |" << endl;
	cout << "                           | | |  _  |/ ___ \\| |\\  | . \\    | || |_| | |_| |" << endl;
	cout << "                           |_| |_| |_/_/   \\_\\_| \\_|_|\\_\\__ |_| \\___/ \\___/ " << endl;
	cout << "                                            / \\  | \\ | |  _ \\                " << endl;
	cout << "                                           / _ \\ |  \\| | | | |               " << endl;
	cout << "                                          / ___ \\| |\\  | |_| |               " << endl;
	cout << "                                ____  ___/_/___\\_\\_|_\\_|____/__   _______    " << endl;
	cout << "                              / ___|/ _ \\ / _ \\|  _ \\  | __ ) \\ / / ____|   " << endl;
	cout << "                             | |  _| | | | | | | | | | |  _ \\\\ V /|  _|     " << endl;
	cout << "                             | |_| | |_| | |_| | |_| | | |_) || | | |___    " << endl;
	cout << "                              \\____|\\___/ \\___/|____/  |____/ |_| |_____|   " << endl;
	cout << endl;
	cout << endl;
	cout << "                                      ";
	exit(0);
}

void MapOptions()
{
	cls();
	cout << endl << endl;
	cout << "				1.Cage" << endl;
	cout << "					   #########" << endl;
	cout << "					   #       #" << endl;
	cout << "					   #       #" << endl;
	cout << "					   #       #" << endl;
	cout << "					   #########" << endl;
	cout <<endl<<endl;
	cout << "				2.Christmas"<< endl;
	cout << "					   #########" << endl;
	cout << "					   # +   + #" << endl;
	cout << "					   #*     *#" << endl;  
	cout << "					   # * * * #" << endl;
	cout << "					   #########" << endl;
	cout<<endl<<endl;
	cout << "				3.Garden" <<endl;
	cout << "					   #########" << endl;
	cout << "					   #_   ___#" << endl;
	cout << "					   #___  __#" << endl;
	cout << "					   #       #" << endl;
	cout << "					   #########" << endl;
	cout<<endl<<endl;
	cout << "				4.Maze"<<endl;
	cout << "					   #########" << endl;
	cout << "					   # ÷   + #" << endl;
	cout << "					   # x   - #" << endl;
	cout << "					   #       #" << endl;
	cout << "					   #########" << endl;
	cout <<endl<<endl;
	cout << "				5.Mine" <<endl;
	cout << "					   #########" << endl;
	cout << "					   #  * *  #" << endl;
	cout << "					   # * * * #" << endl;
	cout << "					   #  * *  #" << endl;
	cout << "					   #########" << endl;
	cout<<endl<<endl;

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
	cout << "				Player 1 choose the colour of your snake!" << endl;
	colour(0x9);
	cout << "						1) OOOOOO" << endl;
	colour(0xB);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x2);
	char C_Colour = '0';
	C_Colour = getch();
	cout << "						You have chosen ";
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
	cout << "OOOOOO" << endl;
}

void ColourOptions2()
{
	cout << "				Player 1 choose the colour of your snake!" << endl;
	colour(0x9);
	cout << "						1) OOOOOO" << endl;
	colour(0xB);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x2);
	cout << "					Choose your colour: ";
	char C_Colour = '0';
	C_Colour = getch();
	cout << "						You have chosen ";
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
	cout << "OOOOOO" << endl;

	cls();
	colour (0x2);
	cout << "				Player 2 choose the colour of your snake!" << endl;
	colour(0x9);
	cout << "						1) OOOOOO" << endl;
	colour(0xB);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x2);
	cout << "					Choose your colour: ";
	C_Colour = '0';
	C_Colour = getch();
	cout << "						You have chosen ";
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
	cout << "OOOOOO" << endl;
}

void GameAscii()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout <<               "                       **********************************************************"   << endl;
	cout <<               "                       *               ______                                   *"   << endl;                 
	cout <<               "                       *              |   __ \\.----.-----.-----.-----.          *"  << endl; 
	cout <<               "                       *              |    __/|   _|  -__|__ --|__ --|          *"   << endl;
	cout <<               "                       *              |___|   |__| |_____|_____|_____|          *"   << endl;
	cout <<               "                       *                                                        *"   << endl;
	cout <<               "                       *   ____               __                                *"   << endl;
	cout <<               "                       *  |_   |      .-----.|  |.---.-.--.--.-----.----.       *"   << endl;
	cout <<               "                       *   _|  |_     |  _  ||  ||  _  |  |  |  -__|   _|       *"   << endl;
	cout <<               "                       *  |______|    |   __||__||___._|___  |_____|__|         *"   << endl;
	cout <<               "                       *              |__|             |_____|                  *"   << endl;
	cout <<               "                       *                                                        *"   << endl;
	cout <<               "                       *              .-----.----.                              *"   << endl;
	cout <<               "                       *              |  _  |   _|                              *"   << endl;
	cout <<               "                       *              |_____|__|                                *"   << endl;
	cout <<               "                       *                                                        *"   << endl;
	cout <<               "                       *   ______             __                                *"   << endl;
	cout <<               "                       *  |__    |    .-----.|  |.---.-.--.--.-----.----.-----. *"   << endl;
	cout <<               "                       *  |    __|    |  _  ||  ||  _  |  |  |  -__|   _|__ --| *"   << endl;
	cout <<               "                       *  |______|    |   __||__||___._|___  |_____|__| |_____| *"   << endl;
	cout <<               "                       *              |__|             |_____|                  *"   << endl;
	cout <<               "                       *                                                        *"   << endl;
	cout <<               "                       **********************************************************"   << endl << endl;
	cout <<               "                                      Press 3 to go back to main menu            "   << endl;
}