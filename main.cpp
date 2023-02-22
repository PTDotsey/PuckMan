#include "Player.h"
#include "Game.h"
bool keepGoing = false;
char selection = ' ';
int pelletcount = 67;
int treasurecount = 10;
int main(){
    Game game = Game();// makes new game
    std::vector<Player*> el; 
    Player *p;// makes player object
    int e;
    do{  
        std::cout << "______________________________" << std::endl;
        std::cout << "______________________________" << std::endl;
        std::cout << "Make a selection from the menu below:" << std::endl;      
        std::cout << "Begin Game      B" << std::endl;
        std::cout << "Exit            E" << std::endl;
        std::cin >> selection;

//start game loop
        if ( toupper(selection) =='B' ){
            p = game.userCreatePlayer();//makes new player
            e = game.numberOfEnemies();
            game.NewGame(p,e);//new game

//loop for game execution. Runs until game is ended by loss of lves or pellet counter decremented to zero
            while( !game.IsGameOver(p) && (game.pelletcount() > 0) ){
                 if (keepGoing){
                    game.TakeTurn(p, el);
// enemy takes turn, loops through all enemies
                    for (long unsigned int i=0; i<el.size(); i++){
                        game.TakeTurnEnemy(el[i],el);    
                    }
                    game.pelletcount(); //checks pellet count
                }
                std::cout << *game.getBoard();
                std::cout << "______________________________" << std::endl;
                std::cout << p->Stringify() << std::endl;
                std::cout << "______________________________" << std::endl;
                std::cout << "Choose a Move:                 ( Use Letter Key )" << game.printMoves(p)<< std::endl;
                std::cout << "______________________________" << std::endl;
                keepGoing= true;
                
            }

            std::cout << "______________________________" << std::endl;
            std::cout << "           Game Over          " << std::endl;
            std::cout << "     Here are your results!         " << std::endl;
            std::cout << "______________________________" << std::endl << std::endl; 
            std::cout << p->Stringify() <<std::endl; //prints end game report          
        }
        game = Game();
        keepGoing = false;
    }while ( toupper(selection) != 'E' );//will loop as long as exit is no selected
    return 0;   // exit program
}