#include "Player.h"

//Constructor.
//Player's hand is initially empty. Should call fillHand() once game starts.
Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
    this->passCount = 0;
}

//Overload constructor
Player::Player(std::string name, int score, LinkedList* hand) {
    this->name = name;
    this->score = score;
    this->hand = new LinkedList(*hand);
    this->passCount = 0;
}

//Deconstructor
Player::~Player() {
    delete hand;
}

//Returns player's name.
std::string Player::getName() {
    return this->name;
}

//Returns player's score.
int Player::getScore() {
    return this->score;
}

//Returns player's hand.
LinkedList* Player::getHand() {
    return this->hand;
}

//Print Function.
//Should only be used for debugging purposes.
void Player::printPlayer() {
    std::cout << "Player: " << this->name << " Score: " << this->score << " Hand: " << std::endl;
    this->hand->printList();
}

void Player::increaseScore(int value) {
    this->score += value;
}

void Player::printHand() {
    for (int i = 0; i < this->hand->size(); i++) {
        std::cout << this->hand->get(i)->tile.letter << "-" << this->hand->get(i)->tile.value;
        if (i == this->hand->size() - 1) {
            std::cout << std::endl;
        }
        else {
            std::cout << ", ";
        }
    }
}

//Initialize player's hand
void Player::fillHand(TileBag* tb) {
    for (int i = this->hand->size() ; i < SCRABBLE_HAND ; ++i) {
        if (!tb->isEmpty()) {
            Node* tile = tb->getTile();
            this->hand->addBack(tile);
        }
    }
}

//Replace a tile by removing from hand and grabbing a new one from the Scrabble LinkedList.
void Player::replaceTile(TileBag* tb, char letter) {
    letter = toupper(letter);
    //Find position of tile to replace from hand
    int replacementIndex = -1;
    Tile tile;
    tile.letter = letter;
    tile.value = 0;
    
    Node* tempTile = new Node(tile);
    replacementIndex = this->hand->search(tempTile);

    if (replacementIndex == -1) {
        throw std::invalid_argument("Tile does not exist in player hand.");
    }

    delete tempTile;

    //Will throw an error here if the tilbag is empty.
    Node* newTile = tb->getTile();
    Node* oldTile = new Node(*getTile(letter));

    this->hand->deleteAt(replacementIndex);
    this->hand->addAt(newTile, replacementIndex);

    //Place tile in tilebag.
    //Assuming that it should be placed in a random location:

    //For testing purposes time seed is set to 69.
    srand(69);

    //To run normally, uncomment the srand function bellow and comment the srand function above.
    //srand(time(NULL));
    int randomVal = rand() % (tb->getTileBag()->size());
    tb->addAt(oldTile, randomVal);
}

Node* Player::getTile(char letter) {
    letter = toupper(letter);
    //Find position of tile to replace from hand
    int replacementIndex = -1;
    Tile tile;
    tile.letter = letter;
    tile.value = 0;
    
    Node* tempTile = new Node(tile);
    Node* returnTile = nullptr;
    replacementIndex = this->hand->search(tempTile);

    if (replacementIndex == -1) {
        delete tempTile;
        throw std::invalid_argument("Tile entered does not exist in the player's hand.");
    }
    else {
        returnTile = this->hand->get(replacementIndex);
    }

    delete tempTile;
    return returnTile;
}

void Player::removeTile(Node* node) {
    //Find position of tile to replace from hand
    int replacementIndex = -1;

    replacementIndex = this->hand->search(node);

    if (replacementIndex == -1) {
        throw std::invalid_argument("Tile does not exist in player hand.");
    }

    //Delete from hand
    this->hand->deleteAt(replacementIndex);
}

// Return the number of times the player has passed
int Player::getPassCount() {
    return this->passCount;
}

// Increment the pass count
void Player::incrementPassCount() {
    this->passCount += 1;
}
// Reset the pass count
void Player::resetPassCount() {
    this->passCount = 0;
}