//
//  Game.hpp
//

#ifndef ____Game__
#define ____Game__

#include "Deck.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include "Human.hpp"
#include "dumbAI.hpp"

#include <cstdio>
#include <vector>
#include <string>
#include <fstream>

class Game {
    
    friend class TestGame;
    
private:
    std::vector<Player*> players;   //vector of player pointers
    Deck inPlay;                    //Deck for cards able to be dealt
    Table table;                    //Table object
public:
    
    /* default constructor */
    Game();
    
    /* Runs a whole round of the game. Continues unless a saveGame excpection is thrown */
    void playGame();
    
    /*
     * Adds a human to the vector of players. Parameters specify the name and the color
     * identifying the player. Ensures that the added player's name and color are unique.
     */
    int addHuman(std::string name, int color);
    
    /*
     * Adds an AI to the vector of players. Parameters specify the name and the color
     * identifying the AI. Ensures that the added AI's name and color are unique.
     */
    int addAI(std::string name, int color);
    
    /*
     * Starts a new game. Initializes and shuffles the inplay deck, adds cards to the
     * player's stockpiles, and deals cards to each player. Parameter specifies the number
     * of stockpile cards. Returns 1 if successful.
     */
    int newGame(int num = 30);
    
    /*
     * Saves a game. User specifies the name of the file to save to. returns 1 if successfull
     */
    int saveGame();
    
    /*
     * Loads a game. user specifies the name of the file to load from. Returns 1 if
     * successfull, 0 otherwise.
     */
    int loadGame();
    
    /* Writes contents of a game to a file */
    void wToFile(std::ofstream& outfile); //writes Game to a file
    
    /* Reads a file into the contents of a game */
    void rFromFile(std::ifstream& infile); //reads data from file into Game
    
    /* Override the == operator */
    bool operator==(const Game& right);
    
    /* Destructor deletes each pointer within the player vector */
    ~Game();
};

#endif /* defined(____Game__) */
