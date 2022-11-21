#include "Game.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

//Game Constructor.
//@param player1 Name of player1
//@param player2 Name of player2
Game::Game(std::string player1, std::string player2, bool checkWords, int numOfPlayers) {
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);

    this->numOfPlayers = numOfPlayers;

    this->tilebag = new TileBag();
    this->board = new Board(checkWords);
    this->endGame = false;
    this->endTurn = false;
    this->placeCommand = false;
    this->gameFinished = false;
    this->placedTile = false;
    this->bingoCounter = 0;
    this->curTurn = 1;
    this->lastPos = "";

    this->player1->fillHand(tilebag);
    this->player2->fillHand(tilebag);

    this->checkWords = checkWords;

    //Comment out when not needed
    //Clears tilebag for endgame cases
    // tilebag->clearBag();
}

Game::Game(std::string player1, std::string player2, std::string player3, bool checkWords, int numOfPlayers) {
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
    this->player3 = new Player(player3);

    this->numOfPlayers = numOfPlayers;

    this->tilebag = new TileBag();
    this->board = new Board(checkWords);
    this->endGame = false;
    this->endTurn = false;
    this->placeCommand = false;
    this->gameFinished = false;
    this->placedTile = false;
    this->bingoCounter = 0;
    this->curTurn = 1;
    this->lastPos = "";

    this->player1->fillHand(tilebag);
    this->player2->fillHand(tilebag);
    this->player3->fillHand(tilebag);

    this->checkWords = checkWords;

    //Comment out when not needed
    //Clears tilebag for endgame cases
    // tilebag->clearBag();
}

Game::Game(std::string player1, std::string player2, std::string player3, std::string player4, bool checkWords, int numOfPlayers) {
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
    this->player3 = new Player(player3);
    this->player4 = new Player(player4);

    this->numOfPlayers = numOfPlayers;

    this->tilebag = new TileBag();
    this->board = new Board(checkWords);
    this->endGame = false;
    this->endTurn = false;
    this->placeCommand = false;
    this->gameFinished = false;
    this->placedTile = false;
    this->bingoCounter = 0;
    this->curTurn = 1;
    this->lastPos = "";

    this->player1->fillHand(tilebag);
    this->player2->fillHand(tilebag);
    this->player3->fillHand(tilebag);
    this->player4->fillHand(tilebag);

    this->checkWords = checkWords;

    //Comment out when not needed
    //Clears tilebag for endgame cases
    // tilebag->clearBag();
}

//Load Game Constructor
//Overloads default constructor
//@param fileName name of the file to be loaded from, looks in gamesaves folder
Game::Game(std::string fileName) {
    std::string nameOfFile = fileName;
    this->gameLoaded = false;
    this->gameFinished = false;
    while (!gameLoaded) {
        try {
                loadGame(nameOfFile);
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
                std::cout << "failed to find game name." << std::endl;
                
                std::cout << "Enter filename of the save file: ";
                if (!getline(std::cin, nameOfFile)) {throw eofException();}
            }
        }
}

//Destructor
Game::~Game() {
    delete player1;
    delete player2;
    delete player3;
    delete player4;
    delete tilebag;
    delete board;
}

//Main game operation.
//Turn based loop.
//Ends when a player inputs EOF character or the game ends (player wins).
void Game::playGame() {
    while (!endGame) {
        try {
            if (this->curTurn == 1) {
                printScore(player1);
                getTurn(player1);
                this->curTurn = 2;
            }
            checkGameStatus();
            
            if (this->curTurn == 2) {
                printScore(player2);
                getTurn(player2);
                if (this->numOfPlayers == 3 || this->numOfPlayers == 4) {
                    this->curTurn = 3;
                }
                else {
                    this->curTurn = 1;
                }
            }
            checkGameStatus();

            if (this->curTurn == 3) {
                printScore(player3);
                getTurn(player3);
                if (this->numOfPlayers == 4) {
                    this->curTurn = 4;
                }
                else {
                    this->curTurn = 1;
                }
                checkGameStatus();
            }

            if (this->curTurn == 4) {
                printScore(player4);
                getTurn(player4);
                this->curTurn = 1;
                checkGameStatus();
            }

        }
        catch (std::exception& e) {
            if (gameFinished) {printGameResults();}
            this->endGame = true;
        }
    }
}

