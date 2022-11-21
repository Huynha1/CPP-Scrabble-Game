#include <iostream>
#include <cctype>
#include "Game.h"

#define EXIT_SUCCESS    0

void printMenu(void);
void printCredits(void);
void newGame();
void loadGame();

/*

Compile: g++ -Wall -Werror -std=c++14 -O -o scrabble scrabble.cpp Tile.cpp Node.cpp LinkedList.cpp TileBag.cpp Player.cpp Board.cpp Game.cpp
Run: ./scrabble
*/

int main() {
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   bool EndGame = false;
   std::string UserInput;

   printMenu();

   try {
      while (EndGame == false) {
         std::cout << "> ";
         if (getline(std::cin, UserInput)) {
            // New Game
            if (UserInput == "1") {
               newGame();
               EndGame = true;
            }
            // Load Game
            else if (UserInput == "2") {
               loadGame();
               EndGame = true;
            }
            // Credits (Show student information)
            else if (UserInput == "3") {
               printCredits();
               printMenu();
            }
            // Quit
            else if (UserInput == "4") {
               EndGame = true;
            }
            // Invalid Input
            else {
               std::cout << "Invalid Input, Please Enter A Number Between 1 And 4" << std::endl;
            }
         }
         else {   //EOF character
            EndGame = true;
         }
      }
   }
   catch (Game::eofException& e) {
      // std::cout << e.what() << std::endl;
      //DO nothing
   }
   std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;
   return EXIT_SUCCESS;
}

// Prints the main menu
void printMenu(void) {  
   std::cout << "Menu" << std::endl;
   std::cout << "---" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit\n" << std::endl;
   std::cout << std::endl;
}

