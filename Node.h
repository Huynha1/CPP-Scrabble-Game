#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:
   //Constructor
   Node(Tile tile);

   //Copy Constructor
   Node(Node& other);

   //Print Command
   void printNode();
   
   //Deconstructor
   ~Node();

   Tile     tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
