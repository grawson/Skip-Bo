//
//  TestGame.cpp
//  
//

#include "Game.hpp"
#include "Human.hpp"
#include <cstdio>
#include <cassert>

using std::cout;
using std::endl;

class TestGame {
public:
    
  static void testAddPlayer() {
    Game game;
        
    assert(game.addHuman("Gavi", 3) == 1);
    assert(game.players.back()->name == "Gavi"); //Player "Gavi" was added
    assert(game.players.back()->color == 3); //Color is blue
        
    assert(game.addHuman("gavi", 0) == 1);
    assert(game.players.back()->name == "gavi"); //Player "gavi" was added
    assert(game.players.back()->color == 0); //Color is red
  }
    
  static void testWRToFile() {
        
        
    Human* plyr1 = new Human("Gavi", 3);
        
    //create hand: 1 2 3
    plyr1->hand.add(1);
    plyr1->hand.add(2);
    plyr1->hand.add(3);
        
    //create discPiles 4 5 6 - 7 8 - XX - 9 10 11
    plyr1->discPile[0].push_back(4);
    plyr1->discPile[0].push_back(5);
    plyr1->discPile[0].push_back(6);
    plyr1->discPile[1].push_back(7);
    plyr1->discPile[1].push_back(8);
    plyr1->discPile[3].push_back(9);
    plyr1->discPile[3].push_back(10);
    plyr1->discPile[3].push_back(11);
        
    //create stockPile 12 13 14 15 16
    plyr1->stockPile.push(12);
    plyr1->stockPile.push(13);
    plyr1->stockPile.push(14);
    plyr1->stockPile.push(15);
    plyr1->stockPile.push(16);
        
    Human* plyr2 = new Human("John", 2);
        
    //create hand: 3 2 1
    plyr2->hand.add(3);
    plyr2->hand.add(2);
    plyr2->hand.add(1);
        
    //create discPiles 11 10 9 - 8 7 - XX - 6 5 4
    plyr2->discPile[0].push_back(11);
    plyr2->discPile[0].push_back(10);
    plyr2->discPile[0].push_back(9);
    plyr2->discPile[1].push_back(8);
    plyr2->discPile[1].push_back(7);
    plyr2->discPile[3].push_back(6);
    plyr2->discPile[3].push_back(5);
    plyr2->discPile[3].push_back(4);
        
    //create stockPile 12 13 14 15 16
    plyr2->stockPile.push(12);
    plyr2->stockPile.push(13);
    plyr2->stockPile.push(14);
    plyr2->stockPile.push(15);
    plyr2->stockPile.push(16);
   
    //add the player1 to a game1
    Game game1;
    game1.players.push_back(plyr1);
      
    //write the game to a file
    std::ofstream outfile ("Skipbo_SavedTest.txt");
    game1.wToFile(outfile);
    outfile.close();
        
    //read file into game2
    Game game2;
    std::ifstream infile ("Skipbo_SavedTest.txt");
    game2.rFromFile(infile);
    infile.close();

    assert(game1 == game2);

    game1.players.push_back(plyr2); //add player2 to game1

    //write game1 to file
    std::ofstream outfile2 ("Skipbo_SavedTest.txt");
    game1.wToFile(outfile2); //write game1
    outfile2.close();
        
    //read file into game 3
    std::ifstream infile2 ("Skipbo_SavedTest.txt");
    Game game3;
    game3.rFromFile(infile2); //read game1 into game3
    infile2.close();

    assert(game1 == game3);
        
    game1.players.pop_back(); //remove plyr2
    assert(!(game1 == game3));
    
    //add plyr2 back to game 3
    game3.players.push_back(plyr2);
    std::ofstream outfile3 ("Skipbo_SavedTest.txt");
    game3.wToFile(outfile3); //write game3
    outfile3.close();
      
    //read file into game4
    std::ifstream infile3 ("Skipbo_SavedTest.txt");
    Game game4;
    game4.rFromFile(infile3); //read game3 into game4
    infile3.close();

    assert(game3 == game4);
        
    //add Decks to game3
    game3.inPlay.deck.push_back(17);
    game3.inPlay.deck.push_back(18);
    game3.inPlay.deck.push_back(19);
    game3.inPlay.deck.push_back(20);
    game3.table.outOfPlay.push_back(21);
    game3.table.outOfPlay.push_back(22);
    game3.table.outOfPlay.push_back(23);
    game3.table.outOfPlay.push_back(24);
        
    //create buldpiles
    game3.table.table[0].build.push(25);
    game3.table.table[0].build.push(26);
    game3.table.table[2].build.push(27);
    game3.table.table[2].build.push(28);
        
    assert(!(game3 == game4));
        
    //write game3 to file
    std::ofstream outfile4 ("Skipbo_SavedTest.txt");
    game3.wToFile(outfile4); //write game3
    outfile4.close();

    //read file into game5
    std::ifstream infile4 ("Skipbo_SavedTest.txt");
    Game game5;
    game5.rFromFile(infile4); //read game3 into game5
    infile4.close();
      
    assert(game3 == game5);

  }
    