//Gets player input.
void Game::getTurn(Player* player) {

    this->endTurn = false;

    while (!endTurn) {
        try {
            std::cout << "> ";
            std::string input;
            if (!getline(std::cin, input)) {throw eofException();}
            parseInput(player, input);
        }
        catch (std::invalid_argument& e) {
            std::cout << "\nInvalid Input\n" << std::endl;
            //std::cout << e.what() << std::endl;
        }
    }
}

//Converts player input arguments into vector, validate the arguments and process the command given.
void Game::parseInput(Player* player, std::string input) {

    //Split the words into a vector
    std::vector<std::string> words{};
    std::string buffer;
    std::stringstream ss(input);

    while (ss >> buffer)
        words.push_back(buffer);

    if (words.size() <= 0) {
        throw std::invalid_argument("");
    }

    //Lower word to validate without cases
    for (unsigned int i = 0; i < words.size(); i++) {
        std::transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
    }
    
    //Parse arguments

    //Place Command
    if (words[0] == "place") {
        if (!placeCommand) {
            this->bingoCounter = 0;
        }
        this->placeCommand = true;
        placeTurn(player, words);
        
        //Continue getting commands if placecommand is continuing
        if (placeCommand) {
            getTurn(player);
        }
    }
    
    //If placing, only place commands should be allowed from here on out
    else if (this->placeCommand == true && placedTile) {
        throw std::invalid_argument("Only place commands are allowed. If finished, enter \"place done\"");
    }

    //Replace command
    else if (words[0] == "replace") {
        replaceTurn(player, words);
    }

    //Pass command
    else if (words[0] == "pass") {
        //Validate number of arguments
        if (words.size() != 1) {
            throw std::invalid_argument("Invalid number of arguments");
        }

        //Lose conditions
        if (this->tilebag->isEmpty()) {
            player->incrementPassCount();
        }

        if (player->getPassCount() == 2) {
            this->endGame = true;
            this->gameFinished = true;
            throw std::exception();
        }
    }

    //Invalid Argument
    else if (words[0] == "save" || words[0] == "help") {
        //Do nothing rn, just skips else statement
    }

    //Invalid Arguement
    else {
        throw std::invalid_argument("Invalid Input");
    }

    //If nothing was thrown
    this->endTurn = true;

    //Turn does not end if user saves game
    if (words[0] == "save") {
        if (words.size() != 2) {
            throw std::invalid_argument("Invalid number of arguments");
        }
        saveGame(words);
        this->endTurn = false;
        //Save then continue gameplay
    }
    if (words[0] == "help") {
        if (words.size() > 1) {
            throw std::invalid_argument("Invalid number of arguments");
        }
        std::cout << "Here are the command you can execute:" << std::endl;
        std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "place <tile> at <row><col> | To place a tile down e.g: place c at a2" << std::endl;
        std::cout << "place done                 | To end turn after placing tiles down" << std::endl;
        std::cout << "replace <tile>             | To replace a tile from hand with a random tile from bag e.g: replace t" << std::endl;
        std::cout << "pass                       | To pass turn" << std::endl;
        std::cout << "save <game_name>           | To save the game e.g: save game1\n" << std::endl;
        this->endTurn = false;

    }
}

//If a place turn command was parsed, this function is called
void Game::placeTurn(Player* player, std::vector<std::string> words) {
    //Guards
    if (words[1] == "done") {
        if (!placedTile) {
            throw std::invalid_argument("Invalid Input, please place a tile down before calling this command, otherwise pass.");
        }
        if (words.size() != 2) {
            throw std::invalid_argument("Argument length != 2");
        }
        this->endTurn = true;
        this->placeCommand = false;
        player->resetPassCount();
        //checkGameStatus();
        this->bingoCounter = 0;
        this->placedTile = false;
        board->checkWords(player, lastPos);
        player->fillHand(tilebag);

    }
    else if (words.size() != 4 && placeCommand == true) {
        throw std::invalid_argument("Invalid number of arguments. Number of arguments is not 4.");
    }

    if (words[1].length() != 1 && placeCommand == true) {
        throw std::invalid_argument("Invalid Argument for tile. Place command should be \"Place <tile letter> at <row position>");
    }

    if (words[2] != "at" && placeCommand == true) {
        throw std::invalid_argument("3rd argument is not \"at\".");
    }
    
    //If passed, run command
    if (placeCommand) {
        char tile = toupper(words[1][0]);
        Node* nodeToPlace = player->getTile(tile);
        std::transform(words[3].begin(), words[3].end(),words[3].begin(), ::toupper);
        this->board->placeTile(player, nodeToPlace, words[3]);
        this->bingoCounter += 1;
        this->placedTile = true;
        this->lastPos = words[3];
    }

    if (bingoCounter >= 7) {
        std::cout << "BINGO!" << std::endl;
        player->increaseScore(50);
    }
}

