#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <random>
#include <iostream>
#include <time.h>

//Assume that the list goes from [0...n-1] where n is the length of the linkedList.
class LinkedList {
public:

   //Constructor, Copy Constructor and Deconstructor

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   //Misc functions

   int size();
   Node* get(int i);
   int search(Node* node);
   void clear();

   //Add functions

   void addFront(Node* node);
   void addBack(Node* node);
   void addAt(Node* node, int i);

   //Delete functions

   void deleteFront();
   void deleteBack();
   void deleteAt(int i);

   //Misc functions 2
   
   void printList();
   void scrabbleList();
   void stringToList(std::string line);

private:
   Node* head;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
