#ifndef ASSIGN2_BOARD
#define ASSIGN2_BOARD

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#include "Node.h"
#include "Player.h"

#define ROWS 15
#define COLS 15

class Board {
public:

    //Constructor and Deconstructor

    Board(bool checkForWords);
    ~Board();

    //Game Functions
    
    void placeTile(Node* node, std::string position);
    void placeTile(Player* player, Node* node, std::string position);
    void updateScore(Player* player, std::string word);
    void checkWords(Player* player, std::string position);
    void checkVert(Player* player, char row, int col);
    void checkHori(Player* player, char row, int col);
    std::string getBoardString();
    std::vector<std::vector<char>> getBoard();
    std::vector<std::string> takenWords;
    std::vector<std::string> takenFirstPos;
    std::vector<std::string> takenLastPos;
    int takenValsToDel;
    std::vector<std::string> Words;

    std::vector<std::string> placedPos;
    bool invalidWord;
    std::vector<Node*> tilesToRemove;
    bool checkForWords;
    std::vector<std::string> scoredWords;
    std::vector<int> wordScores;


private:
    std::vector<std::vector<char>>  board;
    std::map<char, int>             rows;
};

#endif