//If a replace turn command was parsed, this function is called
void Game::replaceTurn(Player* player, std::vector<std::string> words) {

    if (words.size() != 2) {
        throw std::invalid_argument("Invalid number of arguments.");
    }

    if (words[1].length() != 1) {
        throw std::invalid_argument("Tile passed as argument is of incorrect length (should only be 1 character long).");
    }

    char tile = words[1][0];
    try {
        player->replaceTile(this->tilebag, tile);
    } catch (std::out_of_range& e) {
        throw std::invalid_argument("There are no tiles left in the tilebag.");
    }
}

//If a save command was parsed, this function is called
void Game::saveGame(std::vector<std::string> words) {
    //std::string saveGameTitle = "gamesaves/" + words[1] + ".txt";
    std::string saveGameTitle = "TestCases/" + words[1] + ".save";
    std::ofstream saveGame(saveGameTitle);

    //Save game settings
    //Check Words Setting
    saveGame << this->checkWords << std::endl;
    //Number of players
    saveGame << this->numOfPlayers << std::endl;
    

    //Save Player details
    saveGame << player1->getName() << std::endl;
    saveGame << player1->getScore() << std::endl;
    for (int i = 0; i < player1->getHand()->size(); i++) {
        saveGame << player1->getHand()->get(i)->tile.letter << "-" << player1->getHand()->get(i)->tile.value;
        if (i == player1->getHand()->size() - 1) {
            saveGame << std::endl;
        }
        else {
            saveGame << ", ";
        }
    }

    saveGame << player2->getName() << std::endl;
    saveGame << player2->getScore() << std::endl;
    for (int i = 0; i < player2->getHand()->size(); i++) {
        saveGame << player2->getHand()->get(i)->tile.letter << "-" << player2->getHand()->get(i)->tile.value;
        if (i == player2->getHand()->size() - 1) {
            saveGame << std::endl;
        }
        else {
            saveGame << ", ";
        }
    }

    if (this->numOfPlayers == 3 || this->numOfPlayers == 4) {
        saveGame << player3->getName() << std::endl;
        saveGame << player3->getScore() << std::endl;
        for (int i = 0; i < player3->getHand()->size(); i++) {
            saveGame << player3->getHand()->get(i)->tile.letter << "-" << player3->getHand()->get(i)->tile.value;
            if (i == player3->getHand()->size() - 1) {
                saveGame << std::endl;
            }
            else {
                saveGame << ", ";
            }
        }
    }

    if (this->numOfPlayers == 4) {
        saveGame << player4->getName() << std::endl;
        saveGame << player4->getScore() << std::endl;
        for (int i = 0; i < player4->getHand()->size(); i++) {
            saveGame << player4->getHand()->get(i)->tile.letter << "-" << player4->getHand()->get(i)->tile.value;
            if (i == player4->getHand()->size() - 1) {
                saveGame << std::endl;
            }
            else {
                saveGame << ", ";
            }
        }
    }

    //Get Board state
    saveGame << board->getBoardString();
    

    //Get TileBag state
    LinkedList* tb = tilebag->getTileBag();
    for (int i = 0; i < tb->size(); i++) {
        saveGame << tb->get(i)->tile.letter << "-" << tb->get(i)->tile.value;
        if (i == tb->size() - 1) {
            saveGame << std::endl;
        }
        else {
            saveGame << ", ";
        }
    }
    if(this->curTurn == 1){
        saveGame << player1->getName() << std::endl;
    }
    else if(this->curTurn == 2){
        saveGame << player2->getName() << std::endl;
    }
    else if(this->curTurn == 3) {
        saveGame << player3->getName() << std::endl;
    }
    else {
        saveGame << player4->getName() << std::endl;
    }
    // These for loops will save the taken words and taken positions from the board.
    for (int i = 0 ; i < board->takenWords.size() ; ++i) {
        saveGame << board->takenWords[i] + " ";
    }
    saveGame << std::endl;

    for (int i = 0 ; i < board->takenFirstPos.size() ; ++i) {
        saveGame << board->takenFirstPos[i] + " ";
    }
    saveGame << std::endl;

    for (int i = 0 ; i < board->takenLastPos.size() ; ++i) {
        saveGame << board->takenLastPos[i] + " ";
    }
    saveGame << std::endl;

    std::cout << "\nGame successfully saved" << std::endl;
    std::cout << std::endl;
}

