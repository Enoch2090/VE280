#include "deck.h"
#include <iostream>
using namespace std;
Deck::Deck()
{
    this->reset();
}

void Deck::reset()
{
    int CardCounter = 0;
    for (int suit = SPADES; suit <= DIAMONDS; suit++)
    {
        for (int spot = TWO; spot <= ACE; spot++)
        {
            this->deck[CardCounter].suit = Suit(suit);
            this->deck[CardCounter].spot = Spot(spot);
            CardCounter++;
        }
    }
    this->next = 0;
}

void Deck::shuffle(int n)
{
    Card DeckCopy[52];
    int CardCounter = 0;
    int Left = 0;
    int Right = n;
    while ((Left <= n - 1) && (Right <= 51)) // Shuffle the cards
    {
        DeckCopy[CardCounter] = this->deck[Right];
        CardCounter++;
        DeckCopy[CardCounter] = this->deck[Left];
        CardCounter++;
        Left++;
        Right++;
    }
    int Remainder = 0;
    int Max = 0;
    if ((Left < n - 1) || (Right < 51)) // Put the rest cards in order.
    {
        Remainder = (Left < n - 1) ? Left : Right;
        Max = (Left < n - 1) ? (n - 1) : 51;
        while (Remainder <= Max)
        {
            DeckCopy[CardCounter] = this->deck[Remainder];
            CardCounter++;
            Remainder++;
        }
    }
    for (int index = 0; index <= 51; index++)
    {
        this->deck[index] = DeckCopy[index];
    }
    this->next = 0;
}

Card Deck::deal()
{
    this->next++; // Even can't deal, record the next index. Therefore the cardsLeft() method will always be correct.
    if (this->next > 52)
    {
        DeckEmpty ThisDeckEmpty;
        throw ThisDeckEmpty;
    }
    else
    {
        return this->deck[this->next - 1];
    }
}

int Deck::cardsLeft()
{
    return (52 - this->next);
}

void Deck::printDeck()
{
    while (this->cardsLeft() > 0)
    {
        Card newcard = this->deal();
        cout << SuitNames[newcard.suit] << " " << SpotNames[newcard.spot] << endl;
    }
}