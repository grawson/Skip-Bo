#include "Hand.hpp"
#include <cstdio>
#include <cstdbool>
#include <iostream>
#include <fstream>

int Hand::getCardAt(int index){
    if (index < 5 && index >= 0) {
        return this->hand[index];
    } else {
        return -1;
    }
}

int Hand::hasCard(int card){
    int x = -1;
    for (int y = 0; y < 5; ++y) {
        if (card == this->hand[y]) {
            x = y;
        }
    }
    return x;
}

bool Hand::add(int card){
    int y = 0;
    for (int x = 0; x < 5; ++x){
        if (this->hand[x] == -1 && y == 0){
            this->hand[x] = card;
            ++y;
        }
    }
    if (y == 0){
        return false;
    }
    else {
        return true;
    }
}

bool Hand::remove(int index){
    if (index >= 5 || index < 0){
        return false;
    }
    else{
        this->hand[index] = -1;
        return true;
    }
}

bool Hand::isEmpty() {
    
    int numEmpty = 0;
    for (int i = 0; i < 5; i++) {
        if (hand[i] == -1) {
            numEmpty++;
        }
    }
    
    if (numEmpty == 5) {
        return true;
    }
    return false;
}

bool Hand::isFull() {
    for (int i = 0; i < 5; ++i) {
        if (hand[i] == -1)return false;
    }
    return true;
}

void Hand::wToFile(std::ofstream& outfile) {
    for (int i = 0; i < 5; i++) {
        outfile << hand[i] << " ";
    }
}

void Hand::rFromFile(std::ifstream& infile) {
    for (int i = 0; i < 5; i++) {
        infile >> hand[i];
    }
}

bool Hand::operator==(const Hand& right) {
    for (int i = 0; i < 5; i++) {
        if (hand[i] != right.hand[i]) {
            return false;
        }
    }
    return true;
}



