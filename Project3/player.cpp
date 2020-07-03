#include "player.h"
#include <iostream>
class SimplePlayer : public Player
{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

class CountPlayer : public SimplePlayer
{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    void expose(Card c);
    void shuffled();

private:
    int count;
};

//----Definition for the Simple Player----
int SimplePlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}

bool SimplePlayer::draw(Card dealer, const Hand &player)
{
    bool hit = false;
    if (!player.handValue().soft) // hard count
    {
        if (player.handValue().count <= 11)
        {
            hit = true;
        }
        else if (player.handValue().count == 12)
        {
            if (dealer.spot >= 2 && dealer.spot <= 4) // 4, 5, 6
            {
                hit = false;
            }
            else
            {
                hit = true;
            }
        }
        else if ((player.handValue().count >= 13) && (player.handValue().count <= 16))
        {
            if (dealer.spot >= 0 && dealer.spot <= 4) // 2, 3, 4, 5, 6
            {
                hit = false;
            }
            else
            {
                hit = true;
            }
        }
        else
        {
            hit = false;
        }
    }
    else // soft count
    {
        if (player.handValue().count <= 17)
        {
            hit = true;
        }
        else if (player.handValue().count == 18)
        {
            if (dealer.spot == 0 || dealer.spot == 5 || dealer.spot == 6)
            {
                hit = false;
            }
            else
            {
                hit = true;
            }
        }
        else if (player.handValue().count >= 19)
        {
            hit = false;
        }
    }
    return hit;
}

void SimplePlayer::expose(Card c)
{
    // YAY
}
void SimplePlayer::shuffled()
{
    // YAYAY
}
//----Definition for the Counting Player----

int CountPlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    //std::cout << this->count;
    if (this->count >= 2)
    {
        return ((bankroll >= minimum * 2) ? (minimum * 2) : minimum);
    }
    else
    {
        return minimum;
    }
}

void CountPlayer::shuffled()
{
    this->count = 0;
}

void CountPlayer::expose(Card c)
{
    if (c.spot >= 8 && c.spot <= 12) // 10 ~ ACE
    {
        this->count--;
    }
    else if (c.spot >= 0 && c.spot <= 4) // 2 ~ 6
    {
        this->count++;
    }
}

//----Define the players for external use----
static SimplePlayer SPlayer;
static CountPlayer CPlayer;

Player *get_Simple()
{
    return &SPlayer;
}

Player *get_Counting()
{
    return &CPlayer;
}