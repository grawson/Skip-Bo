#ifndef __HUM_
#define __HUM_

#include "Player.hpp"
#include "Table.hpp"
#include <vector>

/** Exception to be called whenever the user chooses to quit and end
 *  the game. Returns control to the catch block within the playGame
 *  method in Game.
 */

class SaveGame: public std::exception {
public:
    virtual const char* what() const throw() // override what() to customize error string
    {  return "Saving game...";  }
};

/** Subclass of player that offers User Interface for a human. It uses
 *  all methods from Player, called whenever the user makes the
 *  appropriate decisions. Contains Input error exception handling
 */

class Human : public Player {
    
public:
    Human(std::string name, int color);
    
    // Show the player's hand
    void viewHand();
    
    // Make decisions for player turn
    bool takeTurn(Deck& inPlay, Table& buildPiles);
    
    // See the menu for the player's options
    void displayMenu();
    
    // See the discard piles and stock cards of all players
    void viewAllPlayers(std::vector<Player*>);
};

#endif
