#ifndef ASSIGN2_TILEBAG
#define ASSIGN2_TILEBAG

#include "LinkedList.h"
#include <iostream>
#include <string>
#include <fstream>

class TileBag {
public:

    //Constructor and Deconstructor

    TileBag();
    TileBag(std::string line);
    ~TileBag();

    //Misc Functions

    Node* getTile();
    bool isEmpty();
    void printBag();
    LinkedList* getTileBag();

    void clearBag();
    void addAt(Node* node, int index);

private:
    // Should not be called by other classes.
    void shuffle(LinkedList* nodeList);
    LinkedList* tileBag;
};

#endif