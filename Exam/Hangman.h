#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>

using namespace std;

// Base game class
class BaseGame {
public:
    virtual void start() = 0;
    virtual void showStats() const = 0;
    virtual ~BaseGame() {}
};

// Main hangman game class
class HangmanGame : public BaseGame {
private:
    string _targetWord;
    string _currentGuessed;
    vector<char> _enteredLetters;
    int _maxAttempts;
    int _usedAttempts;
    time_t _startTime;
    time_t _endTime;

    string decryptWord(const string& encrypted, int key = 3);
    void loadWordFromFile(const string& filename);
    void drawHangman(int mistakes) const;
    bool isLetterUsed(char c) const;

public:
    HangmanGame(const string& filename, int maxAttempts = 6);
    void start() override;
    void showStats() const override;
};

void createDefaultWordsFile(const string& filename);