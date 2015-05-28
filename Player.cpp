//
//  Player.cpp
//

#include "Player.hpp"
#include "BuildPile.hpp"
#include "Hand.hpp"
#include "dumbAI.hpp"

using std::string;
using std::stack;
using std::deque;
using std::cout;
using std::endl;

Player::Player(string nm, int clr) {
    name = nm;
    color = clr;
}

bool Player::playStock(BuildPile& build, deque<int>& outPlay) throw (InputError) {
    
    InputError e;
    
    // if stockPile is empty the game is over
    if (stockPile.empty()) {
        return false;
    }
    
    if (build.playCard(stockPile.top(), outPlay) == false) {
        throw e;
    }
    
    // if stockPile is empty the game is over
    if (stockPile.empty()) {
        return false;
    }
    
    stockPile.pop();    //remove card from stockPile
    return true;
}

void Player::playHand(Deck& inPlay, int handIndex, BuildPile& build, deque<int>& outPlay) throw (InputError) {
    
    InputError e;
    
    //if hand index out of bounds
    if ((handIndex > 4) || (handIndex < 0)) {
        throw e;
    }
    
    if (build.playCard(hand.getCardAt(handIndex), outPlay) == false) {
        throw e;
    }
    
    hand.remove(handIndex);  //remove card from hand
    
    //if hand is empty, draw cards
    if (hand.isEmpty()) {
        drawCards(inPlay, outPlay);
    }
}

void Player::playDiscard(int discIndex, BuildPile& build, deque<int>& outPlay) throw (InputError) {
    
    InputError e;
    
    //if discIndex is invalid
    if ((discIndex < 0) || (discIndex > 3)) {
        throw e;
    }
    
    if (discPile[discIndex].size() == 0) {
        throw e;
    }
    
    int nextCard = discPile[discIndex].back();
    
    if (build.playCard(nextCard, outPlay) == false) {
        throw e;
    }
    
    discPile[discIndex].pop_back();     //remove card from discPile
}

void Player::discard(int handIndex, int discIndex, Deck& inPlay, deque<int>& outPlay) throw (InputError) {
    
    InputError e;
    //if discIndex is invalid
    if ((discIndex < 0) || (discIndex > 3)) {
        throw e;
    }
    
    //if handINdex out of bounds
    if ((handIndex < 0) || (handIndex > 4)) {
        throw e;
    }
    
    //if HandIndex is empty
    if (hand.getCardAt(handIndex) == -1) {
        throw e;
    }
    
    discPile[discIndex].push_back(hand.getCardAt(handIndex));
    hand.remove(handIndex);
    
    //if hand is empty, draw cards
    if (hand.isEmpty()) {
        drawCards(inPlay, outPlay);
    }
}

void Player::drawCards(Deck& theDeck, deque<int>& outPlay, bool firstTurn) {
    while(!hand.isFull()) {
        int newCard = theDeck.draw(outPlay);
        hand.add(newCard);
        
        if (!firstTurn) {
            if(newCard == 0) {
                cout << colorPre(color) << name << " drew a wild card! \033[0m" << endl;
            } else {
                cout << colorPre(color) << name << " drew a " << newCard << ".\033[0m" << endl;
            }
        }
    }
}

void Player::wToFile(std::ofstream& outfile) {
    outfile << name << " ";
    outfile << color << " ";
    outfile << type << " ";
    hand.wToFile(outfile);
    
    //traverse through discPile array
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < (int)discPile[i].size(); j++) {
            outfile << discPile[i].at(j) << " ";
        }
        outfile << -2 << " "; //marks the end of an array index
    }
    
    //flip stockpile stack to print in right order
    int stockSize = (int)stockPile.size();
    stack<int> temp;
    for (int i = 0; i < stockSize; i++) {
        temp.push(stockPile.top());
        stockPile.pop();
    }
    
    //Recreate stockPile from temp and print out temp to file
    stockSize = (int)temp.size();
    outfile << stockSize << " "; //marks the stockPile size for reading
    for (int i = 0; i < stockSize; i++) {
        outfile << temp.top() << " ";
        stockPile.push(temp.top());
        temp.pop();
    }
}

void Player::rFromFile(std::ifstream& infile) {
    infile >> name;
    infile >> color;
    infile >> type;
    hand.rFromFile(infile);
    
    int temp  = 0;
    int discIndex = 0;
    while (discIndex != 4) {
        infile >> temp;
        if (temp == -2) { //-2 separates the indices
            discIndex++;
        } else {
            discPile[discIndex].push_back(temp);
        }
    }
    
    int stockSize;
    infile >> stockSize;
    for (int i = 0; i < stockSize; i++) {
        infile >> temp;
        stockPile.push(temp);
    }
}

// Show all of the discard piles
void Player::viewDiscardPiles() {
    if (discPile) {
        for (int i = 0; i < 4; ++i) {
            if (discPile[i].size() > 0) {
                cout << colorPre(color) << "Cards in discard pile " <<
                i + 1 << " (only right card playable): \033[0m";
                for (int card : discPile[i]) {
                    cout << colorPre(color) << card << " \033[0m";
                }
                cout << endl;
            }
        }
    }
}

// Show top card on the discard pile
void Player::viewStockCard() {
    if (stockPile.size() > 0) {
        cout << colorPre(color) << "Current stock card: " << stockPile.top() << "\033[0m" << endl;
    }
}

bool Player::operator==(const Player& right) {
    if (name != right.name) {
        return false;
    }
    
    if (color != right.color) {
        return false;
    }
    
    if (!(hand == right.hand)) {
        return false;
    }
    
    for (int i = 0; i < 4; i++) {
        if (discPile[i] != right.discPile[i]) {
            return false;
        }
    }
    
    if (stockPile != right.stockPile) {
        return false;
    }
    return true;
}

string Player::colorPre(int color) {
    string colors[6] = {"\033[1;31m","\033[1;32m","\033[1;33m",
        "\033[1;34m","\033[1;35m","\033[1;36m"};
    return colors[color];
}

Player::~Player() {}



