/*================================================================================================================================
Owner: Audrey Duzon
GitHub: https://github.com/audreylearns
Release Verssion: 1 - 10/25/2023

Hi there!
Thank you for viewing my first project in C language.
This was developed after semester 1 of studies.
Further development was made after semester 2&3.


==================================================================================================================================*/

#include <iomanip>
#include <stdlib.h>

#include "wordle.h"

//entry point to game
void wordle(char ** argv) {

    player p1{};
    bool play{ true }, win{}, ingameFlag{}, newWord{};
    unsigned numWords{}, round{};
    std::string* wordList{};
    std::string entry{}, answer{}, topic{};
    char confirm{};
    try {
        numWords = wordCt(argv[1]);
        wordList = loadWord(argv[1], numWords, topic);
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        play = false;
    }
    while (play) {
        win = false;
        std::cout << ">>>  " << topic << std::endl;
        std::cout << "*-------------------------*" << std::endl;
        std::cout << "ROUND: " << round + 1 << std::endl;
        std::cout << "*=========================*" << std::endl;
        std::cout << "|   LETS PLAY WORDLE!!!   |" << std::endl;
        std::cout << "|-------------------------|" << std::endl;
        std::cout << "|                         |" << std::endl;
        std::cout << "|";
        std::cout << std::setw(14) << "xxxxx";
        std::cout << std::setw(12) << "|" << std::endl;
        std::cout << "*=========================*" << std::endl;
        answer = randomWord(wordList, numWords);
        newWord = existing(answer, p1.word_search);
        while (newWord) {
            answer = randomWord(wordList, numWords);
        }
        newWord = false;
        p1.word_search.push_back(answer);
        
        while (p1.lives > 0 && win != true) {
            entry = guess(/*std::cin*/);

            std::cout << std::setw(15) << result(entry, p1.word_search[round], win) << std::endl; //change to iterate later
            win ? p1.pts++ : p1.lives--;
        }
        if (win) {
            std::cout << "*-------------------------*" << std::endl;
            std::cout << "You won!" << std::endl;
            p1.words_guessed.push_back(entry);
            std::cout << "Lives: " << p1.lives << "     " << "Score: " << p1.pts << std::endl;
            std::cout << "Play again? ";
        }
        else {
            std::cout << "*-------------------------*" << std::endl;
            std::cout << "| You ran out of lives :( |" << std::endl;
            std::cout << "*-------------------------*" << std::endl;
            std::cout << "|     Word: " << answer << "         |" << std::endl;
            gamestats(p1);
        }

        do {
            try {
                ingameFlag = false;
                std::cin.ignore();
                std::cin.get(confirm);
                play = playAgain(confirm);
            }
            catch (const char* msg) {
                std::cout << msg << std::endl;
                ingameFlag = true;

            }
        } while (ingameFlag);
        std::cout << std::endl;
        if (play == true && p1.lives !=0) {
            round++;
        }
        else {
            gamestats(p1);
        }
        std::cin.ignore(1000, '\n');
    }

    delete[] wordList;
}


std::string randomWord(const std::string* list, const int num) {
    //only between 0 and num
    srand(time(NULL));
    int val = rand() % (num + 1);
    return list[val];
}

std::string guess() {
    bool valid{};
    std::cout << std::setw(10) << "->";
    std::string guess{};
    std::cin >> guess;
    guess = toLower(guess);
    try {
        valid = validWordle(guess);
    }
    catch(const char* msg){
        std::cout << "\n" << msg << std::endl;
    }
    return valid ? guess : "Invalid Guess";
}

//v3
std::string result(const std::string guess, const std::string word, bool& win) {
    std::unordered_map<char, int>wch;
    std::string rtn{"xxxxx"};
    if (guess == word) {
        win = true;
        return guess;
    }
    else {
        for (auto i = 0; i < word.length(); i++) {
            if (word.find(guess[i]) != std::string::npos) { 
                wch.try_emplace(guess[i], reoccuring(guess[i], word)); 
                if (wch[guess[i]] > 0) {
                    parseExactMatch(guess[i], rtn, guess, word, wch[guess[i]]); 
                    parseMatch(guess[i], rtn, guess, word, wch[guess[i]]);
                }
            }
        }
    }
    return rtn;
}



bool playAgain(char ch) {
    ch = tolower(ch);
    if (!isalpha(ch) || (ch != 'y' && ch != 'n')) { //0 
        throw "Invalid Input. Must be Y or N only.";
    }

    return ch == 'y' ? true : false;
}

bool existing(const std::string str, const std::vector<std::string> arr) {
    bool found{};
    for (auto i = 0; i < arr.size(); i++) {
        if (str == arr[i]) {
            found = true;
        }
    }
    return found;
}

void gamestats(const player p) {
    std::cout << "*-------------------------*" << std::endl;
    std::cout << "| History:                |" << std::endl;
    std::cout << "*=========================*" << std::endl;
    std::cout << "  Total Score: " << p.pts << std::endl;
    std::cout << "  Lives: " << p.lives << std::endl;
    std::cout << "  Words matched: " << std::endl;

    for (auto i = 0; i < p.words_guessed.size(); i++) {
        std::cout << i+1 << ". " << p.words_guessed[i] << std::endl;
    }
    std::cout << "*-------------------------*" << std::endl;
    std::cout << "|   Thanks for playing!   |" << std::endl;
    std::cout << "*-------------------------*" << std::endl;


}

void parseExactMatch(const char ch, std::string& matched, const std::string guess, const std::string correct, int& ct ) {
    if (ct > 0) {
        for (auto i = 0; i < guess.length(); i++) {
            if (ch == guess[i] && correct[i] == ch) {
                matched[i] = ch;
                ct--;
            }
        }
    }
}

void parseMatch(const char ch, std::string& str, const std::string guess,const std::string correct, int& ct) {
    
    if (ct > 0) {
        for (auto i = 0; i < str.length(); i++) {
            if (str[i] == 'x'&& (correct.find(ch) != std::string::npos && guess.find(ch) == i)) {
                str[i] = '+';
                ct--;
            }
        }
    }

}