//If user selected loadgame in menu, this function is used to load game elements into play
void Game::loadGame(std::string fileName) {

    /*

    NOTE:

    IT IS ASSUMED THAT THE CONTENTS OF WHATEVER SAVE FILE TO BE LOADED INTO THE GAME IS UNTAMPERED WITH.
    AS OF RIGHT NOW THERE IS CURRENTLY NO ACTIONS IN PLACE TAKEN THAT AIM TO CHECK THAT A SAVEGAME IS VALID.
    IT IS ALSO ASSUMED THAT WHEN THE GAME IS LOADED, IT IS CURRENTLY PLAYER 1's TURN
    */

    std::string line;
    std::ifstream infile;
    // fileName = "gamesaves/" + fileName;
    // fileName += ".txt";
    fileName = "TestCases/" + fileName;
    fileName += ".save";
    infile.open(fileName);

    //Check if file exists
    //If thrown here, no objects created yet
    if (!infile) {
        throw std::invalid_argument("");
    }

    //Initialize player details
    std::string player1Name = ""; 
    int player1Score = 0;
    std::string player2Name =  ""; 
    int player2Score = 0;
    std::string player3Name = "";
    int player3Score = 0;
    std::string player4Name = "";
    int player4Score = 0;
    
    //Initialize what needs to be initalized
    //this->board = new Board(true);

    this->endGame = false;
    this->endTurn = false;
    this->placeCommand = false;
    bool initializedTB = false;
    int counter = -2;
    int playerIncrement = 0;
    bool oldFileFormat = false;
    /*
    NOTE: COUNTER INDICATES WHICH LINE REPRESENTS WHAT KIND OF INFORMATION
    */
    while (getline (infile, line) && oldFileFormat == false) {
        if (counter == -2) {
            if (line == "1") {
                this->board = new Board(true);
                this->checkWords = true;
            }
            else if (line == "0") {
                this->board = new Board(false);
                this->checkWords = false;
            } 
            else if (line == "#milestone2_format") {
                oldFileFormat = true;
            }
        }
        else if (counter == -1) {
            this->numOfPlayers = std::stoi("" + line);
            if (this->numOfPlayers == 3) {
                playerIncrement = 3;
            }
            else if (this->numOfPlayers == 4) {
                playerIncrement = 6;
            }
        }
        else if (counter == 0) {
            player1Name = line;
        }
        else if (counter == 1) {
            player1Score = std::stoi(line);
        }
        else if (counter == 2) {
            LinkedList* player1hand = new LinkedList();
            player1hand->stringToList(line);

            //Overload constructor
            this->player1 = new Player(player1Name, player1Score, player1hand);
            delete player1hand;
        }
        else if (counter == 3) {
            player2Name = line;
        }
        else if (counter == 4) {
            player2Score = std::stoi("" + line);
        }
        else if (counter == 5) {
            LinkedList* player2hand = new LinkedList();
            player2hand->stringToList(line);
            
            //Overload constructor
            this->player2 = new Player(player2Name, player2Score, player2hand); 
            delete player2hand;
        }
        else if (counter == 6 && (this->numOfPlayers == 3 || this->numOfPlayers == 4)) {
            player3Name = line;
        }
        else if (counter == 7 && (this->numOfPlayers == 3 || this->numOfPlayers == 4)) {
            player3Score = std::stoi("" + line);
        }
        else if (counter == 8 && (this->numOfPlayers == 3 || this->numOfPlayers == 4)) {
            LinkedList* player3hand = new LinkedList();
            player3hand->stringToList(line);
                
            //Overload constructor
            this->player3 = new Player(player3Name, player3Score, player3hand); 
            delete player3hand;           
        }
        else if (counter == 9 && (this->numOfPlayers == 4)) {
            player4Name = line;
        }
        else if (counter == 10 && (this->numOfPlayers == 4)) {
            player4Score = std::stoi("" + line);
        }
        else if (counter == 11 && (this->numOfPlayers == 4)) {
            LinkedList* player4hand = new LinkedList();
            player4hand->stringToList(line);
                
            //Overload constructor
            this->player4 = new Player(player4Name, player4Score, player4hand); 
            delete player4hand;         
        }
        else if (counter == playerIncrement + 8+COLS) {
            
            //Overload constructor
            this->tilebag = new TileBag(line);
            initializedTB = true;
        }
        else if (counter == playerIncrement + 9+COLS) {

            if (line == player1->getName()) {
                this->curTurn = 1;
            }
            else if (line == player2->getName()) {
                this->curTurn = 2;
            }
            else if (line == player3->getName()) {
                this->curTurn = 3;
            }
            else {
                this->curTurn = 4;
            }

        } 
        else if (counter == playerIncrement + 10+COLS) {
            std::stringstream ss(line);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> tokens(begin, end);
            for (auto &s: tokens) {
                this->board->takenWords.push_back(s);
            }
        }
        else if (counter == playerIncrement + 11+COLS) {
            std::stringstream ss(line);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> tokens(begin, end);
            for (auto &s: tokens) {
                this->board->takenFirstPos.push_back(s);
            }
        }
        else if (counter == playerIncrement + 12+COLS) {
            std::stringstream ss(line);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> tokens(begin, end);
            for (auto &s: tokens) {
                this->board->takenLastPos.push_back(s);
            }
        }
        //Implies rest is part of the Board
        else {
            //Loop through each step of the board from it's first to last position
            //By default this is initial position 4, final position 60 and step size 4.
            for (int i = BOARD_FIRST_POS; i <= (BOARD_STEP_SIZE*COLS); i += BOARD_STEP_SIZE) {
                if (line[i] != ' ') {
                    std::string strPos = line[0] + std::to_string((i / 4) - 1);
                    // std::cout << strPos << std::endl;
                    
                    Tile currentTile;
                    currentTile.letter = line[i];
                    currentTile.value = 0;
                    Node* currentNode = new Node(currentTile);
                    
                    try {
                        board->placeTile(currentNode, strPos);
                        delete currentNode;
                    }
                    //Invalid tile
                    catch (std::invalid_argument& e) {
                        delete currentNode;
                    }
                }
            }
        }
        counter++;
    }
    counter = -1;
    infile.clear();
    infile.seekg(0);

    // This while loop will be used to load the milestone2 saved files
    while (getline (infile, line) && oldFileFormat == true) {
        if (counter == -1) {
            // Does nothing, just pass the first line
        }
        else if (counter == 0) {
            this->board = new Board(false);
            this->checkWords = false;
            this->numOfPlayers = 2;
            player1Name = line;
        }
        else if (counter == 1) {
            player1Score = std::stoi(line);
        }
        else if (counter == 2) {
            LinkedList* player1hand = new LinkedList();
            player1hand->stringToList(line);

            //Overload constructor
            this->player1 = new Player(player1Name, player1Score, player1hand);
            delete player1hand;
        }
        else if (counter == 3) {
            player2Name = line;
        }
        else if (counter == 4) {
            player2Score = std::stoi("" + line);
        }
        else if (counter == 5) {
            LinkedList* player2hand = new LinkedList();
            player2hand->stringToList(line);
            
            //Overload constructor
            this->player2 = new Player(player2Name, player2Score, player2hand); 
            delete player2hand;
        }
        else if (counter == 8+COLS) {
            
            //Overload constructor
            this->tilebag = new TileBag(line);
            initializedTB = true;
        }
        else if (counter == 9+COLS) {
            if (line.compare(player2->getName()) == 0){
                this->curTurn = 2;
            }
            else{
                this->curTurn = 1;
            }
        }
        //Implies rest is part of the Board
        else {
            //Loop through each step of the board from it's first to last position
            //By default this is initial position 4, final position 60 and step size 4.
            for (int i = BOARD_FIRST_POS; i <= (BOARD_STEP_SIZE*COLS); i += BOARD_STEP_SIZE) {
                if (line[i] != ' ') {
                    std::string strPos = line[0] + std::to_string((i / 4) - 1);
                    // std::cout << strPos << std::endl;
                    
                    Tile currentTile;
                    currentTile.letter = line[i];
                    currentTile.value = 0;
                    Node* currentNode = new Node(currentTile);
                    
                    try {
                        board->placeTile(currentNode, strPos);
                        delete currentNode;
                    }
                    //Invalid tile
                    catch (std::invalid_argument& e) {
                        delete currentNode;
                    }
                }
            }
        }
        counter++;
    }
    //If tilebag is empty
    if (!initializedTB) {
        // std::cout << "creating tilebag"
        this->tilebag = new TileBag("");
    }
    gameLoaded = true;
    std::cout << "Scrabble game successfully loaded" << std::endl;
}

