#ifndef _DUMBAI_HPP_
#define _DUMBAI_HPP_

#include "Player.hpp"
#include <cstdio>
#include <cstdbool>

/*  Computer player, derived from Player. Makes decisions based on
 *  procedural choices: it tries to play a stock card, then its hand,
 *  then it's discard piles, and finally discards and ends its turn
 *  when it has no more turns.
 *
 *  Known shortcoming: if a match has all computer players, and > 20
 *  stock cards, there is a chance (~30%) that the game will not finish.
 *  This happens because the computers keep making the same decisions,
 *  and the game cannot reach an end because they are unable to play
 *  all of their stock cards.
 */

class dumbAI : public Player{

public:
    dumbAI(std::string, int); //constructor

    // makes a series of moves while it ca
    bool takeTurn(Deck&, Table&);
    
    // Destructor 
    ~dumbAI();
};

#endif
