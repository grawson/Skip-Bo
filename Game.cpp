//
//  Game.cpp
//

#include "Game.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

Game::Game() { }

void Game::playGame() {
    int i = 0;
    int num = players.size();
    bool over = true;
    
    while (over) {
        try {
            over = players[i % num]->takeTurn(inPlay,table);
            ++i;
        } catch (SaveGame& sg) {
            cout << sg.what() << endl;
            saveGame();
            over = false;
        }
    }
    cout << "ENDED SUCCESSFULLY" << endl;
}

int Game::addHuman(string name, int color) {
    
    //checks that color and name are both unique
    for (auto itr:players) {
        if (itr->getName() == name) {
            cout << "That name already exists, please enter another: ";
            cin >> name;
        }
        if (itr->getColor() == color) {
            cout << "That color already exists, please enter another: ";
            cin >> color;
        }
    }
    Human* newPlyr = new Human(name, color);
    players.push_back(newPlyr);
    return 1;
}

int Game::addAI(string name, int color) {
    
    //checks that color and name are both unique
    for (auto itr:players) {
        if (itr->getName() == name) {
            cout << "That name already exists, please enter another: ";
            cin >> name;
        }
    }
    dumbAI* newPlyr = new dumbAI(name, color);
    players.push_back(newPlyr);
    return 1;
}

int Game::newGame(int num) {
    
    inPlay.initialize(); //add cards to inPlay deck and shuffle
    
    
    // Add cards to the players' stock piles
    for (Player* pls : players) {
        for (int i = 0; i < num; ++i) {
            pls->getStockPile().push(inPlay.draw(table.getOutofPlay()));
        }
    }
    
    //deal cards to each player
    for (auto itr:players) {
        itr->drawCards(inPlay, table.getOutofPlay(), true);
    }
    
    return 1;
}

int Game::saveGame() {
    cout << "Choose file name: ";
    string fname;
    cin >> fname;
    std::ofstream outfile(fname);
    wToFile(outfile);
    return 1;
}

int Game::loadGame() {
    cout << "Choose file name: ";
    string fname;
    cin >> fname;
    std::ifstream infile(fname);
    if (infile.good()) {
        rFromFile(infile);
        return 1;
    }
    else {
        return 0;
    }
}

void Game::wToFile(std::ofstream& outfile) {
    
    //write player vector
    outfile << (int)players.size() << " "; //marks the number of players
    for (int i = 0; i < (int)players.size(); i++) {
        players[i]->wToFile(outfile);
    }
    
    inPlay.wToFile(outfile);
    
    table.wToFile(outfile);
    
}

void Game::rFromFile(std::ifstream& infile) {
    int numPlayers;
    infile >> numPlayers;
    string name, color;
    
    for (int i = 0; i < numPlayers; i++) {
        Human* plyr = new Human("BLANK", -1);  //makes a blank player
        players.push_back(plyr);
        players[i]->rFromFile(infile);
    }
    
    for (Player* p : players) {
        if (p->getType() == 1) {
            p = dynamic_cast<dumbAI*>(p);
        }
    }
    
    inPlay.rFromFile(infile);
    table.rFromFile(infile);
}

bool Game::operator==(const Game& right) {
    
    //if the player vectors arent the same size
    if (players.size() != right.players.size()) {
        return false;
    }
    
    //PLayers are equal
    for (int i = 0; i < (int)players.size(); i++) {
        if (!(*players[i] == *(right.players[i]))) {
            return false;
        }
    }
    
    if (!(inPlay == right.inPlay)) {
        return false;
    }
    
    if (!(table == right.table)) {
        return false;
    }
    
    return true;
}

Game::~Game() {
    for (Player* pl : players) {
        delete  pl;
    }
}

