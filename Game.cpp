#include "Game.h"
#include <ctime>

struct{
    int treasurecount = 10;
    int pelletcount = 61;
} mystruct;
//Takes enum pf squaretype and returns unicode icon
std::string SquareTypeStringify(SquareType sq){
        if( sq ==  SquareType::Wall){ return "🧱";}
        if( sq ==  SquareType::Pellet){ return "🟡";}
        if( sq ==  SquareType::Pacman){ return "😀";}
        if( sq ==  SquareType::Treasure){ return "🍒";}
        if( sq ==  SquareType::Enemy){ return "👻";}
        if( sq ==  SquareType::Empty){ return "🟦";}
        if( sq ==  SquareType::PowerUp){ return "😠";}               
}

//creates board through a series of for loops. uses random numbers to generate various icons.
Board::Board()
{
  int rand = std::rand()%100+1;//numbers between 1 and 100

  for (int i = 0; i < get_rows(); i++)
  {
    for (int j = 0; j < get_cols(); j++)
    {
      arr_[i][j] = SquareType::Pellet;
      rand = std::rand()%100+1;
      if (rand <= 10 && arr_[i][j] == SquareType::Pellet)//10% chance
      {
        arr_[i][j] = SquareType::Treasure;
      }      
      if (rand > 10 && rand <= 31)//20% chance of wall
      {
        arr_[i][j] = SquareType::Wall;
      }
    }
  }
  arr_[0][0] = SquareType::Pacman;//human at (0,0)  
}

//returns value of square by pulling what is located on square position
SquareType Board::get_square_value(Position pos) const{
    return this->arr_[pos.row][pos.col];
}

//sets square value at specified location
void Board::SetSquareValue(Position pos, SquareType value){
    this->arr_[pos.row][pos.col] = value;
}

//scans surrounding positions around player and returns possible moves
std::vector<Position> Board::GetMoves(Player *p){
    std::vector<Position> placeholder;
    Position position = p->get_position(); 
    int i = position.row;
    int j = position.col;
    SquareType square;
    Position pos = {i-1, j};
    square = get_square_value(pos);

    if (square != SquareType::Wall ) {//up
            placeholder.push_back(pos);
    }
    pos = {i, j+1};//right
    square = get_square_value(pos);
    if (square != SquareType::Wall ) {
            placeholder.push_back(pos);
    }
    pos = {i+1, j};//down
    square = get_square_value(pos);
    if (square != SquareType::Wall) {
            placeholder.push_back(pos);
    }
    pos = {i, j-1};//left
    square = get_square_value(pos);
    if (square != SquareType::Wall) {
            placeholder.push_back(pos);
    }   
    return placeholder;
}

//function moves player and triggers actions depending on what is on the square they move to
bool Board::MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist){
    int pellet = 1;
    int treasure = 100;
    int enemyList=0;
    for (unsigned long int i=0; i<enemylist.size(); i++)
    {
        if (pos == enemylist[i]->get_position())
        {
            enemyList = i;
        }
    }

    // Checks conditions if player encounters enemy and takes action according to condition
    if (this->get_square_value(pos) == SquareType::Enemy){
       if (!p->hasTreasure()) {      
            this->SetSquareValue(pos, SquareType::Pacman);   
            enemylist[enemyList]->setIsDead(true);    
            p->setHasTreasure(); //if run into enemy with no treasure, lose life
            p->setLives();                              
       }
       else{ 
            this->SetSquareValue(pos, SquareType::Enemy);
            if (p->getLives() == 0){
                p->setIsDead(true); //if run into enemy with treasure, destroys enemy
            }
        }
    }

    if(this->get_square_value(pos) == SquareType::Wall)
    {
        p->incrementMoves();
        return false; //wall blocks movement
    }

    if (this->get_square_value(pos) == SquareType::Treasure){
        
        if(!p->hasTreasure()){
            p->ChangePoints(treasure);
            p->setHasTreasure();
            --mystruct.treasurecount; //collecting trasure if you don't have it makes player collect points and set state to having treasure
        }
        else{
            p->ChangePoints(treasure); //if you already have treasure, it just raises points
            --mystruct.treasurecount;
        }

    }

    if (this->get_square_value(pos) == SquareType::Pellet)//pellet check
    {
        p->ChangePoints(pellet);
        --mystruct.pelletcount; //collecting pellet increases score and decrements pellet counter

    }
    this->SetSquareValue(p->get_position(), SquareType::Empty);
    p->SetPosition(pos);   //all squares become empty when pacman visits them           

    if (!p->hasTreasure())
    { 
        this->SetSquareValue(pos, SquareType::Pacman); //if no treasure, regular pacman       
    }
    else 
    { 
       this->SetSquareValue(pos, SquareType::PowerUp); //if tresure, then super pacman 
    }
    p->incrementMoves();
    return true;
}

//controls enemy movement
bool Board::MoveEnemy(Player *p, Position pos){  
    this->SetSquareValue(p->get_position(), SquareType::Empty);
    p->SetPosition(pos);
    this->SetSquareValue(pos, SquareType::Enemy);//sets spot to enemy
    return true;

}

//constructor for game object
Game::Game(){
    this->board_ = new Board();
    std::vector<Player *> players_;
    this->turn_count_ = 0;
    this->GameOver = false;
}

