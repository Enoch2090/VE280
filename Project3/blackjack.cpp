#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"
#include "rand.h"
using namespace std;
void deal_toplayer(Player *player, Hand &player_h, Deck &deck)
{
    Card dealt_card = deck.deal();
    player_h.addCard(dealt_card);
    cout << "Player dealt " << SpotNames[dealt_card.spot] << " of " << SuitNames[dealt_card.suit] << endl;
    player->expose(dealt_card);
}
void shuffle_deck(Deck &deck, bool reset)
{
    if (reset)
    {
        deck.reset();
    }
    cout << "Shuffling the deck\n";
    for (int shuffle_i = 0; shuffle_i < 7; shuffle_i++) // Shuffle the deck
    {
        int cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
}

void game(int bankroll, int hand, string playerType)
{
    int MINIMUM = 5;
    int player_bankroll = bankroll;
    Player *player;
    Deck deck;
    Hand player_h;
    Hand dealer_h;
    Card dealt_card;
    Card dealer_up;
    Card dealer_down;
    if (playerType == "simple")
    {
        player = get_Simple();
    }
    else if (playerType == "counting")
    {
        player = get_Counting();
    }
    else
    {
        return;
    }

    shuffle_deck(deck, true);
    player->shuffled();
    for (int hand_i = 0; hand_i < hand; hand_i++) // Each loop is a hand to play
    {
        bool player_busted = false;
        bool dealer_busted = false;
        if (player_bankroll < MINIMUM)
        {
            cout << "Player has " << player_bankroll
                 << " after " << hand_i << " hands\n";
            break;
        }
        cout << "Hand " << hand_i + 1 << " bankroll " << player_bankroll << endl;
        if (deck.cardsLeft() < 20)
        {
            shuffle_deck(deck, false);
            player->shuffled();
        }
        int wager = player->bet(player_bankroll, MINIMUM);
        cout << "Player bets " << wager << endl;

        deal_toplayer(player, player_h, deck);

        dealt_card = deck.deal();
        dealer_h.addCard(dealt_card);
        dealer_up = dealt_card;
        cout << "Dealer dealt " << SpotNames[dealt_card.spot] << " of " << SuitNames[dealt_card.suit] << endl;
        player->expose(dealt_card);

        deal_toplayer(player, player_h, deck);

        dealt_card = deck.deal();
        dealer_h.addCard(dealt_card);
        dealer_down = dealt_card;

        if (player_h.handValue().count == 21)
        {
            player_bankroll += 3 * wager / 2;
            cout << "Player dealt natural 21\n";
        }
        else
        {
            while (player->draw(dealer_up, player_h) == true)
            {
                deal_toplayer(player, player_h, deck);
                if (player_h.handValue().count > 21)
                {
                    cout << "Player's total is " << player_h.handValue().count << endl;
                    cout << "Player busts\n";
                    player_busted = true;
                    player_bankroll -= wager;
                    break;
                }
            }
            if (!player_busted)
            {
                cout << "Player's total is " << player_h.handValue().count << endl;
                cout << "Dealer's hole card is " << SpotNames[dealt_card.spot] << " of " << SuitNames[dealt_card.suit] << endl;
                player->expose(dealer_down);
                // Dealer starts to hit
                while (dealer_h.handValue().count < 17)
                {
                    dealt_card = deck.deal();
                    dealer_h.addCard(dealt_card);
                    cout << "Dealer dealt " << SpotNames[dealt_card.spot] << " of " << SuitNames[dealt_card.suit] << endl;
                    player->expose(dealt_card);
                    if (dealer_h.handValue().count > 21)
                    {
                        cout << "Dealer's total is " << dealer_h.handValue().count << endl;
                        cout << "Dealer busts\n";
                        dealer_busted = true;
                        player_bankroll += wager;
                        break;
                    }
                }
                if (!dealer_busted)
                {
                    cout << "Dealer's total is " << dealer_h.handValue().count << endl;
                    if (player_h.handValue().count > dealer_h.handValue().count)
                    {
                        cout << "Player wins\n";
                        player_bankroll += wager;
                    }
                    else if (player_h.handValue().count < dealer_h.handValue().count)
                    {
                        cout << "Dealer wins\n";
                        player_bankroll -= wager;
                    }
                    else
                    {
                        cout << "Push\n";
                    }
                }
            }
        }
        player_h.discardAll();
        dealer_h.discardAll();
        if (hand_i == hand - 1)
        {
            cout << "Player has " << player_bankroll
                 << " after " << hand << " hands\n";
        }
    }
}

int main(int argc, char *argv[])
{
    int bankroll = atoi(argv[1]);
    int hand = atoi(argv[2]);
    string playerType = string(argv[3]);
    //cout << bankroll << " " << hand << " " << playerType << endl;
    game(bankroll, hand, playerType);
    return 0;
}