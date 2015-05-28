//
//  testPlayer.cpp
//

#include "Player.hpp"
#include "BuildPile.hpp"
#include "Table.hpp"
#include "Deck.hpp"
#include "Human.hpp"
#include <cstdio>
#include <deque>
#include <stack>
#include <cassert>

using std::vector;
using std::stack;
using std::deque;
using std::cout;
using std::endl;

class testPlayer {
public:
    
    static void testPlayStock() {
        
        Player* plyrPtr = new Human("Gavi", 2);
        delete plyrPtr;
        
        Deck out;
        deque<int> outPlay = out.deck;
        BuildPile bld;
        
        Human plyr1("GAVI", 3);
        assert(plyr1.playStock(bld, outPlay) == 0);  //empty stockPile
        
        
        plyr1.stockPile.push(4); //add card to stock
        plyr1.stockPile.push(3); //add card to stock
        plyr1.stockPile.push(0); //add card to stock
        plyr1.stockPile.push(2); //add card to stock
        plyr1.stockPile.push(1); //add card to stock
        plyr1.stockPile.push(1); //add card to stock
        plyr1.viewStockCard();
        assert(plyr1.playStock(bld, outPlay) == 1); //add stock 2 to buildpile
        assert(bld.build.top() == 1); //check card was added to buildPile
        assert(plyr1.stockPile.top() == 1); //check card removed from stockpile
        
        try {
            assert(plyr1.playStock(bld, outPlay) == 0); //can't place 1 on 1
        }
        catch (InputError& e) { }
        plyr1.stockPile.pop();
        
        assert(plyr1.playStock(bld, outPlay) == 1); //add stock 2 to buildpile
        assert(bld.build.top() == 2); //check card was added to buildPile
        assert(plyr1.stockPile.top() == 0); //check card removed from stockpile
        
        assert(plyr1.playStock(bld, outPlay) == 1); //add stock 0 to buildpile
        assert(bld.build.top() == 0); //check card was added to buildPile
        assert(plyr1.stockPile.top() == 3); //check card removed from stockpile
        
        try {
            assert(plyr1.playStock(bld, outPlay) == 0); //can't place 3 on 0 (used as 3)
        }
        catch (InputError& e) { }
        plyr1.stockPile.pop();
        
        assert(plyr1.playStock(bld, outPlay) == 1); //add stock 4 to buildpile
        assert(bld.build.top() == 4); //check card was added to buildPile
        
        //*******TEST PLAYER HAS WON HERE********
    }
    
    static void testPlayHand() {
        
        Deck out;
        deque<int> outPlay = out.deck;
        Deck inPlay;
        inPlay.deck.push_front(1);
        inPlay.deck.push_front(1);
        inPlay.deck.push_front(0);
        inPlay.deck.push_front(2);
        inPlay.deck.push_front(1);
        BuildPile bld;
        Human plyr1("Gavi", 3);
        
        // Altered structure; if passes without try block, success!
        // If expected exception caught in try/catch block, success!
        
        plyr1.hand.add(1);
        plyr1.playHand(inPlay, 0, bld, outPlay); //add 1 to build
        bld.build.top(); //top of build is 1
        plyr1.hand.isFull(); //Make sure hand is refilled
        //plyr1.takeTurn(inPlay); // make sure no seg fault
        try {
            plyr1.playHand(inPlay, 0, bld, outPlay); //cant play 1 on 1
        }
        catch (InputError& e) { }
        plyr1.playHand(inPlay, 1, bld, outPlay); //play 2 on buildpile
        assert(plyr1.hand.getCardAt(1) == -1); //card was removed from hand
        try {
            plyr1.playHand(inPlay, 7, bld, outPlay); //index out of bounds
        }
        catch (InputError& e) { }
    }
    
