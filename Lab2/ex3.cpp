/*
 * Lab2 Ex3 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int square[MAX_LEN][MAX_LEN];

void initSquare(int len)
{
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            square[i][j] = 1;
        }
    }
}

void printSquare(int len)
{
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            cout << square[i][j] << " ";
        }
        cout << endl;
    }
}

// REQUIRES: the square with left-upper corner at (x,y)
//           and length len is within square[MAX_LEN][MAX_LEN]
// MODIFIES: square[][]
// EFFECTS: fully update the specified square
void updateSquare(int x, int y, int len)
{
    if (len >= 2)
    {
        int half_len = len / 2;
        for (int i = 0; i < half_len; i++)
        {
            for (int j = 0; j < half_len; j++)
            {
                square[x + i][y + j] = 0;
            }
        }
        updateSquare(x + half_len, y, half_len);
        updateSquare(x, y + half_len, half_len);
        updateSquare(x + half_len, y + half_len, half_len);
        // printSquare(8);
        // cout << endl
        //      << endl;
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int len = 1;
    for (int i = 0; i < n; i++)
    {
        len *= 2;
    }
    initSquare(len);
    updateSquare(0, 0, len);
    printSquare(len);
    return 0;
}
