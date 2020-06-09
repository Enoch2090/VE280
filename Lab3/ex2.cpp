#include <iostream>
#include <limits.h>
#include "ex2.h"

using namespace std;

int fold(int count, int arr[], int (*fn)(int, int), int initial)
{
    if (count > 0)
    {
        int new_arr[count - 1];
        for (unsigned int i = 0; i < count - 1; i++)
        {
            new_arr[i] = arr[i + 1];
        }
        initial = fn(*arr, initial);
        initial = fold(count - 1, new_arr, fn, initial);
    }
    else
    {
        return initial;
    }
    return initial;
}

int fn_add(int a, int b)
{
    return a + b;
}

int fn_count_odd(int a, int n)
{
    return abs(a) % 2 == 1 ? n + 1 : n;
}
