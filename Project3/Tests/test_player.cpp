// $ clang++ -Wall -Werror -O2 --std=c++17 -g test_player.cpp ../player.cpp ../card.cpp ../hand.cpp -o player -lm
// $ ./player > myplayer.out
// $ diff player.out myplayer.out
#include <iostream>
#include <vector>
#include "../player.h"
#include "../card.h"
#include "../hand.h"

using namespace std;

int main()
{
    Player *p1 = get_Simple();
    Player *p2 = get_Counting();
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

    // BET TESTS
    cout << "Test 1" << endl;
    cout << p1->bet(10, 5) << endl;
    cout << p2->bet(10, 5) << endl;
    cout << p2->bet(9, 5) << endl;

    cout << "Test 2" << endl;
    p1->expose(deck[0][2]);
    p1->expose(deck[0][3]);
    p2->expose(deck[0][2]);
    p2->expose(deck[0][3]);
    cout << p1->bet(10, 5) << endl;
    cout << p2->bet(10, 5) << endl;
    cout << p2->bet(9, 5) << endl;
    p1->shuffled();
    p2->shuffled();
    cout << p1->bet(10, 5) << endl;
    cout << p2->bet(10, 5) << endl;
    cout << p2->bet(9, 5) << endl;

    // HARD HANDS
    cout << "Test 3" << endl;
    h.addCard(deck[0][12]);
    h.addCard(deck[0][2]);
    h.addCard(deck[0][10]); // Hand sum 15
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    cout << "Test 4" << endl;
    h.addCard(deck[0][12]);
    h.addCard(deck[0][12]); // This is nonsense, you can't f**king have a hard hand sum 11.
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    cout << "Test 5" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][12]); // Hand sum 12
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][2], h) << endl;
    cout << p2->draw(deck[0][2], h) << endl;
    cout << p1->draw(deck[0][5], h) << endl;
    cout << p2->draw(deck[0][5], h) << endl;

    cout << "Test 6" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][12]);
    h.addCard(deck[0][4]); // Hand sum 18
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    // SOFT HANDS
    cout << "Test 7" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][2]); // Hand sum 16
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    cout << "Test 7" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][2]); // Hand sum 16
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    cout << "Test 8" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][5]); // Hand sum 18
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][1], h) << endl;
    cout << p2->draw(deck[0][1], h) << endl;
    cout << p1->draw(deck[0][5], h) << endl;
    cout << p2->draw(deck[0][5], h) << endl;
    cout << p1->draw(deck[0][6], h) << endl;
    cout << p2->draw(deck[0][6], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    cout << "Test 9" << endl;
    h.discardAll();
    h.addCard(deck[0][12]);
    h.addCard(deck[0][6]); // Hand sum 19
    cout << p1->draw(deck[0][0], h) << endl;
    cout << p2->draw(deck[0][0], h) << endl;
    cout << p1->draw(deck[0][1], h) << endl;
    cout << p2->draw(deck[0][1], h) << endl;
    cout << p1->draw(deck[0][5], h) << endl;
    cout << p2->draw(deck[0][5], h) << endl;
    cout << p1->draw(deck[0][6], h) << endl;
    cout << p2->draw(deck[0][6], h) << endl;
    cout << p1->draw(deck[0][8], h) << endl;
    cout << p2->draw(deck[0][8], h) << endl;

    return 0;
}