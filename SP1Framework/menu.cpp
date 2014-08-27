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
	char I_Choice;
	I_Choice = getch();

		switch(I_Choice)
		{
		case '1': // create a new function that ask the user to choose the gamemode he wants
			cls();
			cout << "Press 1 for single player, Press 2 for 2 players" << endl;
            I_Choice = '0';
            I_Choice = getch();
			if (I_Choice == '1')
			{
				Game1();
			}
			else if (I_Choice == '2')
			{
				Game2();
			}
			Sleep(200);
			break;
		case '2':	Instruction();
            I_Choice = '0';
            I_Choice = getch();
            if (I_Choice != 27)
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
            I_Choice = '0';
            I_Choice = getch();
            if (I_Choice != 27)
            {
                MainMenu();
            }
            else
            {
                MainMenu();
            }
			Sleep(200);
			break;
		case '4':	Options();
            I_Choice = '0';
            I_Choice = getch();
            if (I_Choice != 27)
            {
                MainMenu();
            }
            else
            {
                MainMenu();
            }
			Sleep(200);
			break;
		case '5':	colour(0x02);
			QuitGame();
			break;
		}
	Sleep(150);
	return I_Frame;
}

void MainMenu()
{
	cls();
	string S_Menu[5] = {"1)                                    _____          ______  __   __\n                                     |_____] |      |______|   \\_/  \n                                     |       |_____ |      |    |" , //"PLAY" Ascii Art.
		"2)           _____ __   _ _______ _______  ______ _     _ _______ _______ _____  _____  __   _\n               |   | \\  | |______    |    |_____/ |     | |          |      |   |     | | \\  |\n             __|__ |  \\_| ______|    |    |    \\_ |_____| |_____     |    __|__ |_____| |  \\_|" ,//"INSTRUCTION" Ascii Art.
		"3)               _     _ _____  ______ _     _ _______ _______  _____   ______ _______\n                 |_____|   |   |  ____ |_____| |______ |       |     | |_____/ |______\n                 |     | __|__ |_____| |     | ______| |_____  |_____| |    \\_ |______" , //"HIGHSCORE" Ascii Art.
		"4)                        _____   _____  _______ _____  _____  __   _  _______\n                         |     | |_____]    |      |   |     | | \\  | |______\n                         |_____| |          |    __|__ |_____| |  \\_|  ______|",
		"5)                                     ______ _     _ _____ _______\n                                      |______  \\___/    |      |  \n                                      |______ _/   \\_ __|__    |"}; //"EXIT" Ascii Art.
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
	cout <<    "				            Press the any key to return to the main menu!" << endl;
	cout << endl;
}

void DisplayHighScore()
{
	// Read all the files and display them
	// cout the name of the map also tyvm
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

void Options()
{
	cls();
	cout << "                            Press any key to return to the main menu!" << endl; 
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

	PrintScore.open ("HighScore\\CageHighscore.txt");
	PrintName.open("HighScore\\CageName.txt");

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
	for(int q = 0; q < 5; q++)
	{
		while(getline(PrintName, S_DataName))
		{
			A_StoreName[x] = S_DataName;
			x++;
		}
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

	NewScore.open ("HighScore\\CageHighscore.txt");
	NewName.open("HighScore\\CageName.txt");


	for(int p = 0; p < 5; p++)
	{
		NewScore << VI_Score[p] << endl;
		NewName << VS_Name[p] << endl;
	}

	VI_Score.erase(VI_Score.begin(),VI_Score.begin()+5);
	VS_Name.erase(VS_Name.begin(),VS_Name.begin()+5);

	NewScore.close();
	NewName.close();

	PrintScore.open ("HighScore\\CageHighscore.txt");
	PrintName.open("HighScore\\CageName.txt");

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