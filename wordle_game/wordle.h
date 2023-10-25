/*================================================================================================================================
Owner: Audrey Duzon
GitHub: https://github.com/audreylearns
Release Verssion: 1 - 10/25/2023

Hi there!
Thank you for viewing my first project in C language.
This was developed after semester 1 of studies.
Further development was made after semester 2&3.


==================================================================================================================================*/

#ifndef WORLDE_H
#define WORLDE_H

#include <unordered_map>
#include <vector>
#include "utils.h"

struct player {
	unsigned lives = 6;
	unsigned pts{};
	std::vector<std::string> words_guessed;
	std::vector<std::string> word_search;

};



//entry point to game, param1 is filename #1 from command line argument
void wordle(char **);

//returns random word from list
std::string randomWord(const std::string*, const int);

//returns a valid wordle guess
std::string guess();

//if arg 1 no match rtn x,
//if arg 1 match but wrong location +, 
//if arg 1 matches loc + pos rtn ch
std::string result(const std::string,  const std::string,bool&);

//rtn true if 'y'
bool playAgain(char);

//rtn true if word exist in arg 2
bool existing(const std::string, const std::vector<std::string> arr);

//displays stats of player: lives, score, correct guesses
void gamestats(const player);

//param 1 = char to match
//param 2 = pass by reference, modified string with the exact ch match
//param 3 = user guessed string
//param 4 = correct string
//param 5 = count of ch occurences in correct string, decremented at every exact match
//returns a string via param 2 of exact ch matches from guess word and correct word
void parseExactMatch(const char ch, std::string& matched, const std::string guess, const std::string correct, int& ct);

//param 1 = char to match
//param 2 = pass by reference, modified string with the exact ch match
//param 3 = user guessed string
//param 4 = correct string
//param 5 = count of ch occurences in correct string, decremented at every exact match
//returns a string via param 2 of exact ch matches from guess word and correct word
void parseMatch(const char ch, std::string& , const std::string guess, const std::string correct, int& ct);
#endif // !WORLDE_H
