#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"
using namespace std;

void game(int bankroll, int hand, string playerType)
{
    //TODO: GAME PROCESS
}

int main(int argc, char *argv[])
{
    int bankroll = atoi(argv[1]);
    int hand = atoi(argv[2]);
    string playerType = string(argv[3]);
    game(bankroll, hand, playerType);
    return 0;
}