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

int GetInputMenu()
{
	char C_Choice;
	C_Choice = getch();

	switch(C_Choice)
	{
	case '1': // create a new function that ask the user to choose the gamemode he wants
		cls();
		GameAscii();
		C_Choice = '0';
		C_Choice = getch();
		if (C_Choice == '1')
		{
			Game1();
			MainMenu();
		}
		else if (C_Choice == '2')
		{
			Game2();
			MainMenu();
		}
		else if (C_Choice == '3')
		{
			MainMenu();
		}
			Sleep(200);
			break;
	case '2':	Instruction();
		C_Choice = '0';
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
		C_Choice = '0';
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
	case '4': Options();
		C_Choice = '0';
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
	case '5':
		{
			colour(0x02);
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
		string S_Menu[5] = {"  /|   \\\n   |    |      _____          _____  __   __\n   |    |     |_____] |      |_____|   \\_/\n   |    |     |       |_____ |     |    |\n  ---  /" , //"PLAY" Ascii Art.
			"  __   \\\n /  \\   |     _____ __   _ _______ _______  ______ _     _ _______ _______ _____  _____  __   _\n    /   |       |   | \\  | |______    |    |_____/ |     | |          |      |   |     | | \\  |\n   /    |     __|__ |  \\_| ______|    |    |    \\_ |_____| |_____     |    __|__ |_____| |  \\_|\n  /__  /" ,//"INSTRUCTION" Ascii Art.
			"  __   \\\n /  \\   |     _     _ _____  ______ _     _  _____   _____   _____   ______  ______\n    /   |     |_____|   |   |  ____ |_____| |_____  |       |     | |_____/ |______\n    \\   |     |     | __|__ |_____| |     |  _____| |_____  |_____| |    \\_ |______\n \\__/  /" , //"HIGHSCORE" Ascii Art.
			"   /|  \\\n  / |   |      _____   _____  _______ _____  _____   _   _  _____\n /__|__ |     |     | |_____]    |      |   |     | | \\  | |_____\n    |   |     |_____| |          |    __|__ |_____| |  \\_|  _____|\n    |  /", //"OPTIONS" Ascii Art.
			"  ___  \\\n |      |      ______ _     _ _____ _______\n |___   |     |______  \\___/    |      |\n     |  |     |______ _/   \\_ __|__    |\n  ___| /"}; //"EXIT" Ascii Art.
		int I_Choice = 0;
		colour(0x02);
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

		for (int i = 0; i < 5; ++i)
		{
			if (i == I_Choice)
			{
				colour(0x02);
				cout << S_Menu[i] << endl;
			}
			else
			{
				colour(0x02);
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
		colour(0x02);
		cls();
		cout <<	   "                         _   _ ___ ____ _   _ ____   ____ ___  ____  _____ " << endl;
		cout <<    "                        | | | |_ _/ ___| | | / ___| / ___/ _ \\|  _ \\| ____|" << endl;
		cout <<    "                        | |_| || | |  _| |_| \\___ \\| |  | | | | |_) |  _|  " << endl;
		cout <<    "                        |  _  || | |_| |  _  |___) | |__| |_| |  _ <| |___ " << endl;
		cout <<    "                        |_| |_|___\\____|_| |_|____/ \\____\\___/|_| \\_\\_____|" << endl;
		cout << endl;
		DisplayHighScore();
		cout <<    "				          Press the any key to return to the main menu!" << endl;
		cout << endl;
	}

	void DisplayHighScore()
	{
		ifstream DisplayScore;
		ifstream DisplayName;
		string S_DisplayScore;
		string S_DisplayName;

		DisplayScore.open("Highscore\\CageHighscore.txt");
		DisplayName.open("Highscore\\CageName.txt");
		cout << endl << endl;
		cout << "					CAGE HIGHSCORES" << endl << endl;
		while(!DisplayScore.eof())
		{
			getline(DisplayScore, S_DisplayScore);
			getline(DisplayName, S_DisplayName);
			cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
		}

		DisplayScore.close();
		DisplayName.close();

		DisplayScore.open("Highscore\\BoxHighscore.txt");
		DisplayName.open("Highscore\\BoxName.txt");
		cout << endl << endl;
		cout << "					BOX HIGHSCORES" << endl << endl;
		while(!DisplayScore.eof())
		{
			getline(DisplayScore,S_DisplayScore);
			getline(DisplayName, S_DisplayName);
			cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
		}

		DisplayScore.close();
		DisplayName.close();

		DisplayScore.open("Highscore\\MazeHighscore.txt");
		DisplayName.open("Highscore\\MazeName.txt");
		cout << endl << endl;
		cout << "					MAZE HIGHSCORES" << endl << endl;
		while(!DisplayScore.eof())
		{
			getline(DisplayScore, S_DisplayScore);
			getline(DisplayName, S_DisplayName);
			cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
		}

		DisplayScore.close();
		DisplayName.close();

		DisplayScore.open("Highscore\\MethHighscore.txt");
		DisplayName.open("Highscore\\MethName.txt");
		cout << endl << endl;
		cout << "					METH HIGHSCORES" << endl << endl;
		while(!DisplayScore.eof())
		{
			getline(DisplayScore, S_DisplayScore);
			getline(DisplayName, S_DisplayName);
			cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
		}

		DisplayScore.close();
		DisplayName.close();

		DisplayScore.open("Highscore\\SmileHighscore.txt");
		DisplayName.open("Highscore\\SmileName.txt");
		cout << endl << endl;
		cout << "					SMILE HIGHSCORES" << endl << endl;
		while(!DisplayScore.eof())
		{
			getline(DisplayScore, S_DisplayScore);
			getline(DisplayName, S_DisplayName);
			cout << "					" << S_DisplayName << "	" << S_DisplayScore << endl;
		}

		DisplayScore.close();
		DisplayName.close();
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

	int Options()
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
		cout << "				2.Smile"<< endl;
		cout << "					   #########" << endl;
		cout << "					   # +   + #" << endl;
		cout << "					   #*     *#" << endl;  
		cout << "					   # * * * #" << endl;
		cout << "					   #########" << endl;
		cout<<endl<<endl;
		cout << "				3.Maze" <<endl;
		cout << "					   #########" << endl;
		cout << "					   #_   ___#" << endl;
		cout << "					   #___  __#" << endl;
		cout << "					   #       #" << endl;
		cout << "					   #########" << endl;
		cout<<endl<<endl;
		cout << "				4.Meth"<<endl;
		cout << "					   #########" << endl;
		cout << "					   # ÷   + #" << endl;
		cout << "					   # x   - #" << endl;
		cout << "					   #       #" << endl;
		cout << "					   #########" << endl;
		cout <<endl<<endl;
		cout << "				5.Box" <<endl;
		cout << "					   #########" << endl;
		cout << "					   # #   # #" << endl;
		cout << "					   #       #" << endl;
		cout << "					   # #   # #" << endl;
		cout << "					   #########" << endl;
		cout<<endl<<endl;

		char C_maps;
		C_maps=getch();

		switch(C_maps)
		{
		case '1':
			{
				return 1;
			} break;
		case '2':
			{
				return 2;
			} break;
		case '3':
			{
				return 3;
			} break;
		case '4':
			{
				return 4;
			} break;
		case '5':
			{
				return 5;
			} break;

		default :
			{
				return 1;
			} break;
		}
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

		int z = 0;
		//Player Name
		string A_StoreName[5] = {" "};
		string S_Temp = " ";

		vector<string> VS_Name;
		ifstream PrintName;
		ofstream NewName;
		string S_DataName;

		int x = 0;

		cout << "					Your score is : " << I_PlayerScore << endl;
		cout << endl;

		PrintScore.open ("Highscore\\CageHighscore.txt");
		PrintName.open("Highscore\\CageName.txt");

		//Storing Score into Array
		for(int q = 0; q < 5; q++)
		{
			while(getline(PrintScore, S_Data))
			{
				stringstream ss(S_Data);
				while ( ss >> A_Store[z] )
				{
					VI_Replace.push_back(A_Store[z]);
					z++;
				}
			}
		}

		//Storing Name into Array
		while(getline(PrintName, S_DataName) && x !=5)
		{
			A_StoreName[x] = S_DataName;
			x++;
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

		NewScore.open ("Highscore\\CageHighscore.txt");
		NewName.open("Highscore\\CageName.txt");


		for(int p = 0; p < 5; p++)
		{
			NewScore << VI_Score[p] << endl;
			NewName << VS_Name[p] << endl;
		}

		VI_Score.erase(VI_Score.begin(),VI_Score.begin()+5);
		VS_Name.erase(VS_Name.begin(),VS_Name.begin()+5);

		NewScore.close();
		NewName.close();

		PrintScore.open ("Highscore\\CageHighscore.txt");
		PrintName.open("Highscore\\CageName.txt");

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