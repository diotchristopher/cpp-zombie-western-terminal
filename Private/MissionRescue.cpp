// game
#include "../public/MissionRescue.h"

// cpp
#include <iostream>

using namespace std;

MissionRescue::MissionRescue(Player* player, Location* targetLocation, MissionType missionType, string title, bool isActive, bool isCompleted, int waveCount, int currentWave, int waveRemaining, int zombiesPerWave, bool isRescued) : Mission(player, targetLocation, missionType, title, isActive, isCompleted),
waveCount(waveCount), currentWave(currentWave), waveRemaining(waveRemaining),
zombiesPerWave(zombiesPerWave), isRescued(isRescued) {}


int MissionRescue::getWaveCount() const { return waveCount;} // Oublie de MissionRescue::
int MissionRescue::getCurrentWave() const { return currentWave;}
int MissionRescue::getWaveRemaining() const { return waveRemaining;}
int MissionRescue::getZombiesPerWave() const { return zombiesPerWave;}
bool MissionRescue::getIsRescued() const { return isRescued;}


void MissionRescue::start() { // mots cles inutile ici override
    isActive = true;
    currentWave = 1;
    // enlever inutile ici survivorsToRescue = 2;
    // enlever inutile ici zombiesPerWave = 8;
    localSurvivors = targetLocation->getSurvivors(); // erreur : C++ no operator matches these operands parce que fonction getSurvivor pas vector
    // zombiesRemaining = zombiesPerWave;

    spawnZombies(); // localZombies = spawnZombies inutile ici, la fonction gere deja ca

    isRescued = false;

    cout << "Un camps est attaquer, il y a " << localSurvivors.size() << " survivants." << endl;
}

void MissionRescue::update() {
    if (!isActive || isCompleted) { // remplacer les == false, == true par !variable, variable 
        return;
    }

    // inutile mission echoue maintenant si plus de survivant
    /* if (survivorsToRescue < currentNumberSurvivors) {
        survivorsToRescue = ;
    }
    */
    localSurvivors.erase(
        remove_if(localSurvivors.begin(), localSurvivors.end(), [](Npc* c) { return c->getHealth() <= 0; })); // oublie de localZombies sur le .begin et le .end 
  

    // maj quand survivant mort
    if (localSurvivors.empty())
       // targetLocation->getNumberOfSurvivors() <= 0 // remplacer : currentNumberSurvivors < 0, mauvais signe et facon de faire
    { // mauvaise, logique quand les survivants sont mort, fin de la partie
        cout << "Tous les survivants ont été tués. Mission échouée.\n";
        isActive = false;
        isCompleted = true;
        isRescued = false;
        return;
    }
    // maj quand tous les zombie son mort vague suivante, quand tous les vague termine reussie

    localZombies.erase(
        remove_if(localZombies.begin(), localZombies.end(), [](NpcZombie* z) { return z->getHealth() <= 0; })); // oublie de localZombies sur le .begin et le .end 


    // CombatSystem* combatSystem;
    // combatSystem->StartCombat(localSurvivors, localZombies);


    if (localZombies.empty()) { // zombiesRemaining <= 0 // mauvais signe == au lieu de 
        currentWave++; // remplace : currentWave += 1;
        waveRemaining--; // remplace : currentWave -= 1;
    }

    if (checkCompletion()) {
        isCompleted = true; // correctif final : == au lieu de =
        isActive = false;
        isRescued = true; // ajoute de isRescued
        // enlever le return isCompleted == true && isActive == false;
    }
    else {
        spawnZombies();
    }
}

bool MissionRescue::checkCompletion() {
    return currentWave > waveRemaining; // mauvais signe <= au lieu de >
}

void MissionRescue::spawnZombies() {
    localZombies.clear();

    int totalZombie = zombiesPerWave + currentWave * 2;

    for (int i = 0; i < totalZombie; i++) {


        int randomNumber = rand() % 100; // renomme aleatoire en randomNumber

        string name = "Zombie";
        int health = 10; // Oublie de declarer avant la boucle les variables pour les utiliser en dehors
        int speed = 10;
        bool gender = true;
        int strength = 10;
        Role role = Role::CITIZEN;
        ZombieType type = ZombieType::STANDARD;

        if (randomNumber < 50) { // 50%
            name = "Un zombie normal";
            health = 30;
            speed = 2;
            gender = true;
            strength = 10;
            role = Role::CITIZEN;
            type = ZombieType::STANDARD;
        }
        else if (randomNumber < 75) { // 25%
            name = "Un zombie rapide";
            health = 20;
            speed = 5;
            gender = true;
            strength = 7;
            role = Role::FARMER;
            type = ZombieType::RUNNER;
        }
        else if (randomNumber < 90) { // 15%
            name = "Un zombie cracheur";
            health = 25;
            speed = 3;
            gender = true;
            strength = 5;
            role = Role::PROSTITUTE;
            type = ZombieType::SPITTER;
        }
        else { // 10%
            name = "Un zombie brutale";
            health = 40;
            speed = 1;
            gender = true;
            strength = 20;
            role = Role::BANDIT;
            type = ZombieType::BRUTAL;
        }

        localZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}