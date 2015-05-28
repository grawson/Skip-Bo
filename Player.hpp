//
//  Player.h
//

#ifndef ____Player__
#define ____Player__

#include "Hand.hpp"
#include "BuildPile.hpp"
#include "Deck.hpp"
#include "Table.hpp"
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <exception>

class InputError: public std::exception {
public:
    
    /*
     * Human tries to make an invalid play either because number is out
     * of bounds or number does not fit onto build pile or it is not a number
     */
    virtual const char* what() const throw() // override what() to customize error string
    {  return "Invalid input";  }
};

class Player {
    
    friend class testAIandGameTree;
    friend class testPlayer;
    friend class TestGame;
    friend class TestDumbAI;
    
protected:
    std::string name;              //Name of player
    int color;                     //color of player
    Hand hand;                     //Hand class contains vector of ints
    std::vector<int> discPile[4];  //Stack class contains stack of ints
    std::stack<int> stockPile;     //Stack class contains stack of ints
    int type;                      // 0 for human, 1 for dumbAI
    
public:
    
    /*
     * Constructor takes in parameter for name and color.
     */
    Player(std::string nm, int clr=0);
    
    /*
     * Place the top card of the stockpile onto one of the piles on the
     * table.
     * Parameters: build pile to place the card (passed in from Game).
     * outPlay = the out of play deck
     * Return: false if the game is over. Throws an inout error if attempting to play
     * stockpile onto build pile in wrong order
     */
    bool playStock(BuildPile& build, std::deque<int>& outPlay) throw (InputError);
    
    /*
     * Place a card from the player's hand into a pile onto a build pile.
     * Par: in play deck, hand index to play from, build pile to play on,
     * out of play deck. Throws an input error if hand index is out of bounds or if
     * card from hand to build pile is not in sequential order
     */
    void playHand(Deck& inPlay, int handIndex, BuildPile& build, std::deque<int>& outPlay) throw (InputError);
    
    /*
     * Choose top of specified discard pile to play onto build pile.
     * Par: discIndex = index of discard pile to take card from.
     * BuildIndex of build pile to place card. outOfPlay deck of cards.
     * throws input error if discIndex is invalid if if build card is not sequential
     */
    void playDiscard(int discIndex, BuildPile& build, std::deque<int>& outPlay) throw (InputError);
    
    /*
     * Select card from hand to add to discard pile.
     * Par: card = card from hand to place. discIndex = index of discard pile
     *      to place card
     * throws an input error if discindex or handindex is out of bounds, or if
     * card at handindex is empty
     */
    void discard(int card, int discIndex, Deck& inPlay, std::deque<int>& outPlay) throw (InputError);
    
    /*
     * Draw cards from the center deck until the hand is full (5 cards)
     * performed at the beginning of each turn, or when all cards
     * in the hand are played.
     *
     * bool argument is used to supress output on opening deal
     */
    void drawCards(Deck&, std::deque<int>& outPlay, bool firstTurn = false);
    
    /* writes Player contents to a file */
    void wToFile(std::ofstream& outfile);
    
    /* reads data from file into Player */
    void rFromFile(std::ifstream& infile);
    
    /* Show top card on the stock pile */
    void viewStockCard();
    
    /* Display all discard piles */
    void viewDiscardPiles();
    
    /* overloader == operator */
    bool operator==(const Player& right);
    
    /* assists with outputting text in color */
    std::string colorPre(int);
    
    /* pure virtual function implemented by human and AI */
    virtual bool takeTurn(Deck& inPLay, Table& buildPiles) = 0;
    
    /* default destructor */
    virtual ~Player();
    
    std::stack<int>& getStockPile() { return stockPile; }  //returns reference to stockPile
    std::string getName() { return name; }      //returns the name of the player
    int getColor() { return color; }            //returns the color of the player
    int getType() { return type; }              //returns whether player is human or AI
    Hand& getHand(){ return hand;}              //returns reference to hand
};

#endif /* defined(____Player__) */
