#include "Hangman.h"

string HangmanGame::decryptWord(const string& encrypted, int key) {
    string result = encrypted;
    for (size_t i = 0; i < result.length(); i++) {
        result[i] = result[i] - key;
    }
    return result;
}

void HangmanGame::loadWordFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    vector<string> encryptedWords;
    string word;
    while (file >> word) {
        if (!word.empty()) {
            encryptedWords.push_back(word);
        }
    }
    file.close();

    if (encryptedWords.empty()) {
        throw runtime_error("Words file is empty!");
    }

    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % encryptedWords.size();
    _targetWord = decryptWord(encryptedWords[randomIndex]);
}

void HangmanGame::drawHangman(int mistakes) const {
    cout << "\n+---+\n|   |\n";
    if (mistakes >= 1) cout << " O  |\n"; else cout << "    |\n";
    if (mistakes == 2) cout << " |  |\n";
    else if (mistakes == 3) cout << "/|  |\n";
    else if (mistakes >= 4) cout << "/|\\ |\n";
    else cout << "    |\n";
    if (mistakes == 5) cout << "/   |\n";
    else if (mistakes >= 6) cout << "/ \\ |\n";
    else cout << "    |\n";
    cout << "=========\n\n";
}

bool HangmanGame::isLetterUsed(char c) const {
    for (char letter : _enteredLetters) {
        if (letter == c) return true;
    }
    return false;
}

HangmanGame::HangmanGame(const string& filename, int maxAttempts) {
    _maxAttempts = maxAttempts;
    _usedAttempts = 0;
    _startTime = 0;
    _endTime = 0;

    loadWordFromFile(filename);
    _currentGuessed = string(_targetWord.length(), '_');
}

void HangmanGame::start() {
    _startTime = time(0);
    int mistakes = 0;

    cout << "=======================================" << endl;
    cout << "            HANGMAN GAME               " << endl;
    cout << "=======================================" << endl;
    cout << "Word has " << _targetWord.length() << " letters." << endl;

    while (mistakes < _maxAttempts && _currentGuessed != _targetWord) {
        drawHangman(mistakes);

        cout << "Word: ";
        for (char c : _currentGuessed) {
            cout << c << " ";
        }
        cout << endl;

        cout << "Used letters: ";
        for (char c : _enteredLetters) {
            cout << c << " ";
        }
        cout << endl;

        cout << "Enter a letter: ";
        char input;
        cin >> input;
        input = tolower(input);

        if (isLetterUsed(input)) {
            cout << ">> You already tried this letter! Try another.\n" << endl;
            continue;
        }

        _enteredLetters.push_back(input);
        _usedAttempts++;

        bool found = false;
        for (size_t i = 0; i < _targetWord.length(); i++) {
            if (tolower(_targetWord[i]) == input) {
                _currentGuessed[i] = _targetWord[i];
                found = true;
            }
        }

        if (!found) {
            mistakes++;
            cout << ">> Wrong! Remaining attempts: " << (_maxAttempts - mistakes) << endl;
        }
        else {
            cout << ">> Correct!" << endl;
        }
        cout << "---------------------------------------" << endl;
    }

    _endTime = time(0);

    if (_currentGuessed == _targetWord) {
        cout << "\nYOU WIN! Word guessed: " << _targetWord << endl;
    }
    else {
        drawHangman(mistakes);
        cout << "\nGAME OVER! Word was: " << _targetWord << endl;
    }
}

void HangmanGame::showStats() const {
    double duration = difftime(_endTime, _startTime);

    cout << "\n================ GAME STATS ================" << endl;
    cout << "1. Time spent:      " << duration << " sec." << endl;
    cout << "2. Total attempts:  " << _usedAttempts << endl;
    cout << "3. Target word:     " << _targetWord << endl;
    cout << "4. Player letters:  ";
    for (char c : _enteredLetters) {
        cout << c << " ";
    }
    cout << "\n============================================" << endl;
}

void createDefaultWordsFile(const string& filename) {
    ifstream check(filename);
    if (!check.is_open()) {
        ofstream file(filename);
        if (file.is_open()) {
            vector<string> encryptedWords = {
                "dssoh",     // apple
                "edqdqd",    // banana
                "frpsxwhu",  // computer
                "surjudp",   // program
                "frgh",      // code
                "jdph",      // game
                "krxvh",     // house
                "zdwhu",     // water
                "sdshu",     // paper
                "pxvlf"      // music
            };
            for (const string& w : encryptedWords) {
                file << w << endl;
            }
            file.close();
        }
    }
    else {
        check.close();
    }
}