// game
#include "../public/CombatSystem.h"
#include "../public/IFighter.h"

// cpp
#include <iostream>
#include <algorithm> // oublie pour remove

using namespace std;

// teamA = allie, teamB = ennemi
void CombatSystem::StartCombat(vector<IFighter*>& teamA, std::vector<IFighter*>& teamB) { // remplacement de Player& player, vector<Character*>& enemies
    // enlever
    // DisplayStatus(teamA, teamB); // remplacement de player, enemies

    while (!teamA.empty() && !teamB.empty()) { // Hesitation
        int zombieAttacks = 0;
        const int MAX_ZOMBIE_ATTACKS = 3;
        for (auto* enemy : teamB) { // const &auto au lieu de + renommer fighter en enemy
            if (!enemy->isAlive()) { continue; }
            
            if (zombieAttacks >= MAX_ZOMBIE_ATTACKS) { break; } // oublie

            enemy->performAttack(teamA.front()); // -> au lieu de ., pas pointeur ici
            
            if (!teamA.front()->isAlive()) {
                if (teamA.front()->isPlayerControlled()) {
                    cout << "Vous etes mort !" << endl;
                    return;
                }
                else {
                    cout << teamA.front()->getName() << " est mort !" << endl;
                    teamA.erase(teamA.begin()); // mauvais orthographe a erase / etais en dehors de la boucle
                }
            }
            zombieAttacks++;
        }

        // ajout de ca en etape 2
        for (auto* ally : teamA) { // renommer fighter en ally
            if (!ally->isAlive()) { continue; }
            if (teamA.empty()) { break; }
            //  reflechi a faire ca ici : if (!teamA.front()->isPlayerControlled()) {

            IFighter* target = nullptr; // mauvaise orthographe traget
            
            if (ally->isPlayerControlled()) { // remplacmenet teamA.front(), teste que le premier
                cout << "Choisir un enemi a combattre." << endl;
                
                for (size_t i = 0; i < teamB.size(); i++) { // oublie de size_t, ajout de int pour rien
                    cout << " (" << i << ") " << teamB[i]->getName() << " avec " << teamB[i]->getHealth() << " points de santé !" << endl;
                }

                int choice = -1; // oublie de = 0 et remplacement de 0 par -1 pour pas mettre valeur existante par default
                cin >> choice;

                if (choice >= 0 && choice < (int)teamB.size()) { // oublie de (int) parce que teamB retourne size_t et erreur <= au lieu de <
                    target = teamB[choice]; // mauvaise orthographe traget
                } else { // oublie choix invalide
                    cout << "Index invalide. Cible par défaut : 0" << endl;
                    target = teamB.front(); // mauvaise orthographe traget
                }  
            } else {
                target = teamB.front(); // erreur ici a cause de bon orthographe pas ici ailleurs
            }

            bool headshot = false;
            if (ally->isPlayerControlled()) {
                headshot = (rand() % 100 < 30);
            }
            else {
                headshot = (rand() % 100 < 15);
            }

            if (headshot) {
                cout << ally->getName() << " réussit un HEADSHOT sur "
                    << target->getName() << " !" << endl;
                target->takeDamage(ally->getStrength() * 2);
            }
            else {
                ally->performAttack(target);
            }

            ally->performAttack(target); // mauvaise orthographe traget
            
            if (!target->isAlive()) { // erreur ajoute de !teamB.front()->isAlive()
                cout << target->getName() << " est mort !" << endl;

                // ajout de is lootable
                if (target->isLootable()) {
                    if (rand() % 100 < 40) {
                        if (ally->isPlayerControlled()) {
                            Player& player = static_cast<Player&>(*ally); // on transforme IFighter* en Player& parce que ally est en réalité un Player
                            LootSystem lootSystem;
                            lootSystem.HandleLoot(player); // -> au lieu de .
                        }
                    }
                }
                // teamB.erase(teamB.begin()); // suppression mauvais vector teamA
                teamB.erase(remove(teamB.begin(), teamB.end(), target), teamB.end()); // erreur 
            }
        }
    }
}

/*´// enlever pour le moment
void CombatSystem::DisplayStatus(const Player& player, const vector<Character*>& enemies) { // remplacement de const Player& player, const vector<Character*>& enemies
    cout << "\n===== ÉTAT DU COMBAT =====" << endl;
    cout << player.getName() << " - PV: " << player.getHealth() << ", Stamina: " << player.getStamina() << ", Dead Eyes: " << player.getDeadEyes() << endl;

    for (size_t i = 0; i < enemies.size(); i++) {
        cout << "[" << i << "] " << enemies[i]->getName() << " - PV: " << enemies[i]->getHealth() << endl;
    }
}
 */
