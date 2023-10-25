/*================================================================================================================================
Owner: Audrey Duzon
GitHub: https://github.com/audreylearns
Release Verssion: 1 - 10/25/2023

Hi there!
Thank you for viewing my first project in C language.
This was developed after semester 1 of studies.
Further development was made after semester 2&3.


==================================================================================================================================*/

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <iostream>


//returns max number of words found in file
//throws if file empty
unsigned wordCt(const char*);

//loads words found from file
//throws if:
//	any words found greater than 5 length
//	any symbols are found
std::string* loadWord(const char*, const unsigned, std::string&);

//returns true if str contains only alphabet(a-z)characters
//and length of string == 5
bool validWordle(const std::string);

//returns string in lower case
std::string toLower(std::string);

//rtns amt of reoccuring ch in string
unsigned reoccuring(const char, const std::string);
#endif // !UTILS_H
