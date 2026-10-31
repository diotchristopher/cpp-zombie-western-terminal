// game
#include "../public/MissionCemetery.h"
#include "../public/IFighter.h"

// cpp
#include <iostream>
#include <algorithm>

using namespace std;

MissionCemetery::MissionCemetery(Player* player, Location* targetLocation, const string& title)
    : Mission(player, targetLocation, MissionType::CEMETERY, title, false, false),
    totalCoffins(4 + rand() % 2), burnedCoffins(0), finalWaveSpawned(false), isPurified(false) {
}

int MissionCemetery::getTotalCoffins() const { return totalCoffins; }
int MissionCemetery::getBurnedCoffins() const { return burnedCoffins; }
bool MissionCemetery::getIsPurified() const { return isPurified; }

void MissionCemetery::start() {
    isActive = true;
    cout << ">> [" << getTitle() << "] Tu entres dans le " << getTargetLocation()->getName() << endl;
    cout << "Objectif : Brûler " << totalCoffins << " cercueils et survivre aux vagues de zombies." << endl;

    burnedCoffins = burnedCoffins + 1;
    spawnZombiesPerCoffins(burnedCoffins); // oublie de faire * 1 commencais a 0, logique differente
}

void MissionCemetery::update() {
    if (!isActive || isCompleted || !player) { // erreur ajoute de || !player
        return; 
    }
    
    // ajout de l'equipe A dans IFighter : Joueur
    vector<IFighter*> teamA;

    if (player->getHealth() > 0) { // suppr player && apres ajoute || !player dans update
        teamA.push_back(player);
    }

    // ajout de l'equipe B dans IFighter : Zombie
    vector<IFighter*> teamB;

    for (NpcZombie* zombie : localZombies) {
        if (zombie && zombie->getHealth() > 0) {
            teamB.push_back(zombie);
        }
    }

    // maj quand joueur mort
    if (teamA.empty())
    {
        cout << "Tu es mort. Mission échouée.\n";
        isActive = false;
        isCompleted = true;
        isPurified = false;
        return;
    }

    // maj quand tous les zombie son mort vague suivante, quand tous les vague termine reussie
    if (teamB.empty()) {
        if (burnedCoffins < totalCoffins) {
            burnedCoffins++;
            player->heal(20); // ajout = augemente le taux de survie
            cout << "+20 points de santé" << endl;
            spawnZombiesPerCoffins(burnedCoffins);
        }
    }
    
    // on elimine les zombie restant a la fin de la derniere vagues
    if (burnedCoffins == totalCoffins && !finalWaveSpawned) {
        if (teamB.empty()) {
            finalWaveSpawned = true;
        }
    }

    // on combat si il reste des membres dans teamA et dans teamB
    if (!teamA.empty() && !teamB.empty()) {
        CombatSystem combat;
        combat.StartCombat(teamA, teamB);
    }

    // nettoyage des morts
    cleanupDead();

    if (checkCompletion()) {
        cout << "Le cimetière a été purifié !" << endl;
        giveReward(*player); // ajouter pour donner recompence
        if (getTargetLocation()) {
            getTargetLocation()->setInvasionLevel(InvasionLevel::SAFE);
        }
        isCompleted = true;
        isActive = false;
        isPurified = true;
    }
}

bool MissionCemetery::checkCompletion() {
    return burnedCoffins == totalCoffins && finalWaveSpawned && localZombies.empty() && player->getHealth() > 0;
}

void MissionCemetery::giveReward(Player& player) {
    player.addAmmo(6);
    player.addReputation(200);
    cout << "Tu as gagné 6 munitions pour ton revolver" << endl; // suppr " << player.getAmmo() << " afficher le total au lieu du nombre
    cout <<  "+ Gain d'Honneur" << endl;
}

void MissionCemetery::spawnZombiesPerCoffins(int burnedCoffins) {
    localZombies.clear();

    int zombiesPerWave = 10;
    int totalZombie = zombiesPerWave + burnedCoffins * 2; // souhaite faire par 2,5 mais complique les choses

    string name = "Zombie";
    int health = 10;
    int speed = 10;
    bool gender = true;
    int strength = 10;
    Role role = Role::CITIZEN;
    ZombieType type = ZombieType::STANDARD;

    for (int i = 0; i < totalZombie; i++) {
        if (burnedCoffins == 1) {
            name = "Un zombie normal";
            health = 15;
            speed = 2;
            gender = true;
            strength = 8;
            role = Role::CITIZEN;
            type = ZombieType::STANDARD;
        }
        else if (burnedCoffins >= 2 && burnedCoffins <= totalCoffins) {
            int randomNumber = rand() % 100;

            if (randomNumber < 50) { // 50%
                name = "Un zombie normal";
                health = 15;
                speed = 2;
                gender = true;
                strength = 8;
                role = Role::CITIZEN;
                type = ZombieType::STANDARD;
            }
            else if (randomNumber < 75) { // 25%
                name = "Un zombie rapide";
                health = 15;
                speed = 5;
                gender = true;
                strength = 4;
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
                name = "Un zombie brutal";
                health = 30;
                speed = 1;
                gender = true;
                strength = 12;
                role = Role::BANDIT;
                type = ZombieType::BRUTAL;
            }
        }
        localZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}

void MissionCemetery::spawnLastZombies(int burnedCoffins) {
    localZombies.clear();

    int totalZombie = 5;

    string name = "Zombie";
    int health = 10;
    int speed = 10;
    bool gender = true;
    int strength = 10;
    Role role = Role::CITIZEN;
    ZombieType type = ZombieType::STANDARD;

    for (int i = 0; i < totalZombie; i++) {
        int randomNumber = rand() % 100;

        if (randomNumber < 50) { // 50%
            name = "Un zombie normal";
            health = 15;
            speed = 2;
            gender = true;
            strength = 8;
            role = Role::CITIZEN;
            type = ZombieType::STANDARD;
        }
        else if (randomNumber < 75) { // 25%
            name = "Un zombie rapide";
            health = 15;
            speed = 5;
            gender = true;
            strength = 4;
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
            name = "Un zombie brutal";
            health = 30;
            speed = 1;
            gender = true;
            strength = 12;
            role = Role::BANDIT;
            type = ZombieType::BRUTAL;
        }
        localZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}

void MissionCemetery::cleanupDead() {
    // remove localSurvivors inutile
    localZombies.erase(
        remove_if(localZombies.begin(), localZombies.end(), [](NpcZombie* z) { return z->getHealth() <= 0; }),
        localZombies.end());
}
