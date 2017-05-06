//
//  main.cpp
//  BullCowGame
//
//  Created by James Farrow on 24/04/2017.
//  Copyright © 2017 James Farrow. All rights reserved.
//

/* This is the console executable, that make use of the BullCow class
 This acts as the view in MVC pattern, and is responsible for all
 user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"


//to make syntax unreal friendly
using FText = std::string; //FText used for interaction with user
using int32 = int;



void PrintIntro(); //function prototype
void PlayGame(); //functon prototype
FText GetValidGuess(); //function prototype
bool AskToPlayAgain(); //function prototype
void PrintGameSummary(); //function prototype

//create BullCowGame instance, which we reu-use across game
FBullCowGame BCGame;



//the entry point for our application
int main(int32 argc, const char * argv[]) {
   
    bool bPlayAgain = false;
    
    
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    return 0;
}


// introduce the game
void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    
    return;
}

//plays a single game to completion
void PlayGame()
{
    
    BCGame.Reset();
    
    int32 MaxTries = BCGame.GetMaxTries();
    
    //loop asking for guesses while game is not won
    //and therre are tries remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrenTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n" << std::endl;
        
    } //end while
    
    PrintGameSummary();
    
    return;
}

//loop continually until user gives a valid gues
FText GetValidGuess()
{
    
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do{
        //get a guess from the player
        int32 CurrentTry = BCGame.GetCurrenTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl;
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters" << std::endl;
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter you guess in lowercse" << std::endl;
                break;
            default:
                break;// assume guess is valid
        }//end switch
        
    } while(Status != EGuessStatus::OK); // keep looping until we have no errors
    
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y' || Response[0] == 'Y');
    
}


//summarise game
void PrintGameSummary(){
    
    if(BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!" << std::endl;
    }
    else
    {
        std::cout << "Better luck next time!" << std::endl;
    }
    
    return;
}






