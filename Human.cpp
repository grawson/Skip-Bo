#include "Human.hpp"
#include <iostream>
#include <climits>

#define TEXT cout << "...That wasn't a number. Try again: ";\
cin.clear();\
cin.ignore(INT_MAX, '\n');\

using std::cout;
using std::cin;
using std::endl;
using std::string;


Human::Human(std::string name, int color) : Player(name,color){
    type = 0;
}

// Show the player's hand
void Human::viewHand() {
    if (!hand.isEmpty()) {
        cout << colorPre(color) << "Your hand: \033[0m\n\t";
        hand.printCards(colorPre(color));
        cout << endl;
    }
}

// Make decisions for player turn
bool Human::takeTurn(Deck& inPlay, Table& buildPiles) {
    drawCards(inPlay, buildPiles.getOutofPlay());
    bool cont = true;
    int choice = -1;
    
    while (cont) {
        SaveGame sg;
        
        cout << colorPre(color) << name << "'s turn!\033[0m" << endl;
        displayMenu();
        viewStockCard();
        viewHand();
        viewDiscardPiles();
        buildPiles.showTable(colorPre(color));
        while(!(cin >> choice)) {
            TEXT
        }
        
        int bp = -1; // build pile index
        int dp = -1; // discard pile index
        int handCard = -1; // number of card in hand
        
        switch (choice) {
            case 1: // play stock card
                cout << colorPre(color) << "Which build pile would you like to play on? (1-4)\033[0m ";
                buildPiles.showTable(colorPre(color));
                while(!(cin >> bp)) {
                    TEXT
                }
                --bp;
                
                try {
                    if(playStock(buildPiles.getPile(bp),
                                 buildPiles.getOutofPlay()) == false) {
                        cout << colorPre(color) << name << " WON THE GAME!\033[0m" << endl;
                        return false;
                    }
                    cout << colorPre(color) << "Successully played stock card!\033[0m" << endl;
                } catch (InputError& e) {
                    std::cerr << e.what() << endl;
                }
                
                break;
            case 2: // play hand card
                cout << colorPre(color)<< "Which card from your hand would you like to play? (1-5)\033[0m ";
                while(!(cin >> handCard)) {
                    TEXT
                }
                --handCard;
                cout << colorPre(color)<< "Which build pile would you like to play on? (1-4)\033[0m " << endl;
                buildPiles.showTable(colorPre(color));
                while(!(cin >> bp)) {
                    TEXT
                }
                --bp;
                
                try  {
                    playHand(inPlay,handCard,buildPiles.getPile(bp),
                             buildPiles.getOutofPlay());
                } catch (std::exception& e) {
                    std::cerr << e.what() << endl;
                }
                
                break;
            case 3: // play card from discard pile
                cout << colorPre(color)<< "Which discard pile would you like to play from? (1-4)\033[0m ";
                while(!(cin >> dp)) {
                    TEXT
                }
                --dp;
                cout << colorPre(color) << "Which build pile would you like to play on? (1-4)\033[0m ";
                buildPiles.showTable(colorPre(color));
                while(!(cin >> bp)) {
                    TEXT
                }
                --bp;
                
                try {
                    playDiscard(dp,buildPiles.getPile(bp),
                                buildPiles.getOutofPlay());
                } catch (std::exception& e) {
                    std::cerr << e.what() << endl;
                }
                break;
            case 4:
                cout << colorPre(color) << "Which card would you like to discard? (1-5)\033[0m " << endl;
                while(!(cin >> handCard)) {
                    TEXT
                }
                --handCard;
                cout << colorPre(color) << "Which discard pile would you like to play on? (1-4)\033[0m " << endl;
                viewDiscardPiles();
                while(!(cin >> dp)) {
                    TEXT
                }
                --dp;
                
                try {
                    discard(handCard,dp,inPlay, buildPiles.getOutofPlay());
                    cont = false;
                } catch (std::exception& e) {
                    std::cerr << e.what() << endl;
                }
                break;
            case 5:	    
                throw sg;
                break;
            default:
                cout << colorPre(color) << "Please make a valid choice (1-5)\033[0m " << endl;
                break;
        }
    }
    return true;
}

void Human::displayMenu() {
    cout << colorPre(color) << "\nPlease choose one of the following options:\033[0m" << endl;
    //cout << "0. See the table " << endl;
    cout << colorPre(color) << "1. Play the top card from your stock pile.\033[0m" << endl;
    cout << colorPre(color) << "2. Play a card from your hand.\033[0m" << endl;
    cout << colorPre(color) << "3. Play a card from your discard pile.\033[0m" << endl;
    cout << colorPre(color) << "4. Discard and end your turn.\033[0m" << endl;
    cout << colorPre(color) << "5. Save and quit this game.\n" << endl;
}

void viewAllPlayers(std::vector<Player*> players) {
    for (auto p : players) {
        cout << p->colorPre(p->getColor()) << "\t" << p->getName() << "'s Visibile Cards\033[0" << endl;
        p->viewStockCard();
        p->viewDiscardPiles();
        cout << "\n\n";
    } 
}
//int main() {

//}
