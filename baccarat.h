// @pocket-pistol1
// 16/2/2026

/*
Baccarat is a popular, fast-paced casino card game where players bet on which of two hands—the "Player" or the "Banker"—will have a total value closest to nine. With very low house edge, it is a game of pure chance involving little to no skill, where face cards and 10s count as zero and Aces as one. 
Key Rules and Gameplay
Objective: Bet on the hand (Player or Banker) with a total closest to 9.
Card Values: Aces = 1; 2-9 = Face Value; 10, Jack, Queen, King = 0.
Dealing: Two cards are dealt to both the Player and Banker. If the total exceeds 9, the first digit is dropped (e.g., 
 becomes 
).
Third Card Rule: A third card may be dealt based on specific, fixed rules depending on the initial totals.
Winning: The hand closest to 9 wins. Winning Banker bets are typically charged a 5% commission.
Outcomes: Player Win, Banker Win, or Tie. 
*/
// todo: find a new major
#ifndef BACCARAT_H
#define BACCARAT_H

#include <iostream>
#include <string>
#include <chrono>
#include <limits>
#include <random>
#include <vector>
#include <map>

// ------------------------------
// start of crd
// ------------------------------
namespace crd {
    // each card
    struct Card {
        int val; // Aces = 1; 2-9 = Face Value; 10, Jack, Queen, King = 0
    }; //end of card

    // the whole deck of cards
    struct Deck {
    std::vector<Card> deck; 
    // creates the deck
        Deck() {
            for (int suit = 0; suit < 4; suit++) { deck.push_back({1}); // the ace
                for (int v = 2; v <= 9; v++) {deck.push_back({v});} // 2.. 9
                for (int i = 0; i < 4; i++) {
                    if(i > 1) deck.push_back({0});
                    deck.push_back({10});
                } // faces
            }
        }
    }; // end of deck

    // individual hands
    struct Hand {
        std::vector<Card> vc;
        int totalval; // total value of hand
        void calcTot() {
            for(Card c : vc) {totalval += c.val;}
        }
    }; // end of hand

}
// ------------------------------
// end of crd
// ------------------------------


#endif