//checks if current player's hand has size 0. If true, break
void Game::checkGameStatus() {
    if (this->player1->getHand()->size() == 0 || this->player2->getHand()->size() == 0) {
        this->endGame = true;
        this->gameFinished = true;
        throw std::exception();
    }
    if (this->numOfPlayers == 3 || this->numOfPlayers == 4) {
        if (this->player3->getHand()->size() == 0) {
            this->endGame = true;
            this->gameFinished = true;
            throw std::exception();            
        }
    }
    if (this->numOfPlayers == 4) {
        if (this->player4->getHand()->size() == 0) {
            this->endGame = true;
            this->gameFinished = true;
            throw std::exception();            
        }
    }
}

//Prints current turn details for player.
//Prints according to assignment specifications:
//- Which player turn
//- Both player's scores
//- Current board state
//- Current player's hand
void Game::printScore(Player* player) {
    std::cout << std::endl;
    std::cout << player->getName() << ", it's your turn" << std::endl;
    std::cout << "Score for " << this->player1->getName() << ": " << player1->getScore() << std::endl;
    std::cout << "Score for " << this->player2->getName() << ": " << player2->getScore() << std::endl;
    if (this->numOfPlayers == 3 || this->numOfPlayers == 4) {
        std::cout << "Score for " << this->player3->getName() << ": " << player3->getScore() << std::endl;
    }
    if (this->numOfPlayers == 4) {
        std::cout << "Score for " << this->player4->getName() << ": " << player4->getScore() << std::endl;
    }

    std::cout << board->getBoardString();

    std::cout << std::endl;

    std::cout << "Your hand is" << std::endl;
    player->printHand();
    std::cout << std::endl;
}

