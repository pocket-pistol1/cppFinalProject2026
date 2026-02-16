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

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <limits>
#include <vector>
#include <map>
#include "baccarat.h"

void genHand();
crd::Card getCrd(crd::Deck& d);
int bt; // 1 = bnk, 0 = ply
crd::Deck d; // deck constructor; header ln: 33.. 39
crd::Hand ply; // players hand
crd::Hand bnk; // bankers hand

namespace scrn {
    // ------- prototypes
    void play();
    void clrScrn();
    void hwto_ply();
    void getWnr(int bt, int phnd, int bhnd);
    // ------ prototypes

    void clrScrn() { // clears the terminal
    #ifdef _WIN32 // if windows
        std::system("cls");
    #else
        std::system("clear"); // if anything else
    #endif
    }

    // displaying the menus
    void men_dsply(std::string in) {
        if(in == "1") {play();}
        else if(in == "2") {hwto_ply();}
        else if(in == "3") {exit(EXIT_SUCCESS);}
    }

    void play() { // the actual game
    scrn::clrScrn();   
    genHand(); // generate hands
    printf("1. Bet on Bankers Hand\n");
    printf("0. Bet on Players Hand\n");
    std::cin >> bt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    ply.calcTot();
    bnk.calcTot();
    int phnd = ply.totalval % 10; // take off first digit
    int bhnd = bnk.totalval % 10;

    printf("Player total: %d\n", phnd); // display hand totals
    printf("Banker total: %d\n", bhnd);
    getWnr(bt, phnd, bhnd); // get the winner

    std::string in; // so we cna play again
    printf("1. Play again\n");
    printf("2. See the rules\n");
    printf("3. Give up\n");
    getline(std::cin, in);
    men_dsply(in);
    }

    void hwto_ply() { // the rules, amazing name; we hate readability
        scrn::clrScrn();
        std::string in;
        printf("Baccarat is a popular, fast-paced casino card game where players bet on which of two hands—the Player or the Banker —will have a total value closest to nine. With very low house edge, it is a game of pure chance involving little to no skill, where face cards and 10s count as zero and Aces as one.\n");
        printf("Objective: Bet on the hand (Player or Banker) with a total closest to 9. Card Values: Aces = 1; 2-9 = Face Value; 10, Jack, Queen, King = 0. Dealing: Two cards are dealt to both the Player and Banker. If the total exceeds 9, the first digit is dropped (e.g., 5 becomes 15).\n"); 
        printf("Third Card Rule: A third card may be dealt based on specific, fixed rules depending on the initial totals. Winning: The hand closest to 9 wins. Winning Banker bets are typically charged a 5%' commission.Outcomes: Player Win, Banker Win, or Tie.\n");
        printf("1. Back\n");
        getline(std::cin, in);
    }

    void getWnr(int bt, int phnd, int bhnd) {
        if(bt == 1 && (phnd > bhnd)) {printf("You lose!\n");} // bet banker and plyr was closer to 9
        if(bt == 1 && (phnd < bhnd)) {printf("You win!\n");} // bet banker and banker was closer to 9
        if(bt == 0 && (phnd < bhnd)) {printf("You win!\n");} // bet player and player was closer to 9
        if(bt == 0 && (phnd > bhnd)) {printf("You lose!\n");} // bet player and banker was closer to 9
    }
} // end of scrn

int main() {
    std::string in; // input
   while(true) { // main menu loop
    scrn::clrScrn();
    printf("Welcome to Baccarat!\n");
    printf("1. Play\n");
    printf("2. How To Play\n");
    printf("3. Give up\n");
    std::getline(std::cin, in);
    scrn::men_dsply(in);
   } 
}

// ---------------- non displayed stuff

void genHand() {
    for(int i=0; i < 2; i++) {
        ply.vc.push_back(getCrd(d));
        bnk.vc.push_back(getCrd(d));
    }// if this doseen't work im going to stomp out my cat
}
// returns random card
crd::Card getCrd(crd::Deck& d) {
    std::random_device rd; // create the rng device
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, d.deck.size()-1); // set the range
    int ind = distrib(gen);
    crd::Card rnd = d.deck[ind]; // return a random card in the deck
    d.deck.erase(d.deck.begin() + ind);
    return rnd;
}
