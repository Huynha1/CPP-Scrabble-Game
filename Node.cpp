#include <iostream>
#include "Node.h"

Node::Node(Tile tile) {
    this->tile = tile;
    this->next = nullptr;
}

Node::Node(Node& other) {
    this->tile = other.tile;
    //Will be properly defined in LinkedList, so just set to nullptr for now
    this->next = nullptr;
}

Node::~Node() {
}

void Node::printNode() {
    std::cout << "Node: " << this->tile.letter << "-" << this->tile.value << std::endl;
}