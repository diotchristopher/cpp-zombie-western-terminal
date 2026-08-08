// game
#include "../public/Game.h"

#include <iostream>

using namespace std;

void Game::run() { // oublie Game::
    srand(static_cast<unsigned>(time(nullptr))); // Pour les zombies aléatoires

	cout << "Bienvenue dans WestWorld";
	cout << "Dans quelle direction allais";
	while (true) {
        cout << "\n-- Menu principal --\n";
        cout << "1. Explorer\n";
        cout << "2. Fouiller la zone\n";
        cout << "3. Quêtes\n";
        cout << "4. Quitter\n";
        cout << "Choix : ";

        int choice;
        cin >> choice;

        handlePlayerChoice(choice);
	}
}
