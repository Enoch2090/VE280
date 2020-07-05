// $ clang++ -Wall -Werror -O2 --std=c++17 -g test_hand.cpp ../card.cpp ../hand.cpp -o hand -lm
// $ ./hand > myhand.out
// $ diff hand.out myhand.out
#include <iostream>
#include <vector>
#include "../card.h"
#include "../hand.h"

using namespace std;

void printHand(const Hand &h)
{
    HandValue cv = h.handValue();
    cout << cv.count << " " << cv.soft << endl;
}

int main()
{
    Hand h;
    vector<vector<Card>> deck(4, vector<Card>(13));
    for (int suit = SPADES; suit <= DIAMONDS; suit++)
    {
        for (int spot = TWO; spot <= ACE; spot++)
        {
            deck[suit][spot].suit = Suit(suit);
            deck[suit][spot].spot = Spot(spot);
        }
    }

    // Begin Test
    cout << "Test 1" << endl;
    h.addCard(deck[3][3]);
    h.addCard(deck[0][12]);
    printHand(h);

    cout << "Test 2" << endl;
    h.discardAll();
    printHand(h);

    cout << "Test 3" << endl;
    h.addCard(deck[0][12]);
    h.addCard(deck[1][12]);
    printHand(h);

    cout << "Test 4" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][2]);
    h.addCard(deck[0][12]);
    printHand(h);

    cout << "Test 5" << endl;
    h.discardAll();
    h.addCard(deck[0][0]);
    h.addCard(deck[1][0]);
    h.addCard(deck[2][0]);
    h.addCard(deck[1][5]);
    h.addCard(deck[0][12]);
    printHand(h);

    cout << "Test 6" << endl;
    h.discardAll();
    for (int i = 0; i < 100; i++)
    {
        h.addCard(deck[0][12]);
    }
    printHand(h);

    cout << "Test 7" << endl;
    h.discardAll();
    h.addCard(deck[3][8]);
    h.addCard(deck[3][12]);
    printHand(h);

    cout << "Test 7" << endl;
    h.discardAll();
    h.addCard(deck[3][8]);
    h.addCard(deck[3][8]);
    h.addCard(deck[3][12]);
    printHand(h);

    return 0;
}