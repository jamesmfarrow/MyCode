//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by James Farrow on 25/04/2017.
//  Copyright © 2017 James Farrow. All rights reserved.
//
// do not ever use - using namespace at all
// const at end of function declaration can only be used with member fuctions

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <string>


//make syntax unreal friendly
using FString = std::string;
using int32 = int;


//all values initialised to zero
struct FBullCowCount {
    
    int32 Bulls = 0;
    int32 Cows = 0;
    
};

enum class EGuessStatus{
    
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};


class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const ; //good practice to mark getters as const - not to change returned value
    int32 GetCurrenTry() const; //good practice to mark getters as const - not to change returned value
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    
    EGuessStatus CheckGuessValidity(FString) const;
    
    
    void Reset();
    
    FBullCowCount SubmitValidGuess(FString Guess);
    
//Please try and ignore and focus on interface above
private:
    //see constructor for initialisation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const; // helper method in private
    bool IsLowerCase(FString) const; //helper metgod in private
    
};

#endif /* FBullCowGame_hpp */
