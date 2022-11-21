# **This file is only used to explain how each class functions.**

## Tile.cpp
- Implicit class - has no constructor and likewise, no destructor
- Only class used in this project that is an implicit class
- Only has two variables, (char) `letter` and (int) `value`
Example Tile object:
```
Tile tile1;
tile1.letter = 'A';
tile1.value = 'B';
```

This is realistically also the only code example I will bother showing here, the rest you can just look at the code or the Test folder and peek at the testFiles (although some aren't maintained (see testBoard.cpp))

## Node.cpp
- Explicit class - has constructor and deconstructor
- private variables `tile` and `next`
- @param `next` stores the current tile object
    - Can access the node's tile by doing node->tile.letter / node->tile.value
- @param `next` is a pointer to the "next" node (default nullptr, changes when added to a LinkedList)
- Copy constructor only takes the other's `tile` value, `next` is nullptr

## LinkedList.cpp
- Data structure that stores an ordered list of nodes
- Singly-linked list, explained in lectures both this and last year already so I won't bother re-explaining
- Majority of the functions are add and delete functions depending on position:
    - `addAt()` will add a node at a given index in the LinkedList
    - `deleteFront()` will delete the node at the front of the LinkedList
    - etc.
- Has a `scrabbleList()` function which is basically only exclusive to this project:
    - create a new linkedList
    - get a random value ranging from [0...n-1] where `n-1` is the length of the LinkedList
    - Move the node at that position to the new LinkedList
    - Continue until original LinkedList is empty
    - When empty, move everything back from the new to the original list and delete the new LinkedList
    - Should result in an in-place "scrabble" that just randomizes the list

## TileBag.cpp
- Used to store the scrabble tiles that a `Player` will take from to play the game
- Constructor reads the `ScrabbleTiles.txt` file into nodes, stores them into a LinkedList and then randomizes it
- Other than the constructor, the rest of the class functions are fairly straight-forward, just read the comment for it

## Player.cpp
- Player class takes in @param `name` which sets the player's name (restricted to all-caps due to the game)
- Constructor uses @param `name` to generate player's name, as well as set's the initial score to 0 and an empty `hand`
- When a game starts, Player objects are created and call `fillHand()`, which fills up player's hand from @param `TileBag`, taking the front-most tile from the TileBag until they possess a `hand` of length 7
- As such, whenever a player places/replaces a tile the respective function is called which interacts with `TileBag` and `Board`

## Board.cpp
- The gamespace that the game is played on
- Grid stored as a 2D vector of size 15x15
- Each grid position is denoted by a `<row><column>` string, denoting the row to place and it's column
- `Row` reflects a predefined `Map`, where each key-value pair for each letter (A-O) refers to an integer number
    - The integer number is used to represent the row that a `Tile` may be placed on
- `Column` is more simple, simply indicating which column index the tile should be placed at
- There are two main `PlaceTile` commands (the primary purpose of the Board class anyway):
    - One that utilizes the `Player` class, where the tile that is placed is removed from the Player's `hand`
    - Another that is independent of the `Player` class, used primarily for loading a game (As loading a game does not know which `Player` placed which `Tile`, only their current `score`)

## Game and scrabble
- The `scrabble` file is primarily used as a user-menu, it is effectively the "main" file
- As such, there are no constructors/deconstructors for `scrabble`
- Depending on where a user navigates, it can start a new game or load a game from a savefile (.txt)
- (Also can print group members or quit but thats as important)

- The `Game.cpp` has a basic and overloadded constructor:
    - If no parameters are passed in, it is basically a "new game":
        - `Player` initialized has 0 score, `Board` has no tiles placed, etc.
    - If @param `fileName`(string) is passed in, it will try and load from a save file from the passed in parameter
    - As such, the various class objects will be initialized with values representative of the whatever the filename contains
    - (Likewise, there is an assumption that there is 0 tampering performed on a save file for there to be proper load states)
- Once a `Game` is initialized, it enters `playGame()`, which loops player turns until a quit command or the boolean `endGame` is set to true
- As such, player's take turns by initially printing out current score for the player and then awaiting their input (`printScore(Player)`, `getTurn(Player)`)
- The `getTurn()` function is encapsulated in a try-catch block, which will catch **ALL** exceptions that are of type `invalid_argument`
    - This will thus allow repetition of a Player's turn until proper inputs are inputted
    - -con, only invalid_argument errors that have been throw are managed
    - Catch errors allow dotpoint 1 to work
    - The only exception not caught in the `parseInput()` function is when a `std::exception()` error occurs, however, this only occurs when the user enters "quit" as their input
    - Although not handled by the `getTurn()` catch, it is handled by the `playGame()` catch, which will immediately break the turn cycle and end the game
- The `parseInput()` function basically handles whatever was inputted by the user
    - Throws an error when something invalid occurs (look at comments in code and interpret yourself)
- A special case of `parseInput()` is when there's a place command:
    - a place command requires a user to continue placing tile's until the input "place done" is performed
    - As such, the program processes the command and then recalls the `getTurn()` command
    - However one thing there is to note is that when a placeCommand is initially entered, a boolean value is set to true
    - Thus, whenever anything other than a place command is entered, an `invalid_argument()` error will be thrown
    - Likewise this can only be resolved by entering the "place done" input

Overall this is just a general summary of how all classes work. There is still work to be done so modifications to this file be changed when necessary.