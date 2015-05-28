#include "Deck.hpp"
#include "BuildPile.hpp"
#include "Hand.hpp"
#include "Table.hpp"
#include <deque>
#include <cassert>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using std::cout;
using std::endl;

void testBP() {
    BuildPile *bpp = new BuildPile();
    BuildPile& bp = *bpp;
    
    std::deque<int> discards;
    
    for (int i = 0; i < 13; ++i) {
        bp.playCard(i,discards);
    }
    // Filled up this deck, should be gone and empty
    assert(bp.getSize() == 0);
    
    for (int i = 0; i < 7; ++i) {
        bp.playCard(i,discards);
    }
    // Refill a new build pile
    // REMEMBER, 1 cannot be added because a wild card was used
    // so size should only be 6 now
    assert(bp.getSize() == 6);
    
    // Discard pile is full of the first completed build pile
    assert(discards.size() == 12);
    delete bpp;
}


void testHD() {
    Hand * hdp = new Hand();
    Hand& hd = * hdp;
    
    assert(hd.isEmpty());
    assert(hd.add(12));
    assert(hd.add(10));
    assert(hd.add(5));
    assert(hd.add(2));
    assert(hd.remove(2));
    assert(hd.add(5));
    assert(hd.add(5));
    assert(hd.getCardAt(1) == 10);
    assert(hd.hasCard(12) == 0);
    
    assert(hd.isFull());
    assert(hd.remove(3));
    assert(!hd.isFull());
    delete hdp;
}

void testTable(){
    Table * tbp = new Table();
    Table& tb = *tbp;
    
    assert(tb.playCard(0, 1));
    assert(tb.playCard(1, 1));
    assert(tb.playCard(2, 1));
    assert(tb.playCard(3, 1));
    assert(tb.playCard(2, 2));
    assert(tb.playCard(2, 0));
    assert(tb.getTopCard(2) == 3);
    assert(tb.getTopCard(0) == 1);
    assert(tb.getTopCard(1) == 1);
    int x = 0;
    while (x < 4){
        cout << tb.getTopCard(x) << endl;
        ++x;
    }
    delete tbp;
}

class TestDeck {
public:
    void testDeck() {
        Table * tbp = new Table();
        Table& tb = *tbp;
        Deck* dkp = new Deck();
        Deck& dk = *dkp;
        
        std::deque<int>& out = tb.getOutofPlay();
        assert(dk.addCard(3));
        assert(dk.draw(out) == 3);
        std::vector<int> newCards (3, 4);
        assert(dk.addCards(newCards));
        assert(dk.toString() == "4 4 4\n");
        assert(!dk.addCard(13));
        dk.shuffle();
        assert(dk.draw(out) == 4);
        dk.clear();
        dk.initialize();
        assert(dk.getSize() == 162);
        delete dkp;
        delete tbp;
    }
};

int main() {
    std::srand( unsigned (std::time(0)));
    testBP();
    testHD();
    testTable();
    TestDeck test;
    test.testDeck();
    return 0;
}
