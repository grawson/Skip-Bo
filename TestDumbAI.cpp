#include "Player.hpp"
#include "dumbAI.hpp"
#include "Human.hpp"
#include <iostream>
#include <deque>
#include <stack>
#include <cassert>

/** This is a fairly short test that implements all of the methods
 *  required to play a single turn. Since there is only one void
 *  method for dumbAI, it does not make sense to add assert statements,
 *  but there are four important outcomes we are looking for:
 *      1) No seg faults
 *      2) Turn begins with player drawing five cards
 *      3) Player plays cards from his hand (if not stock pile)
 *      4) Play ends after there are no more moves
 
 *  By running this test, we can see the output to the console, and
 *  verify that everything is running correctly.
 */

class TestDumbAI {
public:
    
    static void testAITurn() {
        
        Deck inPlay;
        inPlay.initialize();
        Table blds;
        
        dumbAI dum("Patrick", 2);
        for (int i = 0; i < 20; ++i) {
            dum.stockPile.push(inPlay.draw(blds.getOutofPlay()));
        }
        dum.takeTurn(inPlay, blds);
    }
    
    
};

int main() {
    TestDumbAI::testAITurn();
    return 0;
}
