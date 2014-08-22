#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stringstream;

void hiscore(int playerscore)
{
	int store[5] = {0};
	int temp = 0;

	vector<int> Score;
	vector<int> i;
	ifstream PrintScore;
	ofstream NewScore;
	string data;
	int z = 0;

	cout << "					Your score is : " << playerscore << endl;
	cout << endl;

	PrintScore.open ("Highscore.txt");

	for(int q = 0; q < 5; q++)
	{
		while(getline(PrintScore, data))
		{
			stringstream ss(data);
			while ( ss >> store[z] )
			{
				i.push_back(store[z]);
				z++;
			}
		}
	}

	for (int x = 0; x < 5; x++)
	{
		if(playerscore >= store[x])
		{
			Score.push_back(playerscore);

			for(int j = x; j < i.size();j++)
			{
				temp = store[j];
				Score.push_back(temp);
				if(Score.size() == 5)
				{
					break;
				}
			}
		}
		else
		{
			Score.push_back(store[x]);
		}
	}
	
	i.erase(i.begin(),i.begin()+5);

	PrintScore.close();
	NewScore.open ("Highscore.txt");

	for(int p = 0; p < 5; p++)
	{
		NewScore << Score[p] << endl;
	}

	Score.erase(Score.begin(),Score.begin()+5);

	NewScore.close();

	PrintScore.open("Highscore.txt");

	while(!PrintScore.eof()) //
	{
		getline(PrintScore, data);
		cout << "						" << data << endl;
	}
	PrintScore.close();
}