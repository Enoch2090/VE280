/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
#include <ctype.h>
#include <cstring>
using namespace std;

// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[])
{
    bool alphabetic = false;
    bool numerical = false;
    bool non_alphanumeric = false;
    int len = strlen(password);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(password[i]))
        {
            alphabetic = true;
        }
        if (isdigit(password[i]))
        {
            numerical = true;
        }
        if (ispunct(password[i]))
        {
            non_alphanumeric = true;
        }
    }
    bool isValid = alphabetic && numerical && non_alphanumeric;
    return isValid;
}

int main()
{
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
