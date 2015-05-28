#include "dumbAI.hpp"
#include <cstdio>
#include <cstdbool>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

dumbAI::dumbAI(string name, int color) : Player (name, color){
    type = 1;
}

bool dumbAI::takeTurn(Deck &inPlay, Table &buildPiles) {
    
    bool madePlay = true;
    int plays;
    drawCards(inPlay, buildPiles.getOutofPlay());
    
    while (madePlay) {
        plays = 0;
        int x = 0;
        // Try and play stock card
        for (int bp = 0; bp < 4; ++bp) {
            try {
                if (playStock(buildPiles.getPile(bp),
                              buildPiles.getOutofPlay()) == false) {
                    cout << colorPre(color).substr(0, colorPre(color).length() - 1) <<
                    "53m" << getName() << " WON THE GAME!\033[0m\a" << endl;
                    return false;
                }
                else {
                    cout << colorPre(color) << getName() <<
                    " played a stock card\033[0m" << endl;
                }
                
                ++plays;
            }
            catch (InputError& e) {
            }
        }
        
        // Try and play hand card
        for (int bp = 0; bp < 4; ++bp) {
            for (int hp = 0; (hp < 5 && x == 0); ++hp) {
                try {
                    playHand(inPlay, hp, buildPiles.getPile(bp),
                             buildPiles.getOutofPlay());
                    cout << colorPre(color) << getName() <<
                    " played a hand card\033[0m" << endl;
                    ++plays;
                    ++x;
                }
                catch (std::exception& e) {
                }
            }
        }
        
        // Try and play discard pile
        // Note: dumb AI only discards on one pile
        // this will be more advanced later
        for (int bp = 0; bp < 4; ++bp) {
            try {
                playDiscard(0, buildPiles.getPile(bp),
                            buildPiles.getOutofPlay());
                cout << colorPre(color) << getName() <<
                " played from discard pile\033[0m" << endl;
                ++plays;
            }
            catch (std::exception& e) {
            }
        }
        
        // Just discard the first card in his hand...
        // This guy is really dumb for now...
        if (plays == 0) {
            try {
                discard(0, 0, inPlay, buildPiles.getOutofPlay());
                cout << colorPre(color) << getName()
                << " discarded a card\033[0m" << endl;
            }
            catch (std::exception& e) {
            }
            madePlay = false;
            
        }
    }
    cout << colorPre(color) << getName() << " finished his turn...\033[0m" << endl;
    return true;
}

dumbAI::~dumbAI() { }
