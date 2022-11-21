#include "Board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

//Constructor
Board::Board(bool checkForWords) {

    // Enable or disable check for word setting
    this->checkForWords = checkForWords;

    //Initialize Board

    for (int i = 0; i < ROWS; i++) {
        std::vector<char> tempVector;
        for (int j = 0; j < COLS; j++) {
            tempVector.push_back(' ');
        }
        this->board.push_back(tempVector);
    }

    //Initialize Row values

    //Generates key-value pairs based on number of rows in #define, ROWS should be a value between 0 and 26 or this code will use weird charicters 
    char curLetter = 'A';
    for(int i = 0; i < ROWS; i++){
        rows[curLetter+i] = i;
    }

    if (this->checkForWords == true) {
        //Adds all the words from the word text file into a vector
        std::string filename("Words");
        std::string line;

        std::ifstream input_file(filename);

        while (getline(input_file, line)){
            //Fix it up so that if the word is invalid then remove the word
            if (line.length() > 1) {
                transform(line.begin(), line.end(), line.begin(), toupper);
                this->Words.push_back(line);
            }
        }
        
        input_file.close();

        //These vectors are pushed with empty values so they can be iterated through.
        this->takenWords.push_back("");
        this->takenFirstPos.push_back("");
        this->takenLastPos.push_back("");
        this->invalidWord = false;
        this->takenValsToDel = 0;
    }

}

//Deconstructor
Board::~Board() {
}

//Places a node to a strPos.
//Assume position formatted to "row""column". i.e: placing node C-1 at A0
//@param node Node to place. 
//@param strPos will split the row and column within the function.
void Board::placeTile(Player* player, Node* node, std::string strPos) {

    //Guard

    //Check Row
    char row = strPos[0];
    if (rows.find(row) == rows.end() ) {
        throw std::invalid_argument("Invalid row entered.");
    }

    //Check column

    std::string colString = strPos.substr(1, -1);
    if (std::any_of(std::begin(colString), std::end(colString), ::isalpha)) {
            throw std::invalid_argument("Invalid column entered");         //Letter inside
        }

    int col = std::stoi(colString);

    if (col > 14 || col < 0) {
            throw std::invalid_argument("Invalid column entered.");
        }

    //If pass, place at board and increase player's score
    if (this->board[rows[row]][col] != ' ') {
        throw std::invalid_argument("You can't place a tile that is already filled in!");
    }
    this->board[rows[row]][col] = node->tile.letter;
    
    if (this->checkForWords == true) { 
        this->placedPos.push_back(strPos);
        this->tilesToRemove.push_back(node);
    }


    //If the check for word setting is false then run these statements
    if (this->checkForWords == false) {
        player->increaseScore(node->tile.value);
        player->removeTile(node);
    }
}

//This function will calculate the score of the word that a user has scored.
void Board::updateScore(Player* player, std::string word) {
    int totalscore = 0;

    std::map<char, int> wordval;
    wordval.insert(std::pair<char,int>('A',1));
    wordval.insert(std::pair<char,int>('B',3));
    wordval.insert(std::pair<char,int>('C',3));
    wordval.insert(std::pair<char,int>('D',2));
    wordval.insert(std::pair<char,int>('E',1));
    wordval.insert(std::pair<char,int>('F',4));
    wordval.insert(std::pair<char,int>('G',2));
    wordval.insert(std::pair<char,int>('H',4));
    wordval.insert(std::pair<char,int>('I',1));
    wordval.insert(std::pair<char,int>('J',8));
    wordval.insert(std::pair<char,int>('K',5));
    wordval.insert(std::pair<char,int>('L',1));
    wordval.insert(std::pair<char,int>('M',3));
    wordval.insert(std::pair<char,int>('N',1));
    wordval.insert(std::pair<char,int>('O',1));
    wordval.insert(std::pair<char,int>('P',3));
    wordval.insert(std::pair<char,int>('Q',10));
    wordval.insert(std::pair<char,int>('R',1));
    wordval.insert(std::pair<char,int>('S',1));
    wordval.insert(std::pair<char,int>('T',1));
    wordval.insert(std::pair<char,int>('U',1));
    wordval.insert(std::pair<char,int>('V',4));
    wordval.insert(std::pair<char,int>('W',4));
    wordval.insert(std::pair<char,int>('X',8));
    wordval.insert(std::pair<char,int>('Y',4));
    wordval.insert(std::pair<char,int>('Z',10));

    for (int i = 0 ; i < word.length() ; ++i) {
        totalscore += wordval.at(word[i]);
    }
    // These are vectors of words and their score that will be updated for the player.
    this->scoredWords.push_back(word);
    this->wordScores.push_back(totalscore);
}

