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

int getVldint();
void genHand(gmeste& gs);
void thrdCrdRl(gmeste& gs);

int getVldint() {
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void thrdCrdRl(gmeste& gs) {
    gs.ply.calcTot();
    gs.bnk.calcTot();
    int phnd = gs.ply.totalval % 10;
    int bhnd = gs.bnk.totalval % 10;
    if (phnd >= 8 || bhnd >= 8) return;

    bool playerDrew = false;
    int playerThirdVal = -1;
    if (phnd <= 5) {
        crd::Card c = getCrd(gs.d);
        gs.ply.vc.push_back(c);
        playerThirdVal = c.val;
        playerDrew = true;
    }
    gs.ply.calcTot();
    phnd = gs.ply.totalval % 10;
    gs.bnk.calcTot();
    bhnd = gs.bnk.totalval % 10;
    if (!playerDrew) {
        if (bhnd <= 5) {gs.bnk.vc.push_back(getCrd(gs.d));}
    }
    else {
        if (bhnd <= 2) {
            gs.bnk.vc.push_back(getCrd(gs.d));
        } else if (bhnd == 3 && playerThirdVal != 8) {
            gs.bnk.vc.push_back(getCrd(gs.d));
        } else if (bhnd == 4 && (playerThirdVal >= 2 && playerThirdVal <= 7)) {
            gs.bnk.vc.push_back(getCrd(gs.d));
        } else if (bhnd == 5 && (playerThirdVal >= 4 && playerThirdVal <= 7)) {
            gs.bnk.vc.push_back(getCrd(gs.d));
        } else if (bhnd == 6 && (playerThirdVal == 6 || playerThirdVal == 7)) {
            gs.bnk.vc.push_back(getCrd(gs.d));
        }
    }
}

namespace scrn {
    // ------- prototypes
    void play(gmeste& gs);
    void clrScrn();
    void hwto_ply();
    void getWnr(int bet, int phnd, int bhnd);
    void men_dsply(int in, gmeste& gs);
    // ------ prototypes

    void clrScrn() { // clears the terminal
    #ifdef _WIN32 // if windows
        std::system("cls");
    #else
        std::system("clear"); // if anything else
    #endif
    }

    // displaying the menus
    void men_dsply(int in,gmeste& gs) {
        switch(in) {
            case 1: play(gs); break;
            case 2: hwto_ply(); break;
            case 3: exit(EXIT_SUCCESS);
        }
    }

    void play(gmeste& gs) { // the actual game
    scrn::clrScrn();   
    genHand(gs); // generate hands
    thrdCrdRl(gs);
    printf("1. Bet on Bankers Hand\n");
    printf("0. Bet on Players Hand\n");
    gs.bt = getVldint();
    gs.ply.calcTot();
    gs.bnk.calcTot();
    int phnd = gs.ply.totalval % 10; // take off first digit
    int bhnd = gs.bnk.totalval % 10;

    printf("Player total: %d\n", phnd); // display hand totals
    printf("Banker total: %d\n", bhnd);
    getWnr(gs.bt, phnd, bhnd); // get the winner

    int in; // so we cna play again
    printf("1. Play again\n");
    printf("2. See the rules\n");
    printf("3. Give up\n");
    std::cin >> in;
    men_dsply(in,gs);
    }

    void hwto_ply() { // the rules, amazing name; we hate readability
        scrn::clrScrn();
        int in;
        printf("Baccarat is a popular, fast-paced casino card game where players bet on which of two hands—the Player or the Banker —will have a total value closest to nine. With very low house edge, it is a game of pure chance involving little to no skill, where face cards and 10s count as zero and Aces as one.\n");
        printf("Objective: Bet on the hand (Player or Banker) with a total closest to 9. Card Values: Aces = 1; 2-9 = Face Value; 10, Jack, Queen, King = 0. Dealing: Two cards are dealt to both the Player and Banker. If the total exceeds 9, the first digit is dropped (e.g., 5 becomes 15).\n"); 
        printf("Third Card Rule: A third card may be dealt based on specific, fixed rules depending on the initial totals. Winning: The hand closest to 9 wins. Winning Banker bets are typically charged a 5%' commission.Outcomes: Player Win, Banker Win, or Tie.\n");
        printf("1. Back\n");
        in = getVldint();
    }

    void getWnr(int bt, int phnd, int bhnd) {
        if(bt == 1 && (phnd > bhnd)) {printf("You lose!\n");} // bet banker and plyr was closer to 9
        if(bt == 1 && (phnd < bhnd)) {printf("You win!\n");} // bet banker and banker was closer to 9
        if(bt == 0 && (phnd < bhnd)) {printf("You win!\n");} // bet player and player was closer to 9
        if(bt == 0 && (phnd > bhnd)) {printf("You lose!\n");} // bet player and banker was closer to 9
        if(phnd == bhnd) {printf("You tied, no one wins.\n");} // tie
    }
} // end of scrn

int main() {
    int in; // input
    gmeste gs;
   while(true) { // main menu loop
    scrn::clrScrn();
    printf("Welcome to Baccarat!\n");
    printf("1. Play\n");
    printf("2. How To Play\n");
    printf("3. Give up\n");
    in = getVldint();
    scrn::men_dsply(in,gs);
   } 
}

// ---------------- non displayed stuff

void genHand(gmeste& gs) {
    //clear hands
    gs.ply.vc.clear();
    gs.bnk.vc.clear();
    for(int i=0; i < 2; i++) {
        gs.ply.vc.push_back(crd::getCrd(gs.d));
        gs.bnk.vc.push_back(crd::getCrd(gs.d));
    }// if this doseen't work im going to stomp out my cat
    /* */
}
