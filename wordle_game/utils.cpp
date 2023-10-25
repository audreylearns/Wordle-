/*================================================================================================================================
Owner: Audrey Duzon
GitHub: https://github.com/audreylearns
Release Verssion: 1 - 10/25/2023

Hi there!
Thank you for viewing my first project in C language.
This was developed after semester 1 of studies.
Further development was made after semester 2&3.


==================================================================================================================================*/

#include "utils.h"

//returns max number of words found in file
//throws if file empty
unsigned wordCt(const char* filename) {
    if (filename) {
        std::fstream file(filename);
        std::string temp{};
        int ct{ -1 };
        while (file && !file.eof()) {
            std::getline(file, temp);
            ct++;
        }
        return ct;
    }
    else {
        throw "Please include a valid file name";
    }

}

//loads words found from file
//throws if:
//	any words found greater than 5 length
//	any symbols are found
//  returns address of DMA array holding words from file
std::string* loadWord(const char* filename, const unsigned num, std::string& gameTitle) {
    std::string* rtn = new std::string[num];
    bool valid{};
    unsigned ct = 0;
    if (filename) {
        std::fstream file(filename);
        std::string temp{};
        while (!file.eof() && ct < num) {
            std::getline(file, temp);
            if (temp[0] != '#') {
                temp = toLower(temp); 
                validWordle(temp);
                rtn[ct] = temp;
                ct++;
            }
            else {
                temp = temp.substr(1);
                gameTitle = temp;
            }
        }
    }
    else {
        throw "Please include a valid filename";
    }
    return rtn;
}

bool validWordle(const std::string str) {
    bool valid = str.length() == 5;
    if (!valid) {
        throw "Length of words in Wordle must be 5.";
    }
    for (auto i = 0; i < 5; i++) {
        valid = false;
        valid = isalpha(str[i]); //non zero val if ch is alpha
        if (!valid) {
            throw "Digits and symbols are not allowed in Wordle";
        }
    }

    return valid;
}

std::string toLower(std::string str) {
    for (auto i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

unsigned reoccuring(const char ch, const std::string str) {
    unsigned ct{};
    for (auto i = 0; i < str.length(); i++) {
        if (ch == str[i]) {
            ct++;
        }
    }
    return ct;
}