//This function will check for words horizontally on the board
void Board::checkHori(Player* player, char row, int col) {
    //This boolean variable will check within this function if the word has been found
    bool foundWord = false;

    char currChar = this->board[rows[row]][col];
    std::string currentWord = "";

    //This while loop will move the starting character to the most left position of the tiles
    while (isspace(this->board[rows[row]][col-1]) == 0 && col - 1 >= 0) {
        --col;
        currChar = this->board[rows[row]][col];
    }

    //firstpos is the position of the first letter
    std::string firstPos = row + std::to_string(col);
    currentWord += currChar;

    //This while loop will concatenate the characters to currword as it scans every tile to the most right position
    while (isspace(this->board[rows[row]][col+1]) == 0 && col + 1 <= 14) {
        ++col;
        currChar = this->board[rows[row]][col];
        currentWord += currChar;
    }

    //lastpos is the last position of the last letter
    std::string lastPos = row + std::to_string(col);

    bool takenPos = false;

    //this for loop will loop through the words vector to see if the word created by the user is valid
    for (int i = 0; i < this->Words.size() ; ++i) {
        if (this->Words[i] == currentWord) {
            foundWord = true;
            //this inner for loop will check if the word scanned is already taken
            for (int j = 0 ; j < this->takenWords.size() ; ++j) {
                if (this->Words[i] == this->takenWords[j] && firstPos == this->takenFirstPos[j] && lastPos == this->takenLastPos[j]) {
                    takenPos = true;
                }
                else if (currentWord.size() > 1 && j == this->takenWords.size() - 1 && takenPos == false) {
                    this->takenWords.push_back(currentWord);
                    this->takenFirstPos.push_back(firstPos);
                    this->takenLastPos.push_back(lastPos);
                    this->updateScore(player, currentWord);
                    this->takenValsToDel += 1;
                    currentWord = "";
                }
            }
        }
        else if (i == this->Words.size() - 1 && currentWord.size() > 1 && foundWord == false) {
            // This statement will check if a word is valid
            this->invalidWord = true;
        }
    }

}

//This function will check for words vertically on the board
void Board::checkVert(Player* player, char row, int col) {
    // This boolean variable will check within this function if the word has been found
    bool foundWord = false;

    char currChar = this->board[rows[row]][col];
    std::string currentWord = "";

    //This while loop will move the starting character to the most top position of the tiles
    while (isspace(this->board[rows[row - 1]][col]) == 0 && row - 1 >= 'A') {
        --row;
        currChar = this->board[rows[row]][col];
    }

    //firstpos is the position of the first letter
    std::string firstPos = row + std::to_string(col); 
    currentWord += currChar;

    //This while loop will concatenate the characters to currword as it scans every tile to the most lowest position
    while (isspace(this->board[rows[row + 1]][col]) == 0  && row + 1 <= 'O') {
        ++row;
        currChar = this->board[rows[row]][col];
        currentWord += currChar;
    }

    //lastpos is the last position of the last letter
    std::string lastPos = row + std::to_string(col);

    bool takenPos = false;

    //this for loop will loop through the words vector to see if the word created by the user is valid
    for (int i = 0; i < this->Words.size() ; ++i) {
        if (this->Words[i] == currentWord) {
            foundWord = true;
            //this inner for loop will check if the word scanned is already taken
            for (int j = 0 ; j < this->takenWords.size() ; ++j) {
                if (this->Words[i] == this->takenWords[j] && firstPos == this->takenFirstPos[j] && lastPos == this->takenLastPos[j]) {
                    takenPos = true;
                }
                else if (currentWord.size() > 1 && j == this->takenWords.size() - 1 && takenPos == false) {
                    this->takenWords.push_back(currentWord);
                    this->takenFirstPos.push_back(firstPos);
                    this->takenLastPos.push_back(lastPos);
                    this->updateScore(player, currentWord);
                    this->takenValsToDel += 1;
                    currentWord = "";
                }
            }
        }
        else if (i == this->Words.size() - 1 && currentWord.size() > 1 && foundWord == false) {
            // This statement will check if a word is valid
            this->invalidWord = true;
        }
    }

}

