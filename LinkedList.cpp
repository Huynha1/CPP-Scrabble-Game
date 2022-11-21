#include "LinkedList.h"

//Constructor
LinkedList::LinkedList() {
    this->head = nullptr;
    this->length = 0;
}

//Copy Constructor
LinkedList::LinkedList(LinkedList& other) {

    //Initialize values
    this->head = nullptr;
    this->length = 0;

    //Copy elements
    for (int i = 0; i < other.size(); i++) {
        Node* currentNode = new Node(*other.get(i));
        addBack(currentNode);
    }
}

//Deconstructor
LinkedList::~LinkedList() {
    Node* currentNode = this->head;
    Node* nextNode = nullptr;
    
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nullptr;
        currentNode = nextNode;
    }
}

//Returns the length of the LinkedList
int LinkedList::size() {
    return this->length;
}

//Returns Node at @param index
Node* LinkedList::get(int index) {
    //Guard clause
    if (index > this->length || index < 0) {
        throw std::out_of_range("Trying to call LinkedList get function for an index outside it's range [0...n].");
    }
    
    Node* currentNode = this->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

//Returns (int) the first instance of the given node, even when multiple are found.
int LinkedList::search(Node* node) {
    Node* currentNode = this->head;
    int returnCounter = -1;
    int counter = 0;
    while (currentNode != nullptr) {
        if (currentNode->tile.letter == node->tile.letter) {
            if (returnCounter == -1) {
                returnCounter = counter;
            }
        }
        counter++;
        currentNode = currentNode->next;
    }
    return returnCounter;
}

//Clears LinkedList. Does not deconstruct pointer to the LinkedList.
void LinkedList::clear() {
    //Guard: List is empty
    if (this->length <= 0) {
        throw std::domain_error("Linked List is already empty.");
    }

    //Guard: When there is more than 1 Node in the list
    if (this->length > 1) {
        Node* currentNode = this->head->next;

        while(currentNode != nullptr) {
            this->head->next = currentNode->next;
            currentNode->next = nullptr;
            delete currentNode;
            currentNode = this->head->next;
        }
    }

    //Delete the head
    delete this->head;
    this->head = nullptr;

    this->length = 0;
}

//Adds a @param node to the front of the list
void LinkedList::addFront(Node* node) {
    //Case 1: List is empty
    if (this->length == 0) {
        this->head = node;
    }
    //Case 2: List is not empty
    else {
        Node* oldHead = this->head;
        this->head = node;
        node->next = oldHead;
    }

    this->length++;
}

//Adds a @param node to the end of the list
void LinkedList::addBack(Node* node) {
    Node* currentNode = this->head;
    
    //Case 1: Empty list
    if (this->length == 0) {
        this->head = node;
        node->next = nullptr;
    } 
    //Case 2: Not empty list
    else {
        Node* prevNode = nullptr;

        //Go to end node
        while (currentNode != nullptr) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        prevNode->next = node;
        node->next = nullptr;
    }

    this->length++;
}

//Adds a @param node to the position @param i.
//Fails if 
void LinkedList::addAt(Node* node, int i) {
    //Guard 1: Adding at front 
    if (i == 0) {
        // std::cout << "Index passed in is the first element. Calling 'addFront'" << std::endl;
        addFront(node);
    }

    //Guard 2: Adding at back
    else if (i == this->length) {
        // std::cout << "Index passed in is the last element. Calling 'addBack'" << std::endl;
        addBack(node);
    }

    //Guard 3: Out of range
    else if (i < 0 || i > this->length) {
        throw std::out_of_range("Index is not within range. Please ensure it is not a negative value or greater than the length of the list.");
    }

    //End of guards
    else {
        Node* currentNode = this->head;
        Node* prevNode = nullptr;

        //Reach index to swap at
        for (int index = 0; index < i; index++) {
            if (currentNode == nullptr) {
                throw std::logic_error("Linked List is detached.");
            }
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        //Insert node at index
        prevNode->next = node;
        node->next = currentNode;
        this->length++;
    }
}

//Deletes the head node and is replaced by the next one.
void LinkedList::deleteFront() {
    //Guard: Empty list
    if (this->length <= 0) {
        throw std::out_of_range("Linked List is empty. Can't delete front.");
    }

    //End of guard
    else {
        Node* newHead = this->head->next;
        delete this->head;
        this->head = newHead;      

        this->length--;
    }
}

//Deletes tail node and sets its previous to nullptr.
void LinkedList::deleteBack() {
    //Guard: Empty list
    if (this->length <= 0) {
        throw std::out_of_range("Linked List is empty. Can't delete front.");
    }

    //End of guard
    else {
        Node* currentNode = this->head;
        Node* prevNode = nullptr;

        //Go to end node
        while (currentNode->next != nullptr) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        delete currentNode;
        currentNode = nullptr;
        prevNode->next = currentNode;

        this->length--;
    }
}

//Deletes the node at @param index
void LinkedList::deleteAt(int index) {
    //Guard: Out of range
    if (index > length || index < 0) {
        throw std::out_of_range("Linked List is empty. Can't delete at.");
    }
    
    //End of guard

    Node* currentNode = this->head;
    Node* prevNode = nullptr;
    
    //Case 1: First element
    if (index == 0) {
        // std::cout << "Index passed in is the first element. Calling 'deleteFront'" << std::endl;
        deleteFront();
    } 
    
    //Case 2: Last element
    else if (index == this->length) {
        // std::cout << "Index passed in is the last element. Calling 'deleteBack'" << std::endl;
        deleteBack();
    }

    //Case 3: Not first or last element
    else {
        for (int i = 0; i < index; i++) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        prevNode->next = currentNode->next;
        delete currentNode;
        currentNode = nullptr;

        this->length--;
    }
}

//For each node in LinkedList, calls printNode()
void LinkedList::printList() {
    Node* currentNode = this->head;
    while (currentNode != nullptr) {
        currentNode->printNode();
        currentNode = currentNode->next;
    }
}

//Randomizes the order of the LinkedList in place
void LinkedList::scrabbleList() {
    
    LinkedList* tempList = new LinkedList();

    while (this->length > 0) {
        
        //Generate Random Number
        srand(time(NULL));
        int randomVal = rand() % (this->length);
        
        //Temporarily store in list
        Node* newNode = new Node(*get(randomVal));
        tempList->addBack(newNode);
        deleteAt(randomVal);
    }

    //Move elements back
    while (tempList->size() > 0) {
        Node* newNode = new Node(*tempList->get(0));
        addBack(newNode);
        tempList->deleteFront();
    }

    delete tempList;
}

//Adds a comma seperated list to linkedList using addBack() function
//@param line - Should be in the format "Letter1-Value1, Letter2-Value2, Letter3-Value...LetterN-ValueN"
void LinkedList::stringToList(std::string line) {
    std::string currentString = "";

    for (unsigned int i = 0 ; i < line.length(); ++i) {
        if (line[i] == ',' || i == line.length() - 1) {
            //If last line, also add to currentString
            if (i == line.length() - 1) {currentString += line[i];}
            
            //To accomodate for 2-digit values, use substring 
            //(i.e: "Z-10" if accessing only 1st index, will assume Z has value 1)
            std::string valueString = currentString.substr(2, -1);
            Tile currentTile;
            currentTile.letter = currentString[0];
            currentTile.value = std::stoi(valueString);
            
            Node* currentNode = new Node(currentTile);
            this->addBack(currentNode);
            currentString = "";
        }
        else if (line[i] != ' ') {
            currentString += line[i];
        }

        // else {
        //     throw std::invalid_argument("Error passed in line for stringToList()");
        // }
    }
}