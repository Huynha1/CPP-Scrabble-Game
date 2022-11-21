#include "TileBag.h"

//Constructor.
//Initialized by reading the scrabbleTiles.txt file and randomizing the order.
TileBag::TileBag() {
    this->tileBag = new LinkedList();

    //Parses scrabbleTiles.txt to a LinkedList
    std::string line;
    std::ifstream scrabbleTiles ("ScrabbleTiles.txt");
    if (scrabbleTiles.is_open()) {
        while (!scrabbleTiles.eof()) {
            getline(scrabbleTiles, line);
            if (line[0] != '\0') {
                Tile currentTile;
                currentTile.letter = line[0];
                currentTile.value = std::stoi(line.substr(1,-1));
                Node* currentNode = new Node(currentTile);
                this->tileBag->addBack(currentNode);
            }
        }
        scrabbleTiles.close();
    }

    //Shuffle linkedlist
    shuffle(this->tileBag);
}

//Overload Constructor.
//Uses LinkedList StringToList(string) function.
TileBag::TileBag(std::string line) {
    this->tileBag = new LinkedList();

    this->tileBag->stringToList(line);
}

//Deconstructor.
TileBag::~TileBag() {
    delete tileBag;
}

//Returns a copy of the  head node and deletes the head node.
//Used by Player class to fill hand.
Node* TileBag::getTile() {
    Node* currentNode = this->tileBag->get(0);

    //Consider empty tilebag
    if (currentNode == nullptr) {
        throw std::out_of_range("Tilebag is empty!");
    }

    Node* tile = new Node(*currentNode);
    this->tileBag->deleteFront();
    return tile;
}

bool TileBag::isEmpty() {
    bool isEmpty = false;

    if (this->tileBag->size() == 0) {
        isEmpty = true;
    }

    return isEmpty;
}

//Print Function.
//Prints to the assignment specifications (comma seperated)
void TileBag::printBag() {
    Node* currentNode = this->tileBag->get(0);
    while (currentNode != nullptr) {
        if (currentNode->next != nullptr) {
            std::cout << currentNode->tile.letter << "-" << currentNode->tile.value << ", ";
        } 
        else {
            std::cout << currentNode->tile.letter << "-" << currentNode->tile.value << std::endl;
        }
        currentNode = currentNode->next;
    }
}

//Returns the tilebag.
LinkedList* TileBag::getTileBag() {
    return this->tileBag;
}

//Calls LinkedList scrabbleList() function.
void TileBag::shuffle(LinkedList* nodeList) {
    this->tileBag->scrabbleList();
}

void TileBag::clearBag() {
    this->tileBag->clear();
}

void TileBag::addAt(Node* node, int index) {
    this->tileBag->addAt(node, index);
}