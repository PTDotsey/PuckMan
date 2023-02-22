#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Player.h"
#include "Game.h"

TEST_CASE ("Player"){

    SECTION("Construction test"){
        bool is_human = true;
        std::string name = "Preston";    
        Player test = Player(name, is_human);

        REQUIRE(test.get_name() == "Preston");
        REQUIRE(test.get_points() == 0 );
        REQUIRE(test.is_human() == true);
        REQUIRE(test.getLives() == 3);
    }   
}

TEST_CASE ("Board Tests"){
    // testing constructors
    Board board = Board();
    Player *p = new Player("Preston", true);
    std::vector<Player*> test;

    SECTION ("print board test"){
        std::cout << board << std::endl;
    }
    
    SECTION("Test Moving"){
        Position pos1 = {3,4};
        Position pos2 = {3,4};
        Position pos3 = {4,4};
        Position pos4 = {4,4};
        REQUIRE(pos1 == pos2);
        REQUIRE(pos3 == pos4);    
    
        board.MovePlayer(p, pos1, test);
        std::cout << "1." << board <<std::endl;
        std::cout << "\n" << board <<std::endl;
        Position addition = {0,0};
        addition = pos3;
        board.MovePlayer(p, pos3, test);
        std::cout << "2."<< board<<std::endl;
        std::cout << "\n" << board <<std::endl;
        REQUIRE( addition == pos3);  
    }
        SECTION("testing player moves"){
        std::vector<Position> pos = board.GetMoves(p);
        for (long unsigned int i = 0; i < pos.size(); i++){
            std::cout << p->ToRelativePosition(pos[i]) << " ";
        }
    }
    
}

TEST_CASE("Testing increasing points"){
    SECTION("adding points"){
        Player p = Player("Preston", true);
        REQUIRE(p.get_points() == 0);
        const int x = 100;
        p.ChangePoints(x);
        REQUIRE(p.get_points()==100);
        
    }
}