//Prints when bool gameFinished is true
void Game::printGameResults() {
    std::cout << "\nGame Over" << std::endl;
    std::cout << "Score for " << this->player1->getName() << ": " << this->player1->getScore() << std::endl;
    std::cout << "Score for " << this->player2->getName() << ": " << this->player2->getScore() << std::endl;
    if (numOfPlayers > 2) {
        std::cout << "Score for " << this->player3->getName() << ": " << this->player3->getScore() << std::endl;
        if (numOfPlayers == 4) {
            std::cout << "Score for " << this->player4->getName() << ": " << this->player4->getScore() << std::endl;
        }
    }

    int highestscore = this->player1->getScore();
    std::string winningplayer = this->player1->getName();

    if (this->player2->getScore() > highestscore) {
        highestscore = this->player2->getScore();
        winningplayer = this->player2->getName();
    }
    if (this->player3->getScore() > highestscore && this->numOfPlayers > 2) {
        highestscore = this->player3->getScore();
        winningplayer = this->player3->getName();
    }
    if (this->player4->getScore() > highestscore && this->numOfPlayers == 4) {
        highestscore = this->player4->getScore();
        winningplayer = this->player4->getName();
    }

    if (this->player1->getScore() == this->player2->getScore()) {
        if (this->numOfPlayers == 3) {
            if (this->player1->getScore() == this->player3->getScore()) {
                highestscore = -1;
            }
        }
        else if (this->numOfPlayers == 4) {
            if (this->player1->getScore() == this->player3->getScore() && this->player3->getScore() == this->player4->getScore()) {
                highestscore = -1;
            }
        }
        else {
            highestscore = -1;
        }
    }

    if (highestscore == -1) {
        std::cout << "Draw!" << std::endl;
    }
    else {
        std::cout << "Player " << winningplayer << " won!" << std::endl;
    }


}