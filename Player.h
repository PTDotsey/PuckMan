#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <iostream>

struct Position {
	int row;
	int col;

	// already implemented for you!
	friend bool operator==(const Position & lhs, const Position &other) {
		return lhs.row == other.row && lhs.col == other.col;
	}

	friend std::ostream & operator << (std::ostream &out, const Position &p){
		out << "Position: [" << p.row << ", " << p.col << "]";
		return out;
	}
};

class Player {
public:
	// TODO: implement -- DONE!!
	Player(const std::string name, const bool is_human);  // constructor

	// These are already implemented for you
	std::string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool is_human() const {return is_human_; }  // inline member function
	bool hasTreasure() const {return has_Treasure_; }  // inline member function
	bool isDead() const {return isDead_; }  // inline member function
	int getLives() const {return lives_; }


	// TODO: implement the following functions
	// You MUST implement the following functions
	void ChangePoints(const int x);

	// set a new position for this player
	void SetPosition(Position pos);

	// checks if the player owns a treasure
	void setHasTreasure();

	//checks if the enemy is dead
	void setIsDead(bool isdead);

	//updates the lives for a player
	void setLives();


	// You may want to implement these functions as well
	// ToRelativePosition is a function we used to translate positions
	// into direction s relative to the player (up, down, etc)
	std::string ToRelativePosition(Position other);

	// Convert this player to a string representation of their name and points
	std::string Stringify();

	// this method should return the number of moves made by the player in this game 
	int getMoves();

	// update the number of moves in each human player's turn
	void incrementMoves();

	// You may add other functions as needed/wanted
	
	// overload the pritnt operator
	// friend std::ostream & operator << (std::ostream &out, const Player &p){
	// 	out << "Name: " << p.get_name();
	// 	out << "Points: " << p.get_points();
	// 	return out;
	// }

private:
	std::string name_;
	int points_;
	Position pos_;
	bool is_human_;
	bool has_Treasure_;
	bool isDead_;
	int lives_ = 3;
	int moves_;

	// You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_