  static void testSaveLoad() {
    Game game1;
    Game game2;
    Game game3;
      
    game1.saveGame();
    game2.loadGame();
        
    assert(game1 == game2); //empty games are equal
     
    Human* plyr1 = new Human("Gavi", 3);
      
    //create hand: 1 2 3
    plyr1->hand.add(1);
    plyr1->hand.add(2);
    plyr1->hand.add(3);
        
    //create discPiles 4 5 6 - 7 8 - XX - 9 10 11
    plyr1->discPile[0].push_back(4);
    plyr1->discPile[0].push_back(5);
    plyr1->discPile[0].push_back(6);
    plyr1->discPile[1].push_back(7);
    plyr1->discPile[1].push_back(8);
    plyr1->discPile[3].push_back(9);
    plyr1->discPile[3].push_back(10);
    plyr1->discPile[3].push_back(11);
        
    //create stockPile 12 13 14 15 16
    plyr1->stockPile.push(12);
    plyr1->stockPile.push(13);
    plyr1->stockPile.push(14);
    plyr1->stockPile.push(15);
    plyr1->stockPile.push(16);
      
    Human* plyr2 = new Human("John", 5);
    
    //create hand: 1 2 3
    plyr2->hand.add(1);
    plyr2->hand.add(2);
    plyr2->hand.add(3);
    
    //create discPiles 4 5 6 - 7 8 - XX - 9 10 11
    plyr2->discPile[0].push_back(4);
    plyr2->discPile[0].push_back(5);
    plyr2->discPile[0].push_back(6);
    plyr2->discPile[1].push_back(7);
    plyr2->discPile[1].push_back(8);
    plyr2->discPile[3].push_back(9);
    plyr2->discPile[3].push_back(10);
    plyr2->discPile[3].push_back(11);
    
    //create stockPile 12 13 14 15 16
    plyr2->stockPile.push(12);
    plyr2->stockPile.push(13);
    plyr2->stockPile.push(14);
    plyr2->stockPile.push(15);
    plyr2->stockPile.push(16);
      
    game1.players.push_back(plyr1); //add player1 to game1
    game1.players.push_back(plyr2); //add player2 to game1

    //add Decks to game1
    game1.inPlay.deck.push_back(17);
    game1.inPlay.deck.push_back(18);
    game1.inPlay.deck.push_back(19);
    game1.inPlay.deck.push_back(20);
    game1.table.outOfPlay.push_back(21);
    game1.table.outOfPlay.push_back(22);
    game1.table.outOfPlay.push_back(23);
    game1.table.outOfPlay.push_back(24);
     
    //create buldpiles
    game1.table.table[0].build.push(25);
    game1.table.table[0].build.push(26);
    game1.table.table[2].build.push(27);
    game1.table.table[2].build.push(28);
      
    game1.saveGame(); //save data in file
    game3.loadGame(); //loads game from data

    assert(game1 == game3);
    assert(!(game1 == game2)); //does not equal empty game2
        
  }
};


int main() {
    
  cout << endl << "Testing playStock..." << endl;
  TestGame::testAddPlayer();
  cout << "playStock tests passed." << endl;
    
  cout << endl << "Testing reading and writing to file..." << endl;
  TestGame::testWRToFile();
  cout << "reading and writing tests passed." << endl;
    
  cout << endl << "Testing save and load..." << endl;
  TestGame::testSaveLoad();
  cout << "save and load tests passed." << endl << endl;
    
  cout << "All tests passed." << endl << endl;
    
  return 0;

}
