/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWin(int count, int arr[], int position)
{
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    bool win = false;
    if (arr[position] == 280)
    {
        win = true;
    }
    else
    {
        int new_position1 = position + arr[position];
        int new_position2 = position - arr[position];
        arr[position] = -1;
        if ((new_position1 <= count - 1) && (arr[new_position1] > 0))
        {
            if (canWin(count, arr, new_position1))
            {
                win = true;
            }
        }

        if (new_position2 >= 0)
        {
            if (canWin(count, arr, new_position2))
            {
                win = true;
            }
        }
    }

    return win;
}

int main()
{
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i)
    {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position) << endl;
}