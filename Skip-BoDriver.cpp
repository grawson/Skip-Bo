#include "Skip-BoDriver.hpp"
#include <cstdlib>
#include <ctime>
#include <climits>

#define TEXT cout << "...That wasn't a number. Do it right this time: ";\
cin.clear();\
cin.ignore(INT_MAX, '\n');\

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;

Game game;

void isNewGame() {
    string NGame;
    bool endloop = false;
    while (!endloop) {
        cout << "Would you like to start a new game? (y/n) ";
        cin >> NGame;
        if (NGame == "y" || NGame == "Y") {
            int startsize;
            cout << "Please enter stockpile size: (1 - 30) ";
            while(!(cin >> startsize)) {
                TEXT
            }
            while(startsize < 1 || startsize > 30) {
                cerr << "Error: Invalid size. Please enter a new size. ";
                while(!(cin >> startsize)) {
                    TEXT
                }
            }
            startMenu(startsize);
            endloop = true;
        }
        else if (NGame == "n" || NGame == "N") {
            if (game.loadGame() == 1) {
                endloop = true;
            }
            else {
                cerr << "Error: File could not be read." << endl;
            }
        }
        else { }
    }
}

void startMenu(int num) {
    int hums; // number of human players
    int coms; // number of AI players
    
    cout << "Welcome to Skip-bo!" << endl;
    cout << "You can play with 2-6 people" << endl;
    cout << "Enter number of human players: ";
    while(!(cin >> hums)){
        TEXT
    }
    
    while (hums < 0) {
        cout << "...Seriously?!?  How many would you reeeaaally want? ";
        while(!(cin >> hums)){
            TEXT
        }
    }
    
    while (hums > 6 ) {
        cout << "That's too many players (6 max). How many would you really want? ";
        while(!(cin >> hums)){
            TEXT
        }
    }
    
    cout << "Enter number of computer players: ";
    while(!(cin >> coms)) {
        TEXT
    }
    
    while (hums + coms > 6) {
        cout << "That's too many players (6 max)! Please enter fewer computer players: ";
        while(!(cin >> coms)){
            TEXT
        }
    }
    
    while (hums + coms < 2) {
        cout << "That's too few players (2 min)! Please enter more computer players: ";
        while(!(cin >> coms)) {
            TEXT
        }
    }
    int i = 0;
    for (; i < hums; ++i) {
        string name;
        
        cout << "Enter the name for human " << i+1 << ": ";
        cin >> name;
        
        game.addHuman(name, i);
    }
    
    for (int j = i; j < coms + i; ++j) {
        string name = "";
        
        cout << "Enter the name for computer " << j-i + 1 << ": ";
        cin >> name;
        
        game.addAI(name, j);
    }
    
    
    game.newGame(num);
    cout << "Cards have been dealt, time to play!" << endl;
    
}

int main() {
    std::srand( unsigned (std::time(0)));
    //std::srand(289);
    isNewGame();
    game.playGame();
    return 0;
}
