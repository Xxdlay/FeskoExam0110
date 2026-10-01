#include <conio.h>
#include "Hangman.h"

int main() {
    try {
        createDefaultWordsFile("words.txt");

        BaseGame* game = new HangmanGame("words.txt");

        game->start();
        game->showStats();

        delete game;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nPress any key to exit...";
    _getch();
    return 0;
}