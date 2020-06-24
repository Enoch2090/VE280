#include "player.h"

class SimplePlayer : public Player
{
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

class CountPlayer : public Player
{
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};