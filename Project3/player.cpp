#include "player.h"
#include <iostream>
class SimplePlayer : public Player
{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // EFFECTS: return the bet of the simple player.
    bool draw(Card dealer, const Hand &player);
    // EFFECTS: return whether to draw.
    void expose(Card c);
    // EFFECTS: no effect, dummy func.
    void shuffled();
    // EFFECTS: no effect, dummy func.
};

class CountPlayer : public SimplePlayer
{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // EFFECTS: return the bet of the counting player.
    void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    void shuffled();
    // EFFECTS: tells the player that the deck has been re-shuffled.

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
    int a = 0;
    a++;
}
void SimplePlayer::shuffled()
{
    int a = 0;
    a++;
}
//----Definition for the Counting Player----

int CountPlayer::bet(unsigned int bankroll, unsigned int minimum)
{
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