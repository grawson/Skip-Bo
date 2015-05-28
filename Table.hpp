#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <cstdio>
#include <cstdbool>
#include <iostream>
#include "BuildPile.hpp"
#include <deque>
#include <string>

/** This class primarily holds the playable buildpiles, and the pile of
 *  cards that have been removed from play, after buildpiles have been
 *  filled. Provides methods to access the top cards of the piles. The top
 *  card on the buildpile is determined by the current size, rather than the
 *  actual card. This eliminates the problem of determining what card lies
 *  below a wild card.
 */

class Table{
    
    friend class TestGame;
    
private:
    
    // Holds the four playable buildpiles in the middle of the table
    BuildPile table[4];
    
    // Holds all the cards that have been removed from play (full Build Piles)
    std::deque<int> outOfPlay;
    
    // Number of wild cards that have been played
    int numWilds;
    
public:
    
    // Constructor
    Table();
    
    // Plays a card on a particular build pile
    // The first parameter specifies the pile to add to, the second, the card to add
    bool playCard(int, int);
    
    // Returns the top card of the specified pile
    int getTopCard(int);
    
    // Access one of the piles in the table
    BuildPile& getPile(int);
    
    // Access the out of play vector
    std::deque<int>& getOutofPlay();
    
    // Display top cards on the build  piles
    void showTable(std::string color);
    
    // Writes Table to a file
    void wToFile(std::ofstream& outfile);
    
    // Reads data from file into Table
    void rFromFile(std::ifstream& infile);
    
    // Tests if two tables are equal to each other (deep)
    bool operator==(const Table& right);
    
};

#endif
