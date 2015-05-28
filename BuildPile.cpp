#include "BuildPile.hpp"

using std::deque;


bool BuildPile::playCard(int newCard, deque<int>& outOfPlay) {
    bool ret = false;
    if (newCard == 0 || newCard == (int) build.size() +  1){
        build.push(newCard);
        ret = true;
    }
    if (build.size() == 12) {
        putOutOfPlay(outOfPlay);
        ret = false;
    }
    return ret;
}

void BuildPile::putOutOfPlay(deque<int>& outOfPlay) {
    while (!build.empty()) {
        outOfPlay.push_back(build.top());
        build.pop();
    }
}

void BuildPile::wToFile(std::ofstream& outfile) {
    
    //flip buildPile stack to print in right order
    int buildSize = (int)build.size();
    outfile << buildSize << " "; //marks the size of the buildPile
    std::stack<int> temp;
    for (int i = 0; i < buildSize; i++) {
        temp.push(build.top());
        build.pop();
    }
    
    //Recreate buildPile from temp and print out temp to file
    buildSize = (int)temp.size();
    for (int i = 0; i < buildSize; i++) {
        outfile << temp.top() << " ";
        build.push(temp.top());
        temp.pop();
    }
}

void BuildPile::rFromFile(std::ifstream& infile, int buildSize) {
    
    int temp;
    for (int i = 0; i < buildSize; i++) {
        infile >> temp;
        build.push(temp);
    }
}

bool BuildPile::operator==(const BuildPile& right) {
    if (build != right.build) {
        return false;
    }
    return true;
}

