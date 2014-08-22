/*#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void Boarder()
{
    int map[30][100];

    for (int row = 0; row < 30; row++)
    {
        for (int col = 0; col < 100; col++)
        {
            if (row == 0 || col == 0 || col == 99 || row == 29)
            {
                map[row][col] = 1;
            }

            else
            {
                map[row][col] = 0;
            }

        }
    }

   for (int row = 0; row < 30; row++)
    {
        for (int col = 0; col < 100; col++)
        {
            if (map[row][col] == 1)
            {
                cout << "*";
            }

            else
            {
                cout << " ";
            }
        }
    }

}*/