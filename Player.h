#ifndef ASSIGN2_PLAYER
#define ASSIGN2_PLAYER

#include <string>
#include <iostream>
#include <time.h> //Used in placing tile randomly in tilebag

#include "LinkedList.h"
#include "TileBag.h"

#define SCRABBLE_HAND 7

class Player {
public:

    //Constructor and Deconstructor
    Player(std::string name);
    Player(std::string name, int score, LinkedList* hand);
    ~Player();

    //Get methods

    std::string getName();
    int getScore();
    LinkedList* getHand();

    void increaseScore(int value);

    //Game functions

    void fillHand(TileBag* tb);
    void replaceTile(TileBag* tb, char letter);
    void removeTile(Node* node);
    void printHand();
    Node* getTile(char letter);

    
    //Misc functions
    
    void printPlayer();
    int getPassCount();
    void incrementPassCount();
    void resetPassCount();

private:
    std::string name;
    int         score;
    LinkedList* hand;
    int         passCount;
};

#endif