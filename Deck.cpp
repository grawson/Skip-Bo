#include "Deck.hpp"
#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <sstream>

using std::deque;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

Deck::Deck() { }

string Deck::toString() {
    ostringstream oss;
    int i = 1;
    for (; (unsigned) i < deck.size(); ++i) {
        oss << deck[i-1] << " ";
    }
    oss << deck[i-1] << endl;
    return oss.str();
}

int Deck::getSize() {
    int size = deck.size();
    return size;
}

bool Deck::addCard(int card) {
    if (card < 0 || card > 12) {
        cerr << "Error: Card must be between 0 and 12." << endl;
        return false;
    }
    else {
        deck.push_front(card);
        return true;
    }
}

void Deck::shuffle() {
    
    std::random_shuffle(deck.begin(), deck.end());
}

int Deck::draw(std::deque<int>& outOfPlay) {
    if (!deck.empty()) {
        int card = deck.front();
        deck.pop_front();
        return card;
    }
    else if (!outOfPlay.empty()) {
        addCards(outOfPlay);
        int card = deck.front();
        deck.pop_front();
        return card;
    }
    else {
        initialize();
        int card = deck.front();
        deck.pop_front();
        std::cout << "ADDED A NEW DECK" << std::endl;
        return card; 
    }
}

void Deck::initialize() {
    int num = 0;
    for (int i = 0; i < 18; ++i) {
        addCard(num);
    }
    while (num < 12) {
        ++num;
        for (int i = 0; i < 12; ++i) {
            addCard(num);
        }
    }
    shuffle();
}

void Deck::clear() {
    while (!deck.empty()) deck.pop_front();
}

Deck::~Deck() { }

void Deck::wToFile(std::ofstream& outfile) {
    
    outfile << (int)deck.size() << " "; //marks the size of the deck for reading
    
    for (int i = 0; i < (int)deck.size(); i++) {
        outfile << deck[i] << " ";
    }
}

void Deck::rFromFile(std::ifstream& infile) {
    int deckSize = 0;
    infile >> deckSize; //read the deck size
    
    int temp;
    for (int i = 0; i < deckSize; i++) {
        infile >> temp;
        deck.push_back(temp);
    }
}

bool Deck::operator==(const Deck& right) {
    if (deck != right.deck) {
        return false;
    }
    return true;
}


