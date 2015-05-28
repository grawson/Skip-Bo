#include <cstdio>
#include <cstdbool>
#include <iostream>
#include <string>
#include "Table.hpp"
#include "BuildPile.hpp"
#include <vector>

using std::string;

Table::Table() {
    numWilds = 0;
}


bool Table::playCard(int pile, int card){
    bool ret = this->table[pile].playCard(card, this->outOfPlay);
    if (card == 0){
        ++numWilds;
    }
    return ret;
}//KEEP THIS - USED BY THE COMPUTER/AI CLASS

int Table::getTopCard(int pile){
    unsigned int x = this->table[pile].getSize();
    return (int) x;
}

BuildPile& Table::getPile(int pileNum) {
    return table[pileNum];
}

std::deque<int>& Table::getOutofPlay() {
    return outOfPlay;
}

void Table::showTable(string color) {
    std::cout << color << "Top cards on build piles: \033[0m";
    for (int i = 0; i < 4; ++i) {
        std::cout << color << table[i].getSize() << " \033[0m";
    }
    std::cout << std::endl;
}

void Table::wToFile(std::ofstream& outfile) {
    for (int i = 0; i < 4; i++) {
        table[i].wToFile(outfile);
    }
    outfile << outOfPlay.size() << " "; // mark size of outOfPlay
    for (int i : outOfPlay) {
        outfile << i << " ";
    }
}

void Table::rFromFile(std::ifstream& infile) {
    
    int buildCount;
    for (int i = 0; i < 4; i++) {
        infile >> buildCount;
        table[i].rFromFile(infile, buildCount);
    }
    
    int outPlaySize;
    int card;
    infile >> outPlaySize;
    for (int i = 0 ; i < outPlaySize; ++i) {
        infile >> card;
        outOfPlay.push_back(card);
    }
    
}

bool Table::operator==(const Table& right) {
    for (int i = 0; i < 4; i++) {
        if (!(table[i] == right.table[i])) {
            return false;
        }
    }
    
    if (outOfPlay != right.outOfPlay) {
        return false;
    }
    
    return true;
    
}

