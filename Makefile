CXX = g++
CXXFLAGS	= -std=c++17 -Wall
CXXTESTFLAGS = --coverage # can be used to generate files that help calculate unit test coverage
CXXGDB = -ggdb
OBJECTS = Player.o Game.o

.PHONY: Player.o Game.o test main

all: Player.o Game.o test main

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

test: $(OBJECTS) test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

main: $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	rm Player.o Game.o test main