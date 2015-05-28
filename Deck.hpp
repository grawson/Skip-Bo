#ifndef _DECK_HPP_
#define _DECK_HPP_

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

/** Data structure to hold the main deck for the game. Contains a
 *  std double-ended queue, as well as methods to add to the deck,
 *  shuffle it, and draw cards. When a random seed is created (in the
 *  driver), the deck is randomly shuffled every time it is created,
 *  resulting in a unique game.
 */

class Deck {
    // Following friend classes only for test cases
    friend class testPlayer;
    friend class TestGame;
    friend class TestDeck;
    
private:
    // Holds 162 cards for dealing to players
    std::deque<int> deck;
    std::string toString();
    
public:
    Deck();
    int getSize();
    
    // Add a new card to this deck
    bool addCard(int card);
    
    // Add all cards in a container class to this deck. Uses a deque
    // or vector in the course of this program.
    template<typename T>
    bool addCards(T cards) {
        deck.insert(deck.begin(), cards.begin(), cards.end());
        return true;
    }
    
    // Randomly arrange all cards in the deck.
    void shuffle();
    
    // Draw the top card. If the deck is empty, it attempts to reshuffle
    // cards from the OutOfPlay deck (discarded build piles), and, failing
    // that, introduces a new deck into play.
    int draw(std::deque<int>& outOfPlay);
    
    // Add 162 cards to the deck and shuffle at start of game
    void initialize();
    
    // Clear all the cards in this deck
    void clear();
    ~Deck();
    
    // Write the number of cards in the deck, as well as each individual
    // card to a text file.
    void wToFile(std::ofstream& outfile);
    
    // Read in all cards from a saved deck file.
    void rFromFile(std::ifstream& infile);
    
    // Tests if two decks are identical to each other. Used when loading
    // files, and primarily in testing read/write methods.
    bool operator==(const Deck& right);
    
};

#endif
