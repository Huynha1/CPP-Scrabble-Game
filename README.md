# apt-assign2

See `Class.md` for a rundown on how each file works

***

## Changelog:
    - Created Tile, Node, LinkedList files and testNodeList file which tests implementation
    - Tile and Node class functions implemented
    - LinkedList functions implemented (unchecked for memory leaks)
    - TileBag adapted from testNodeList
    - TileBag shuffle function added
    - scrabble and scrabbleGame classes files created
    - scrabbleGame constructor created (creates Player objects)
    - scrabble menu, credits and newGame (partial) created
    - Added board, player and game files
    - Added unit testing various .cpp files in Test folder
    - Now working on scrabble.cpp -> New game read command and validate input length finished
    - Game save function added
    - Game load function also added
    - expanded board size to 15
    - reformatted board print functions to loops
    - added game bingo function
    - added game checkgameconditions to check if a player has won
    - Code now saves current player's turn at the end of the file
    - Reading file now loads from the given player's turn

***

## How to compile and run code
    - For testing purposes in the Player.cpp file under the replace tile function on line 102, the random time seed is set to 69,to run it normally change the parameter within the `srand()` function to `time(NULL)`.

    - To compile the code, enter the following command into the terminal: `g++ -Wall -Werror -std=c++14 -O -o scrabble scrabble.cpp Tile.cpp Node.cpp LinkedList.cpp TileBag.cpp Player.cpp Board.cpp Game.cpp`.

    - To run the code, enter the following command into the terminal: `./scrabble`

## How to run the Test Cases (!! Test Cases only work for the original milestone 2 code)
    - end_mid_game
        - In this test the game terminates midgame because the code reaches the end of file.
        - To run the code, input the following command into the terminal: `./scrabble < TestCases/end_mid_game.input > TestCases/end_mid_game.gameout`
        - To compare the outputs, input the following command into the terminal: `diff -w TestCases/end_mid_game.output TestCases/end_mid_game.gameout`

    - save_test
        - In this test, the game save is being tested.
        - To run the code, input the following command into the terminal: `./scrabble < TestCases/save_test.input > TestCases/save_test.gameout`
        - To compare the outputs of the save file, input the following command into the terminal: `diff -w TestCases/save_test.expsave TestCases/save_test.save`

    - win_from_empty_hand
        - In this test, the game ends from a player placing all tiles from their hand and the tile bag is empty.
        - To run the code, input the following command into the terminal: `./scrabble < TestCases/win_from_empty_hand.input > TestCases/win_from_empty_hand.gameout`
        - To compare the outputs, input the following command into the terminal: `diff -w TestCases/win_from_empty_hand.output TestCases/win_from_empty_hand.gameout`

    - win_from_pass
        - In this test, the game ends from a player passing twice and the tile bag is empty.
        - To run the code, input the following command into the terminal: `./scrabble < TestCases/win_from_pass.input > TestCases/win_from_pass.gameout`
        - To compare the outputs, input the following command into the terminal: `diff -w TestCases/win_from_pass.output TestCases/win_from_pass.gameout`