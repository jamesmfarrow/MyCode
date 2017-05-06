//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by James Farrow on 25/04/2017.
//  Copyright © 2017 James Farrow. All rights reserved.
//


#include "FBullCowGame.hpp"
#include <map>

//syntax for unreal friendly
#define TMap std::map


using int32 = int;

//default constructor
FBullCowGame::FBullCowGame(){ Reset(); }

//getter methods
int32 FBullCowGame::GetCurrenTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength()const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {4,6}, {5,7}, {6,8} };
    
    return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
    
    const FString HIDDEN_WORD = "planet"; //this MUST be an isogram
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    
    
    return;
    
    
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if(!IsIsogram(Guess))//if guess isnt an isogram
    {
        if(Guess.length() != GetHiddenWordLength())
        {
            return EGuessStatus::Wrong_Length;
        }
        else
        {
            return EGuessStatus::Not_Isogram;
        }
    }
    if(!IsLowerCase(Guess)) //if the guess isnt all lowercase
    {
        if(Guess.length() != GetHiddenWordLength())
        {
            return EGuessStatus::Wrong_Length;
        }
        else
        {
            return EGuessStatus::Not_Lowercase;// TODO write function
        }
    }
    if(Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length; //if guess length is wrong
    }

    return EGuessStatus::OK;
   
}

//receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
    
    //loop thorough all letters in hidden word
    for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){ //MHWChar My Hidden Word Char
        //compare letters against guess
        for(int GChar = 0; GChar < WordLength; GChar++){ // GChar Guess Char
            //if letter matches and in same place
            if(MyHiddenWord[MHWChar] == Guess[GChar]){
                if(MHWChar == GChar){
                    BullCowCount.Bulls++; //increment Bulls
                } //end inner if
                else{
                    BullCowCount.Cows++; //increment Cows
                }// end else
            }// end outer if
        } // end inner for
    }//end outer for
    
    if(BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}//end function


bool FBullCowGame::IsIsogram(FString Word) const
{
    
    
    //treat 0 and 1 letter words as isograms
    if(Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    for(auto Letter : Word){ // for all Letters of Word
        Letter = tolower(Letter); //handle mixed case
        LetterSeen[Word[Letter]] = true;
        if(LetterSeen[Letter]){
            return false;
        }
        else {
            LetterSeen[Letter] = true;
        }
    }
    
    return true; // for exampl in cases where /0 is entered
}



bool FBullCowGame::IsLowerCase(FString Word) const {
    
    for(auto Letter : Word)
    { // for all Letters of Word
        //if not lowercase letter
        if(!islower(Letter))
        {
            return false;
        }
    }
    
    
    return true; // for exampl in cases where /0 is entered
}