    static void testPlayDiscard() {
        Player* plyr1 = new Human("Gavi", 3);
        BuildPile bld;
        Deck out;
        deque<int> outPlay = out.deck;
        
        plyr1->discPile[0].push_back(1);
        plyr1->discPile[1].push_back(1);
        plyr1->discPile[1].push_back(0);
        
        try {
            plyr1->playDiscard(5, bld, outPlay); //index out of bounds
        }
        catch (InputError& e) { }
        plyr1->playDiscard(0, bld, outPlay); //add 1 to buildpile
        assert(bld.build.top() == 1); //top card is 1
        assert(plyr1->discPile[0].back() != 1); //card was removed from discardPile
        
        plyr1->playDiscard(1, bld, outPlay); //add 0 to buildpile
        assert(bld.build.top() == 0); //top card is 0
        assert(plyr1->discPile[1].back() == 1); //card was removed from discardPile
        
        try {
            plyr1->playDiscard(1, bld, outPlay); //Cant add 1 on 2
        }
        catch (InputError& e) { }
        delete plyr1;
    }
    
    static void testDiscard() {
        Table testPiles;
        deque<int>& outPlay = testPiles.getOutofPlay();
        Deck inPlay;
        inPlay.deck.push_front(1);
        inPlay.deck.push_front(2);
        inPlay.deck.push_front(0);
        inPlay.deck.push_front(4);
        inPlay.deck.push_front(5);
        Human plyr1("Gavi", 3);
        plyr1.viewHand(); // empty hand, shouldn't print anything
        plyr1.drawCards(inPlay, outPlay); //fills hand
        plyr1.viewHand(); // should print full hand
        plyr1.viewDiscardPiles(); // empty discard piles
        try {
            plyr1.discard(5, 1, inPlay, outPlay); //index out of bounds
        }
        catch (InputError& e) { }
        try {
            plyr1.discard(1, 5, inPlay, outPlay); //index out of bounds
        }
        catch (InputError& e) { }
        
        plyr1.discard(0, 0, inPlay, outPlay); //add 5 to discPile 1
        assert(plyr1.discPile[0].back() == 5); //top of DicPile 1 is 5
        
        plyr1.discard(1, 1, inPlay, outPlay); //add 4 to discPile 2
        assert(plyr1.discPile[1].back() == 4); //top of DicPile 2 is 4
        plyr1.viewHand(); // Hand missing 5 and 4
        plyr1.discard(2, 0, inPlay, outPlay); //add 3 to discPile 1
        assert(plyr1.discPile[0].back() == 0); //top of DicPile 1 is 3
        
        plyr1.discard(3, 0, inPlay, outPlay); //add 2 to discPile 1
        assert(plyr1.discPile[0].back() == 2); //top of DicPile 1 is 2
        
        try {
            plyr1.discard(0, 0, inPlay, outPlay); //handIdex is empty
        }
        catch (InputError& e) { }
        plyr1.viewDiscardPiles(); // Showing cards in 1st and 2nd piles
    }
    
    static void testDrawCards() {
        Table test;
        Deck inPlay;
        inPlay.deck.push_front(1);
        inPlay.deck.push_front(2);
        inPlay.deck.push_front(0);
        inPlay.deck.push_front(4);
        inPlay.deck.push_front(5);
        Human plyr1("Gavi", 3);
        
        plyr1.drawCards(inPlay, test.getOutofPlay());
        
        assert(plyr1.hand.getCardAt(0) == 5);
        assert(plyr1.hand.getCardAt(1) == 4);
        assert(plyr1.hand.getCardAt(2) == 0);
        assert(plyr1.hand.getCardAt(3) == 2);
        assert(plyr1.hand.getCardAt(4) == 1);
        plyr1.hand.remove(4);
        assert(plyr1.hand.getCardAt(4) == -1); //card slot is empty
    }
};

int main() {
    cout << endl << "Testing playStock..." << endl;
    testPlayer::testPlayStock();
    cout << "playStock tests passed." << endl << endl;;
    
    cout << "Testing playHand..." << endl;
    testPlayer::testPlayHand();
    cout << "playHand tests passed." << endl;
    
    cout << "Testing playDiscard..." << endl;
    testPlayer::testPlayDiscard();
    cout << "playDiscard tests passed." << endl;
    
    cout << "Testing discard..." << endl;
    testPlayer::testDiscard();
    cout << "discard tests passed." << endl;
    
    cout << "Testing drawCards..." << endl;
    testPlayer::testDrawCards();
    cout << "drawCards tests passed." << endl;
    
    cout << "All tests passed." << endl << endl;
    
    return 0;
}
