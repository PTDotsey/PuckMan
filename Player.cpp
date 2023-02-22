#include <iostream>
#include "Player.h"
//player constructor
Player::Player(const std::string name, const bool is_human){
    
    if (is_human){
        this->name_ = name;
        Position p = {0,0};
        this->pos_ = p;
    }else{
        Position e = { (rand()%8)+1, (rand()%8)+1 };
        this->pos_ = e;
    }

    this->is_human_ = is_human;
    this->points_ = 0;
    this->has_Treasure_ = false;
    this->isDead_ = false;
    this->lives_ = 3;
    this->moves_ = 0;
}

//updates players points
void Player::ChangePoints(const int x){
    this->points_ += x;
}

//sets player objects position in board
void Player::SetPosition(Position pos){
    this->pos_ = pos;
}

//updates players treasure status
void Player::setHasTreasure(){
    this->has_Treasure_ = (!this->hasTreasure());
}

//checks if enemy is dead
void Player::setIsDead(bool isdead){
    this->isDead_ = isdead;
}

//decrements lives counter
void Player::setLives(){
    this->lives_ -= 1;
}

//scans moves and translates to instruction
std::string Player::ToRelativePosition(Position other){
    if (this->pos_.row-1 == other.row && this->pos_.col == other.col) { return "UP      W";}
    if (this->pos_.row+1 == other.row && this->pos_.col == other.col) { return "DOWN    S";}
    if (this->pos_.row == other.row && this->pos_.col-1 == other.col) { return "LEFT    A";}
    if (this->pos_.row == other.row && this->pos_.col+1 == other.col) { return "RIGHT   D";}
    else return "No relative Position";
}

//prints player info including points, name and lives
std::string Player::Stringify(){
    return ("Name: " + this->get_name() + "\nPoints: " + std::to_string(this->get_points()) + "\tLives: " + std::to_string(this->getLives())); 
}

//retrieves player moves made
int Player::getMoves(){
    return this->moves_;
}

//increments move counter
void Player::incrementMoves(){
    this->moves_++;
}
