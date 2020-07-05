// Add the following to you deck.h:
// void printDeck();
// Run with:
// $ clang++ -Wall -Werror -O2 --std=c++17 -g test_deck.cpp ../deck.cpp ../card.cpp -o deck -lm
// $ ./deck > mydeck.out
// $ diff deck.out mydeck.out

#include <iostream>
#include "../deck.h"
using namespace std;

void Deck::printDeck() // CONSOLE
{
    for (int print_counter = this->next; print_counter < 52; print_counter++)
    {
        cout << SpotNames[this->deck[print_counter].spot] << " of " << SuitNames[this->deck[print_counter].suit] << endl;
    }
}
int main()
{
    Deck d;
    cout << "Test 1" << endl;
    d.printDeck();
    cout << "Test 2" << endl;
    d.shuffle(21);
    d.printDeck();
    cout << "Test 3" << endl;
    d.deal();
    d.deal();
    d.printDeck();
    cout << "Test 4" << endl;
    d.shuffle(15);
    d.printDeck();
    cout << "Test 5" << endl;
    for (int i = 0; i < 10; i++)
    {
        d.deal();
    }
    d.printDeck();
    cout << "Test 6" << endl;
    d.reset();
    d.shuffle(48);
    d.printDeck();
    cout << "Test 7" << endl;
    d.reset();
    d.shuffle(0);
    d.printDeck();
    cout << "Test 8" << endl;
    d.shuffle(52);
    d.printDeck();
    return 0;
}