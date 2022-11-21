#ifndef ASSIGN2_GAME
#define ASSIGN2_GAME
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

#include "TileBag.h"
#include "Player.h"
#include "Board.h"

//These #defines are used mainly in loading a game
#define BOARD_FIRST_POS     4
#define BOARD_STEP_SIZE     4

class Game {
public:

    //Constructor/Destructor

    Game(std::string player1, std::string player2, bool CheckWords, int numOfPlayers);
    Game(std::string player1, std::string player2, std::string player3, bool CheckWords, int numOfPlayers);
    Game(std::string player1, std::string player2, std::string player3, std::string player4, bool CheckWords, int numOfPlayers);
    Game(std::string fileName);
    ~Game();

    //Main Function

    void playGame();

    struct eofException : public std::exception {
        const char* what() const throw() {
            return "EOF";
        }
    };

private:
    /*
    THESE FUNCTIONS SHOULD ONLY BE INTERNALLY CALLED
    */

    //Print commands

    void printScore(Player* player);
    void printGameResults();

    //Turn processors
    void getTurn(Player* player);
    void parseInput(Player* player, std::string input);
    void placeTurn(Player* player, std::vector<std::string> words);
    void replaceTurn(Player* player, std::vector<std::string> words);

    void checkGameStatus();
    
    //Save/Load functions
    void saveGame(std::vector<std::string> words);
    void loadGame(std::string fileName);


    Player*     player1;
    Player*     player2;
    Player*     player3;
    Player*     player4;
    TileBag*    tilebag;
    Board*      board;
    int         curTurn;        //signifies which player has the current turn: 2 == player2, else player 1
    bool        endGame;        //signifies that the game is finished
    bool        endTurn;        //signifies that the turn is finished, move to next player turn
    bool        placeCommand;   //signifies that a place command has been inputted, loop until "place done"
    bool        gameLoaded;     //signifies that the game's been loaded, resume normal gameplay
    bool        gameFinished;   //signifies that the game is finished, and a winner has been decided
    bool        placedTile;     //signifies that a tile has been placed, used to update bingocounter
    int         bingoCounter;   //counter that prints BINGO! when 7 tiles have been placed
    std::string lastPos;        //last tile position of the word being placed
    bool        checkWords;     //if true then word validation will be enabled
    int         numOfPlayers;   //number of players

};

#endif // ASSIGN2_GAME