//start new game
void Game::NewGame(Player *human, const int enemies)
{

  Position human_init_pos = {0,0};
  human->SetPosition(human_init_pos);
  players_.push_back(human);
  board_ = new Board();
  int i = 0;

  while(i < enemies)
  {
    Position enemy_positon = {rand() % board_->get_rows(), rand() % board_->get_cols()};// createsrandom enemy positions
    if(board_->get_square_value(enemy_positon) == SquareType::Pellet)
    {

      Player *enemy = new Player("enemy"+std::to_string(i), false); //creates new enemies in loop based on int enemies
      enemy->SetPosition(enemy_positon);//sets position to random position
      board_->SetSquareValue(enemy_positon, SquareType::Enemy); 
      players_.push_back(enemy);
      i++;
      }
  }
}

//controls player and enemy turns
void Game::TakeTurn(Player *p,std::vector<Player*> enemylist){
    //TODO:
    // ask for moves
    char input = ' ';
    int var1 = p->get_position().row;
    int var2 = p->get_position().col;
    Position pos;
    while ( toupper(input) != 'W' && toupper(input) != 'D' && toupper(input) != 'S' && toupper(input) != 'A'){
        std::cout << "Enter your move:" << std::endl;
        std::cin >> input;
        input = toupper(input);
        if ( input == 'W' || input == 'D' || input == 'S' || input == 'A') {

            // make move
            if (input == 'W') {// sets posiyion in array according to selection
                var1 =var1 -1;
                if (var1<0)
                {
                    var1=0;
                }
            }
             if (input == 'S') {
                var1 =var1 +1;
                if (var1>9)
                {
                    var1=9;
                }
            }
            if (input == 'A') {
                var2 =var2-1;
                if (var2<0)
                {
                    var2=0;
                }
            }
            if (input == 'D') {
                var2 =var2+1;
                if (var2>9)
                    {
                        var2=9;
                    }
            }
            pos = {var1,var2};
            this->setBoard(p,pos,enemylist);
        }
        else
        {
            std::cout << "Select a valid move" << std::endl;
        }
    }
    
}

//prints board
Board* Game::getBoard(){
    return this->board_; // prints board
}

//prints new board
void Game::setBoard(Player *p, Position pos, std::vector<Player*> enemylist){
    this->board_->MovePlayer(p,pos,enemylist);
}

Player* Game::getPlayer(int a){
    return this->players_[a]; //pulls player details
}

void Game::addToEnemyList(Player* enemy){
	this->players_.push_back(enemy); //adds number of enemies to
}

//prints possible player moves
std::string Game::printMoves(Player *p){
    std::vector<Position> position = this->getBoard()->GetMoves(p);
    std::string placeholder = "";
    long unsigned int sq = 4 - position.size();
    for (long unsigned int i = 0; i < position.size(); i++)
    {
        std::cout<<std::endl;
        placeholder +=  p->ToRelativePosition(position[i]);
    }
    for(long unsigned int j = 0; j<sq; j++)
    {
        std::cout<<"  "<<std::endl;
        placeholder += "\n";
    }
    return placeholder;
}

//controls enemy movement
void Game::TakeTurnEnemy(Player *p, std::vector<Player*> &enemylist){
    
}

//checks if player is dead
bool Game::IsGameOver(Player *p){
    Board b;
    
    if((p->getLives() <= 0) || ( mystruct.pelletcount <= 0 && mystruct.treasurecount <= 0)){  std::cout << GenerateReport(p) <<std::endl; return true;  }
    else{  return false;  }
}

//checks pellet count
bool Game::CheckifdotsOver(){
    return (this->dots_count_ == 0);
}

//prints end game report
std::string Game::GenerateReport(Player *p){
//p.Stringify();
}

//creates player
Player* Game::userCreatePlayer(){
    std::string name;
    std::cout<< "Enter Player Name:" << std::endl;
    std::cin >> name;
    Player *p = new Player(name, true);
    return p;
}


int Game::pelletcount(){
    int count, var1, var2 = 0;
    Position pos;
    //loops through all squares and counts pellets
    for (int var1=0; var1<10; var1++)
    {
        for (int var2=0; var2<10; var2++)
        {
            pos = {var1,var2};
            if (this->getBoard()->get_square_value(pos) == SquareType::Pellet)
            { 
                count +=1;
            }
        }
    }
    return count;
}

//retrieves enemy count
int Game::numberOfEnemies(){
    int num;
    std::string num_input;
    char selection = ' ';
    bool is_number = true;
    do {
        std::cout<< "How many enemies? Must be between two and ten:" << std::endl;
        std::cin >> num_input;

        // input validation
        for (long unsigned int i = 0; i < num_input.length(); i++){
            if (isdigit(num_input[i])) 
                { 
                is_number = true;
                num = stoi(num_input);     
                }
            else 
            {
                  is_number = false;  
            }
        }

        if ((is_number) && (num >= 2) && (num <= 10)) {
            std::cout << "Start game (Y/N)?" << std::endl;
            std::cout<< "Yes(Y)" << std::endl;
            std::cout<< "No(N)" << std::endl;   
            std::cin >> selection;
        }
        else{
            std::cout << "Please enter a valid number" << std::endl;
        }

    }
    while( toupper(selection) != 'Y');
    return num;
}

std::ostream& operator<<(std::ostream& os, const Board &b){
		Position position = {0,0};
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				
				position = {i, j};
				os << SquareTypeStringify( b.get_square_value(position) ) << " ";
			}
			os << std::endl;
		}		
		return os;
	}
