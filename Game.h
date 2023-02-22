#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <fstream>
#include "Player.h"

enum class SquareType { Wall, Pellet, Pacman, Treasure, Enemy, Empty, PowerUp };

// TODO: implement
std::string SquareTypeStringify(SquareType sq);

class Board {
public:
	// TODO: implement
	Board();
	int get_rows() const {return 10; }
	int get_cols() const {return 10; }

	// // TODO: you MUST implement the following functions
	SquareType get_square_value(Position pos) const;
	void SetSquareValue(Position pos, SquareType value);
	std::vector<Position> GetMoves(Player *p);
	bool MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist);
    bool MoveEnemy(Player *p, Position pos);
	friend std::ostream& operator<<(std::ostream& os, const Board &b);
	int pelletCount = 67;
	int treasurecount = 20;

private:
	SquareType arr_[10][10];
	int arr2_ [10][10];
	int rows_;
	int cols_;
}; 

class Game {
public:
	// TODO: implement these functions
	Game(); // constructor
	void NewGame(Player *human, const int enemies);
	void TakeTurn(Player *p,std::vector<Player*> enemylist);
	void TakeTurnEnemy(Player *p, std::vector<Player*> &enemylist);
	bool 
	IsGameOver(Player *p);
	bool CheckifdotsOver();
	std::string GenerateReport(Player *p);
	Player* userCreatePlayer();
	int numberOfEnemies();
	Board* getBoard();
	void setBoard(Player *p, Position pos, std::vector<Player*> enemylist);
	Player* getPlayer(int i);
	void addToEnemyList(Player* enemy);
	std::string printMoves(Player *printMoves);
	void minusPellet(int &x);
	void minusTreasure(int &x);
	int pelletcount();
	

	Board *board_;
	std::vector<Player *> players_;
	int turn_count_;
    int dots_count_;
	int treasurecount_;
    bool GameOver;

};
#endif  // _GAME_H_
