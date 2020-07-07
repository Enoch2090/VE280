#include "hand.h"
Hand::Hand()
{
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::discardAll()
{
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c)
{
    if (c.spot <= 8)
    {
        this->curValue.count += (c.spot + 2);
    }
    else if (c.spot > 8 && c.spot < 12)
    {
        this->curValue.count += (10);
    }
    else if (c.spot == 12)
    {
        if (this->curValue.count > 10)
        {
            this->curValue.count += 1;
        }
        else
        {
            this->curValue.count += 11;
            this->curValue.soft = true;
        }
    }
    if (this->curValue.count > 21 && this->curValue.soft)
    {
        this->curValue.count -= 10; // Change a soft ACE to a hard ACE.
        this->curValue.soft = false;
    }
}

HandValue Hand::handValue() const
{
    return this->curValue;
}