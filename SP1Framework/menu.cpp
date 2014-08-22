#include<iostream>
#include<string>
#include "Framework\console.h"
#include "menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void MainMenu()
{
    for (bool B_Check = true; B_Check != false;)
    {
        string S_Menu[5] = {"Play" , "Instruction" , "Highscore", "Options", "Exit"};
        int I_Choice = 0;

        while(true)
        {
			system("cls");

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
                    colour(0x03);
                    cout << "						" << char(16) << Menu[i] << endl;
                }
                else
                {
                    colour(0x02);
                    cout << "						" << char(16)Menu[i] << endl;
                }
            }

            while(true)
            {
                if (GetAsyncKeyState(VK_UP) != 0)
                {
                    choice -= 1;
                    if (choice == -1)
                    {
                        choice = 4;
                    }
                    break;
                }

                else if (GetAsyncKeyState(VK_DOWN) != 0)
                {
                    choice += 1;
                    if (choice == 5)
                    {
                        choice = 0;
                    }
                    break;
                }

                else if (GetAsyncKeyState(VK_RETURN) != 0)
                {
                    switch(choice)
                    {
                    case 0:
                        {
                            game();
                            Sleep(1000);
                        } break;
                    case 1:
                        {
                            instruction();
							Sleep (200);
						} break;
                    case 2:
                        {
                            highscore();
                            Sleep (200);
                        } break;
					case 3:
						{
							options();
							Sleep(200);
						} break;
                    case 4:
                        {
                            colour(0x02);
                            quitGame();
                            g_quitGame = true;
                        } break;
                    }
                }
            }
            Sleep(150);
        }
    }
}

void instruction()
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
    cout << "                       Press UP or Down arrow keys to return to the main menu!" << endl;
    cout << "                            Press UP arrow key to return to the main menu!" << endl;
}

void quitGame()
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
    g_quitGame = true;
    exit(0);
}

void options()
{
	cls();
	colourOptions();
	cout << "                            Press UP arrow key to return to the main menu!" << endl; 
}

void colourOptions()
{
	int color = 0;

	colour(0xB);
	cout << "						1) OOOOOO" << endl;
	colour(0xC);
	cout << "						2) OOOOOO" << endl;
	colour(0xD);
	cout << "						3) OOOOOO" << endl;
	colour(0xE);
	cout << "						4) OOOOOO" << endl;
	colour(0x7);
	cout << "					Choose your colour: ";
	cin >> color;
	cout << "						You have chosen ";
	switch (color)
	{
		case LIGHT_BLUE: colour(0xB); chosencolour[0] = 0xB;
			break;
		case RED: colour(0xC); chosencolour[0] = 0xC;
			break;
		case PINK: colour(0xD); chosencolour[0] = 0xD;
			break;
		case YELLOW: colour(0xE); chosencolour[0] = 0xE;
			break;
	}
	cout << "OOOOOO" << endl;
	colour(0x7);
}