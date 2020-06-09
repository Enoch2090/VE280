/*
 * Lab4 Ex1, VE280 SU2020 
 * Created by Jinglei Xie
 * Last update: May 23, 2020
 * Please fill in the parts marked with "TODO". DO NOT CHANGE anything else.
 */

#include <iostream>
#include <cstdlib>
using namespace std;

// Classes for exception types. They are just dummy types for you to use when
// handling expections.
class MARKET1_CLOSED
{
};
class MARKET2_CLOSED
{
};

// EFFECTS: Check whether there is enough flour in market1. If not, throw
//          how much flour you still want.
void buy_flour(int num_pies, float flour_remain)
{
    if (flour_remain <= 250 * num_pies)
    {
        throw(250 * num_pies - flour_remain);
    }
}

// EFFECTS: Check whether there are enough eggs in market1. If not, throw
//          how many eggs you still want.
void buy_eggs(int num_pies, int eggs_remain)
{
    if (eggs_remain <= 1 * num_pies)
    {
        throw(1 * num_pies - eggs_remain);
    }
}

// EFFECTS: Check whether there are enough apples in market2. If not, throw
//          how many apples you still want.
void buy_apples(int num_apples, int apples_remain)
{
    if (apples_remain <= 2 * num_apples)
    {
        throw(2 * num_apples - apples_remain);
    }
}

// EFFECTS: Check if market1 is open. If it is open, then go on to buy flour
//          and eggs. If it is closed, throw an exception of "MARKET1_CLOSED"
//          type.
// NOTE:    For consistency, please first call buy_flour and then buy_eggs
//          if market1 is open.
void visit_market1(bool market1_status, int num_pies, float flour_remain, int eggs_remain)
{
    if (!market1_status)
    {
        MARKET1_CLOSED mk1;
        throw mk1;
    }
    else
    {
        try
        {
            buy_flour(num_pies, flour_remain);
        }
        catch (float flour_needed)
        {
            throw flour_needed;
        }
        try
        {
            buy_eggs(num_pies, eggs_remain);
        }
        catch (int eggs_needed)
        {
            throw eggs_needed;
        }
    }
}

// EFFECTS: Check if market2 is open. If it is open, then go on to buy apples.
//          If it is closed, throw an exception of "MARKET2_CLOSED" type.
void visit_market2(bool market2_status, int num_pies, int apples_remain)
{
    if (!market2_status)
    {
        MARKET2_CLOSED mk2;
        throw mk2;
    }
    else
    {
        try
        {
            buy_apples(num_pies, apples_remain);
        }
        catch (int apples_needed)
        {
            throw apples_needed;
        }
    }
}

int main(int argc, char *argv[])
{
    int num_pies;        // number of pies you want to make.
    bool market1_status; // whether market1 is open or closed. 1 for open and 0 for closed.
    bool market2_status; // whether market2 is open or closed. 1 for open and 0 for closed.
    float flour_remain;  // amount of flour remaining in market1 (in grams).
    int eggs_remain;     // number of eggs remaining in market1.
    int apples_remain;   // number of apples remaining in market2.

    // Read all the above parameters from the program arguments
    num_pies = atoi(argv[1]);
    market1_status = (bool)atoi(argv[2]);
    market2_status = (bool)atoi(argv[3]);
    flour_remain = stof(argv[4]);
    eggs_remain = atoi(argv[5]);
    apples_remain = atoi(argv[6]);
    bool flag = 1; // If any expception happens, flag will be changed to 0.

    // You will first visit market1 and then visit market2. If any exception happens,
    // your buying process will end. Pay attention to the type of variable in each "catch()".

    cout << "You visit market1 first..." << endl;
    try
    {
        visit_market1(market1_status, num_pies, flour_remain, eggs_remain);

        cout
            << "You've bought enough flour and eggs. Then you visit market2..." << endl;
        try
        {
            visit_market2(market2_status, num_pies, apples_remain);

            cout
                << "You've also bought enough apples! You can go home and make the pies now!" << endl;
        }
        catch (MARKET2_CLOSED mk2)
        {
            cout << "market2 is closed!" << endl;
            flag = 0;
        }
        catch (int apples_needed)
        {
            cout << "Apples in market2 are not enough. You still need " << apples_needed << " more." << endl;
            flag = 0;
        }
    }
    catch (MARKET1_CLOSED mk1)
    {
        cout << "market1 is closed!" << endl;
        flag = 0;
    }
    catch (float flour_needed)
    {
        cout << "Flour in market1 is not enough. You still need "
             << flour_needed << " grams more." << endl;
        flag = 0;
    }
    catch (int eggs_needed)
    {
        cout << "Eggs in market1 are not enough. You still need "
             << eggs_needed << " more." << endl;
        flag = 0;
    }

    if (!flag)
        cout << "It seems that today is not a good day for making apple pies." << endl;

    return 0;
}
