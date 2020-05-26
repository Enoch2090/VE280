/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
bool *generateIsPrime(bool *LUT)
{
    LUT[0] = false;
    LUT[1] = false;
    for (int i = 2; i < RANGE; i++)
    {
        LUT[i] = true;
    } // Mark all indexes as prime.
    int smallest_prime = 0;
    while (LUT[99221] == true)
    {
        for (int i = 2; i < RANGE; i++)
        {
            if (LUT[i] == true && i > smallest_prime)
            {
                smallest_prime = i;
            }
            else
            {
                continue;
            }
            break;
        }
        int multiple = RANGE / smallest_prime;
        for (int i = 2; i <= multiple; i++)
        {
            LUT[(i * smallest_prime)] = false;
        }
    }
    return LUT;
}

int main()
{
    bool LUT[RANGE];
    bool *isPrime = generateIsPrime(LUT);
    int n = 0;
    cin >> n;
    int *numbers = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }
    int outcnt = 0;
    for (int j = 0; j < n; j++)
    {
        if (*(isPrime + numbers[j]))
        {
            if (outcnt >= 1)
            {
                cout << ' ';
            }
            cout << numbers[j];
            outcnt++;
        }
    }
    cout << endl;
    delete[] numbers;
    return 0;
}