// Starts a new game
void newGame() {
   std::string UserInput = "";
   bool CorrectInput = false;
   std::cout << "Starting a New Game\n" << std::endl;

   bool CheckWords = false;
   std::cout << "Would you like the game to check for word correctness? Input Y (for Yes) or N (for No)" << std::endl;
   while (!CorrectInput) {
      std::cout << "> ";
      if (!getline(std::cin, UserInput)) {throw Game::eofException();}

      if (UserInput == "Y" || UserInput == "y") {
         CheckWords = true;
         CorrectInput = true;
      }
      else if (UserInput == "N" || UserInput == "n") {
         CorrectInput = true;
      }
      else {
         std::cout << "Please input Y (Yes) or N (No)" << std::endl;
      }
   }

   CorrectInput = false;
   std::string player3 = "";
   std::string player4 = "";
   int numberOfPlayers = 0;
   std::cout << "How many players are playing the game? (Please pick a number between 2-4)" << std::endl;
   while (!CorrectInput) {
      std::cout << "> ";
      if (!getline(std::cin, UserInput)) {throw Game::eofException();}

      if (UserInput == "2") {
         CorrectInput = true;
         numberOfPlayers = 2;
      }
      else if (UserInput == "3") {
         CorrectInput = true;
         numberOfPlayers = 3;
      }
      else if (UserInput == "4") {
         CorrectInput = true;
         numberOfPlayers = 4;
      }
      else {
         std::cout << "Please input a number between 2 to 4" << std::endl;
      }
   }

   std::string player1;
   bool isAllUpper = false;
   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   // Loops until the inputed line is all uppercase
   while (isAllUpper == false) {
      isAllUpper = true;
      // Retreives the input
      std::cout << "> ";
      if (!getline(std::cin, player1)) {throw Game::eofException();}

      // Loops through the input charicter by charicter and checks if they are uppercase
      for (unsigned int i = 0 ; i < player1.size() ; ++i) {
         // If the given char is not uppercase
         if (isupper(player1[i]) == false) {
            isAllUpper = false;     
         }
      }
      // Prints error if input contains lower case 
      if (isAllUpper == false){
         std::cout << "please enter a name with uppercase characters only" << std::endl;  
      }

      // Check for length
      if (player1.size() <= 0) {
         std::cout << "please enter atleast 1 character." << std::endl;
         isAllUpper = false;
      }
   }

   std::cout << std::endl;

   std::string player2;
   isAllUpper = false;
   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   // Loops until the inputed line is all uppercase
   while (isAllUpper == false) {
      isAllUpper = true;
      // Retreives the input
      std::cout << "> ";
      if (!getline(std::cin, player2)) {throw Game::eofException();}

      // Loops through the input charicter by charicter and checks if they are uppercase
      for (unsigned int i = 0 ; i < player2.size() ; ++i) {
         // If the given char is not uppercase
         if (isupper(player2[i]) == false) {
            isAllUpper = false;     
         }
      }
      // Prints error if input contains lower case 
      if (isAllUpper == false){
         std::cout << "please enter a name with uppercase characters only" << std::endl;  
      }

      // Check for length
      if (player2.size() <= 0) {
         std::cout << "please enter atleast 1 character." << std::endl;
         isAllUpper = false;
      }
   }

   std::cout << std::endl;

   if (numberOfPlayers == 3 || numberOfPlayers == 4) {
      isAllUpper = false;
      std::cout << "Enter a name for player 3 (uppercase characters only)" << std::endl;
      // Loops until the inputed line is all uppercase
      while (isAllUpper == false) {
         isAllUpper = true;
         // Retreives the input
         std::cout << "> ";
         if (!getline(std::cin, player3)) {throw Game::eofException();}

         // Loops through the input charicter by charicter and checks if they are uppercase
         for (unsigned int i = 0 ; i < player3.size() ; ++i) {
            // If the given char is not uppercase
            if (isupper(player3[i]) == false) {
               isAllUpper = false;     
            }
         }
         // Prints error if input contains lower case 
         if (isAllUpper == false){
            std::cout << "please enter a name with uppercase characters only" << std::endl;  
         }

         // Check for length
         if (player3.size() <= 0) {
            std::cout << "please enter atleast 1 character." << std::endl;
            isAllUpper = false;
         }
      }

      std::cout << std::endl;
   }

   if (numberOfPlayers == 4) {
      isAllUpper = false;
      std::cout << "Enter a name for player 4 (uppercase characters only)" << std::endl;
      // Loops until the inputed line is all uppercase
      while (isAllUpper == false) {
         isAllUpper = true;
         // Retreives the input
         std::cout << "> ";
         if (!getline(std::cin, player4)) {throw Game::eofException();}

         // Loops through the input charicter by charicter and checks if they are uppercase
         for (unsigned int i = 0 ; i < player4.size() ; ++i) {
            // If the given char is not uppercase
            if (isupper(player4[i]) == false) {
               isAllUpper = false;     
            }
         }
         // Prints error if input contains lower case 
         if (isAllUpper == false){
            std::cout << "please enter a name with uppercase characters only" << std::endl;  
         }

         // Check for length
         if (player4.size() <= 0) {
            std::cout << "please enter atleast 1 character." << std::endl;
            isAllUpper = false;
         }
      }

      std::cout << std::endl;
   }

   std::cout << "Let's Play!" << std::endl;
   if (numberOfPlayers == 2) {
      Game* game = new Game(player1, player2, CheckWords, numberOfPlayers);
      game->playGame();
      delete game;
   }
   else if (numberOfPlayers == 3) {
      Game* game = new Game(player1, player2, player3, CheckWords, numberOfPlayers);
      game->playGame();
      delete game;
   }
   else if (numberOfPlayers == 4) {
      Game* game = new Game(player1, player2, player3, player4, CheckWords, numberOfPlayers);
      game->playGame();
      delete game;
   }

   // game->playGame();
   // Cleanup
   // delete game;
}

// Loads the game using a users file
void loadGame() {
   std::string fileName;
   std::cout << "Enter the filename from which load a game: " << std::endl;
   std::cout << "> ";
   // Gets the file name from input (relative path)
   if (!getline(std::cin, fileName)) {throw Game::eofException();}
   // Creates a game object on the heap using file name as input
   Game* game = new Game(fileName);
   game->playGame();
   // Cleanup
   delete game;
}

// Simply prints the credits
void printCredits(void) {
   std::string names[4] = {"Anton Angelo Carasig", "Henry Huynh", "Patrick Rivera", "Oliver Guzowski"};
   std::string studentID[4] = {"s3906344", "s3905838", "s3721043", "s3897734"};
   std::string email[4] = {"s3906344@student.rmit.edu.au", "s3905838@student.rmit.edu.au", "s3721043@student.rmit.edu.au", "s3897734@student.rmit.edu.au"};

   std::cout << "----------------------------------" << std::endl;

   for (int i = 0 ; i < 4 ; ++i) {
      std::cout << "Name: " << names[i] << std::endl;
      std::cout << "Student ID: " << studentID[i] << std::endl;
      std::cout << "Email: " << email[i] << std::endl;
      if (i < 3) {
         std::cout << "\n";
      }
   }
   std::cout << "----------------------------------" << std::endl;
}