void Board::checkWords(Player* player, std::string strPos) {
    if (this->checkForWords == true) {
        //Row
        char row = strPos[0];

        //Column

        std::string colString = strPos.substr(1, -1);

        int col = std::stoi(colString);

        char ogrow = strPos[0];
        char ogcol = std::stoi(colString);

        // This if statement will check if a single letter was placed by checking for white space around it
        if ((isspace(this->board[rows[row]][col-1]) == 1 || col - 1 < 0) && (isspace(this->board[rows[row]][col+1]) == 1 || col + 1 > 14) && (isspace(this->board[rows[row - 1]][col]) == 1 || row - 1 < 'A') && (isspace(this->board[rows[row + 1]][col]) == 1 || row + 1 > 'O')) {
            this->invalidWord = true;
        }
        
        // This while loop will shift the current pos to the very left
        while (isspace(this->board[rows[row]][col-1]) == 0 && col - 1 >= 0) {
            --col;
        }

        // The statement below will scan for words vertically and horizontally based on the current position
        this->checkVert(player, row, col);
        this->checkHori(player, row, col);

        // This while loop will shift the current position the very left and scan for words vertically and horizontally
        while (isspace(this->board[rows[row]][col+1]) == 0 && col + 1 <= 14) {
            ++col;
            this->checkVert(player, row, col);
            this->checkHori(player, row, col);
        }

        row = ogrow;
        col = ogcol;

        // This while loop will shift the current position upwards
        while (isspace(this->board[rows[row - 1]][col]) == 0 && row - 1 >= 'A') {
            --row;
        }

        this->checkHori(player, row, col);
        this->checkVert(player, row, col);

        // This while loop will shift the current position downwards and scan for words vertically and horizontally.
        while (isspace(this->board[rows[row + 1]][col]) == 0  && row + 1 <= 'O') {
            ++row;
            this->checkHori(player, row, col);
            this->checkVert(player, row, col);
        }
        // If a word that was scanned is invalid then the tiles that are placed will be removed
        if (this->invalidWord == true) {
            for (int i = 0 ; i < this->placedPos.size() ; ++i) {
                this->board[rows[this->placedPos[i][0]]][std::stoi(this->placedPos[i].substr(1, -1))] = ' ';
            }
            std::cout << "Word placed down by " << player->getName() << " is invalid, their turn is passed." << std::endl;
            for (int i = 0 ; i < this->takenValsToDel ; ++i) {
                this->takenWords.pop_back();
                this->takenFirstPos.pop_back();
                this->takenLastPos.pop_back();
            }

        }
        //TODO make load work with check words
        // If word is valid then players scored will updated 
        if (this->invalidWord == false) {
            // This for loop removes the tile that was placed from the players hand
            for (int i = 0 ; i < this->tilesToRemove.size() ; ++i) {
                player->removeTile(this->tilesToRemove[i]);
            }
            for (int i = 0 ; i < this->scoredWords.size() ; ++i) {
                std::cout << "\n" << player->getName() << " scored " << this->wordScores[i] << " points for " << this->scoredWords[i] << std::endl;
                player->increaseScore(this->wordScores[i]);
            }
        }

        //These variables and vectors are reset after each players turn.
        this->takenValsToDel = 0;
        this->scoredWords.clear();
        this->wordScores.clear();
        this->tilesToRemove.clear();
        this->placedPos.clear();
        this->invalidWord = false;
    }

}

// Placing tile without player interaction (for load game)
void Board::placeTile(Node* node, std::string strPos) {

    char row = strPos[0];
    if (rows.find(row) == rows.end() ) {
        throw std::invalid_argument("Invalid row entered.");
    }

    std::string colString = strPos.substr(1, -1);
    if (std::any_of(std::begin(colString), std::end(colString), ::isalpha)) {
            throw std::invalid_argument("Invalid column entered");         //Letter inside
        }

    int col = std::stoi(colString);

    if (col > 14 || col < 0) {
            throw std::invalid_argument("Invalid column entered.");
        }

    if (this->board[rows[row]][col] != ' ') {
        throw std::invalid_argument("You can't place a tile that is already filled in!");
    }
    this->board[rows[row]][col] = node->tile.letter;
}


//Gets the state of the board
std::string Board::getBoardString(){
    std::string finalString = "";
    std::string topString = "    ";
    std::string bottomString = "----";
    // Generates the top of the table based on the size of the board
    for(unsigned int i = 0; i < COLS; i++){
        std::string iString = std::to_string(i);
        // This checks the number of digits and adjusts the formatting accordingly
        if(i < 10){
            topString = topString + iString;
            topString = topString + "   ";
        }
        else if(i < 100){
            topString = topString + iString;
            topString = topString + "  ";
        }
        else if(i < 1000){
            topString = topString + iString;
            topString = topString + " ";
        }
        bottomString = bottomString + "----";
    }
    // Trims off the end
    topString.pop_back();
    bottomString.pop_back();
    // Puts together the top of table
    finalString += topString + "\n";
    finalString += bottomString + "\n";

    char baseLetter = 'A';
    for (unsigned int i = 0; i < ROWS; i++) {
        char curLetter = baseLetter + i;
        // Generates the char of the corresponding row
        finalString.push_back(curLetter);
        finalString += " | ";
        // Generates the rest of the row based on the size of the board
        for (unsigned int j = 0; j < this->board[i].size(); j++) {
            finalString += this->board[i][j];
            finalString += " | ";
        }
        finalString += "\n";
    }
    return finalString;
}

std::vector<std::vector<char>> Board::getBoard() {
    return this->board;
}