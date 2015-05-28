#ifndef ___BP_
#define ___BP_

#include <stack>
#include <deque>
#include <iostream>
#include <fstream>

/** Data structure to hold the playable buildpile, with methods to access
 *  the size, play a card (with error checking), and move the whole pile
 *  out of play if it becomes full.
 */

class BuildPile {
    friend class testPlayer;
    friend class TestGame;
    
private:
    // Actual cards. Stack container so that we can only access top card
    std::stack<int> build;
    
public:
    
    // Default constructor
    BuildPile(){};
    
    // Print the size of the pile. Unused, except for testing.
    void printSize() { std::cout << build.size() << std::endl; };
    
    // Returns the size of this pile. Allows public access.
    unsigned int getSize() { return build.size();}
    
    // Attempts to play a card on the stack (first argument). Returns true
    // if successful. If this buildpile is full (has 12 cards), it moves it
    // to the out of play deque (second argument)
    bool playCard(int, std::deque<int>&);
    
    // Writes BuildPile to a file
    void wToFile(std::ofstream& outfile);
    
    // Reads data from file into BuildPile
    void rFromFile(std::ifstream& infile, int buildSize);
    
    // Moves all cards in this stack to the out of play deque.
    void putOutOfPlay(std::deque<int>&);
    
    
    // Checks if two buildpiles are equal.
    bool operator==(const BuildPile& right);
    
    
};

#endif
