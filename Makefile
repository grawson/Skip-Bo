CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -O -g

bin: Skip-Bo

test:	containerTests dumbAITest playerTest gameTest
	@echo "Running tests..."
	echo "testGame.txt testGame.txt testGame.txt testGame.txt" | ./gameTest
	./containerTests
	./dumbAITest
	./playerTest
	@echo "All tests passed!"

Hand.o: Hand.cpp Hand.hpp
	$(CC) $(CXXFLAGS) -c Hand.cpp

Deck.o: Deck.cpp Deck.hpp
	$(CC) $(CXXFLAGS) -c Deck.cpp

BuildPile.o: BuildPile.cpp BuildPile.hpp
	$(CC) $(CXXFLAGS) -c BuildPile.cpp

Table.o: Table.cpp Table.hpp BuildPile.hpp
	$(CC) $(CXXFLAGS) -c Table.cpp BuildPile.cpp

Player.o: Player.cpp Player.hpp Table.hpp Hand.hpp Deck.hpp BuildPile.hpp
	$(CC) $(CXXFLAGS) -c Player.cpp

dumbAI.o: dumbAI.cpp dumbAI.hpp Player.hpp Hand.hpp BuildPile.hpp Table.hpp Deck.hpp
	$(CC) $(CXXFLAGS) -c dumbAI.cpp

Human.o: Human.cpp Human.hpp Player.hpp Hand.hpp BuildPile.hpp Deck.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c Human.cpp

Game.o: Game.cpp Game.hpp Deck.hpp Player.hpp Hand.hpp BuildPile.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c Game.cpp

TestCases.o: TestCases.cpp Deck.hpp BuildPile.hpp Hand.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c TestCases.cpp

TestDumbAI.o: TestDumbAI.cpp Player.hpp dumbAI.hpp Human.hpp Deck.hpp BuildPile.hpp Hand.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c TestDumbAI.cpp

TestGame.o: TestGame.cpp Game.hpp Player.hpp Human.hpp dumbAI.hpp Deck.hpp BuildPile.hpp Hand.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c TestGame.cpp

testPlayer.o: testPlayer.cpp Human.hpp Player.hpp Deck.hpp BuildPile.hpp Hand.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c testPlayer.cpp

Skip-Bo.o: Skip-BoDriver.cpp Skip-BoDriver.hpp Game.hpp Player.hpp Human.hpp dumbAI.hpp Deck.hpp BuildPile.hpp Hand.hpp Table.hpp
	$(CC) $(CXXFLAGS) -c Skip-BoDriver.cpp

containerTests: TestCases.o Deck.o BuildPile.o Hand.o Table.o
	$(CC) $(CXXFLAGS) TestCases.o Deck.o BuildPile.o Hand.o Table.o -o containerTests

dumbAITest: TestDumbAI.o Player.o dumbAI.o Human.o Hand.o Table.o BuildPile.o Deck.o
	$(CC) $(CXXFLAGS) TestDumbAI.o Player.o dumbAI.o Human.o Hand.o Table.o Deck.o BuildPile.o -o dumbAITest

playerTest: testPlayer.o Player.o Human.o Deck.o BuildPile.o Hand.o Table.o
	$(CC) $(CXXFLAGS) testPlayer.o Player.o Human.o Deck.o BuildPile.o Hand.o Table.o -o playerTest

gameTest: TestGame.o Game.o Player.o Human.o dumbAI.o Hand.o Deck.o Table.o BuildPile.o
	$(CC) $(CXXFLAGS) TestGame.o Game.o  Player.o Human.o dumbAI.o Hand.o Deck.o Table.o BuildPile.o -o gameTest

Skip-Bo: Skip-Bo.o Game.o Player.o Human.o dumbAI.o Hand.o Deck.o Table.o BuildPile.o
	$(CC) $(CXXFLAGS) Skip-BoDriver.o Game.o  Player.o Human.o dumbAI.o Hand.o Deck.o Table.o BuildPile.o -o Skip-Bo

clean:
	rm -f a.out *~ *.o *.gcov *# *.gcda *.gch *.gcno gmon.out containerTests dumbAITest playerTest gameTest Skipbo_SavedTest.txt Skip-Bo
