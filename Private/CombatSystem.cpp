// game
#include "../public/CombatSystem.h"

// cpp
#include <iostream>

using namespace std;

void CombatSystem::StartCombat(Player& player, vector<Character*>& enemies) {
    DisplayStatus(player, enemies);

    // affiche un message de debut de combat
    cout << "Combat contre " << enemies.size() << "enemie(s) !" << endl;

    // tant que le joueur a de la vie et qu'il y a des enemi, le combat continue
    while (player.getHealth() > 0 && !enemies.empty()) {
        // choix de l'enemi a combattre
        int targetIndex = 0; // remplacer par target
        if (targetIndex > 1) { // 0 au lieu de 1
            cout << "Choisir un enemi a combattre entre ( 0 et " << enemies.size() - 1 << ")" << endl;
            cin >> targetIndex;
            if (targetIndex < 0 || targetIndex >= enemies.size()) {
                cout << "Index invalide. Cible par défaut : 0" << endl;
                targetIndex = 0;
            }
        }
        // target enemie to performAttack 
        Character* target = enemies[targetIndex]; // Inattention boucle for au lieu de Class et renomer enemi en target
        player.performAttack(target);

        cout << player.getName() << " comat " << target->getName() << " !" << endl; // target . au lieu de ->

        // si target est mort arrete
        if (target->getHealth() <= 0) { // oublie du =
            cout << target->getName() << "est mort !" << endl;
            enemies.erase(enemies.begin() + targetIndex); // oublie
        }

        if (enemies.empty()) break; // ajout

        // etais en dehors de la boucle
        // enemi attack le joueur, boucle
        for (Character* enemy : enemies) { // mauvaise technique, oublie de Class, utilisation de auto
            enemy->performAttack(&player); // oublie de la reference et . au lieu de ->
            cout << enemy->getName() << " attaque " << player.getName() << " !" << endl;
        }

        DisplayStatus(player, enemies); // ajout
    }

    // si joueur est mort stop
    if (player.getHealth() <= 0) { // oublie du egale
        cout << "Vous etes mort !" << endl; 
    } else {
        cout << "Un enemie viens d'etre elimine, on peux continue!" << endl;
    }
}

void CombatSystem::DisplayStatus(const Player& player, const vector<Character*>& enemies) {
    cout << "\n===== ÉTAT DU COMBAT =====" << endl;
    cout << player.getName() << " - PV: " << player.getHealth() << ", Stamina: " << player.getStamina() << ", Dead Eyes: " << player.getDeadEyes() << endl;

    for (size_t i = 0; i < enemies.size(); i++) {
        cout << "[" << i << "] " << enemies[i]->getName() << " - PV: " << enemies[i]->getHealth() << endl;
    }
}
