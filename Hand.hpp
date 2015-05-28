#ifndef _HAND_HPP_
#define _HAND_HPP_
#include <cstdio>
#include <cstdbool>
#include <iostream>
#include <fstream>

/** Data structure to hold the cards in a player's hand. Contains
 *  methods to access all the cards, remove and add to the hand,
 *  and check if there are cards in the hand.
 */

class Hand{
    
private:
    int hand[5] = {-1, -1, -1, -1, -1}; // holds the hand
    
public:
    
    // returns card at index position specified in parameter, or -1, if
    // the index is out of bounds.
    int getCardAt(int);
    
    // returns the index of the card specified by the parameter or -1
    // if the card does not exist.
    int hasCard(int);
    
    // returns true if card added to the hand, false if the hand is already full
    bool add(int);
    
    // removes card at position specifed by parameter, returns true if
    // success, false if the card does not exist.
    bool remove(int);
    
    // check is the hand is empty. Returns true or false
    bool isEmpty();
    
    // check if hand is full.
    bool isFull();
    
    // prints all cards to the screen (used exclusively for human players)
    void printCards(std::string color) {
        for (int x = 0; x < 5; ++x) {
            if (hand[x] != -1) {
                std::cout << color << hand[x] << "  \033[0m";
            } else {
                std::cout << color << "#  \033[0m";
            }
        }
        std::cout << std::endl;
    }
    
    // writes Hand to a file
    void wToFile(std::ofstream& outfile);
    
    // reads data from file into Hand
    void rFromFile(std::ifstream& infile);
    
    // tests if two hands are equal to each other
    bool operator==(const Hand& right);
    
};

#endif
