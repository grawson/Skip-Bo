#include "AI.hpp"
#include "GameTree.hpp"
#include "Player.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include <cstdio>
#include <cstdbool>
#include <vector>
#include <stack>
#include <deque>
#include <cassert>


class testAIandGameTree{
public:
  static void constructorTest(){
    AI ar = AI("Arun", 5);
	
    Hand h;
    h.add(5);//initializing hardcoded hand
    h.add(4);
    h.add(0);
    h.add(1);
    h.add(7);
    int tab[4];//initializing hardcoded table
    tab[0] = 1;
    tab[1] = 4;
    tab[2] = 6;
    tab[3] = 9;
    std::vector<int> discPile[4];//Initialzing one of the discard piles.
    discPile[0].push_back(4);
    discPile[0].push_back(2);
    discPile[0].push_back(1);
    discPile[0].push_back(7);
    discPile[0].push_back(3);
    GameTree *nw = new GameTree(h, 5, tab, -1, 0, 0, discPile, nullptr, -1, -1);
    assert(nw->thand == h);
    assert(nw->StockPileTop == 5);
    assert(nw->table[0] == tab[0]);
    assert(nw->discPile[0] == discPile[0]);
    assert(nw->parent == nullptr);
  }

  static void turnTest(){
    AI ar = AI("Arun", 5);
    Deck inPlay;
    inPlay.initialize();
    Table blds;

    for (int i = 0; i < 20; ++i) {
      ar.stockPile.push(inPlay.draw(blds.getOutofPlay()));
    }
    ar.takeTurn(inPlay, blds);
    }
};

int main(){
  testAIandGameTree::constructorTest();
  testAIandGameTree::turnTest();
  return 0;
}
