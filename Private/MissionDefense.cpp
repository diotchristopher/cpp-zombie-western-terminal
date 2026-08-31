// game
#include "../public/MissionDefense.h"
#include "../public/IFighter.h"

// cpp
#include <iostream>
#include <algorithm>

using namespace std;

MissionDefense::MissionDefense(Player* player, Location* targetLocation, const std::string& title)
    : Mission(player, targetLocation, MissionType::DEFENSE, title, false, false),
    totalWaves(0), currentWave(0), isDefenseSuccess(false) {
}

int MissionDefense::getTotalWaves() const { return totalWaves; }
int MissionDefense::getCurrentWave() const { return currentWave; }
bool MissionDefense::getIsDefenseSuccess() const { return isDefenseSuccess; }

void MissionDefense::start() {
    isActive = true;
    currentWave = 1;

    if (getTargetLocation()->getInvasionLevel() == InvasionLevel::THREATENED) {
        const int survivorsPlanned = rand() % 6;
        totalWaves = 2;
        spawnSurvivors(survivorsPlanned);
        spawnZombiesPerWave(currentWave);
    }
    else if (getTargetLocation()->getInvasionLevel() == InvasionLevel::INFESTED) {
        totalWaves = 4;
        spawnZombiesPerWave(currentWave);
    }

    cout << ">> [" << getTitle() << "] " << getTargetLocation()->getName()
        << " est attaquée par des hordes de zombies !" << endl;
    cout << "Objectif : Tenir " << totalWaves << " vagues !" << endl;
}

void MissionDefense::update() {
    if (!isActive || isCompleted) {
        return;
    }

    // ajout de l'equipe A dans IFighter : Joueur et Allie
    vector<IFighter*> teamA;

    if (player && player->getHealth() > 0) {
        teamA.push_back(player);
    }

    for (Npc* survivor : localSurvivors) { // difficultes a trouve le Npc*, pensais a const auto, etc...
        if (survivor && survivor->getHealth() > 0) {
            teamA.push_back(survivor);
        }
    }

    // ajout de l'equipe B dans IFighter : Zombie ou Hostile
    vector<IFighter*> teamB;

    for (NpcZombie* zombie : localZombies) {
        if (zombie && zombie->getHealth() > 0) {
            teamB.push_back(zombie);
        }
    }

    // maj quand survivant et joueur mort
    if (teamA.empty())
    {
        cout << "Tous les survivants ont été tués. la ville est tomber.\n";
        cout << "[Nom de la ville] has been lost" << endl;
        isActive = false;
        isCompleted = true;
        isDefenseSuccess = false;
        return;
    }

    // maj quand tous les zombiés sont morts vague suivante, quand tous les vague termine reussie
    if (teamB.empty()) {
        if (currentWave < totalWaves) {
            currentWave++;
            spawnZombiesPerWave(currentWave);
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
        isCompleted = true;
        isActive = false;
        isDefenseSuccess = true;
        if (getTargetLocation()) {
            getTargetLocation()->setInvasionLevel(InvasionLevel::SAFE);
        }
        cout << ">> Victoire ! La defense de " << getTargetLocation()->getName() << " a reussi !" << endl;
    }
}

bool MissionDefense::checkCompletion() { // double checkCompletion()
    return currentWave == totalWaves;
}

void MissionDefense::giveReward(Player& player) {
    player.addAmmo(6);
    player.addReputation(100);
    cout << "Tu as gagné " << player.getAmmo() << " munitions pour ton revolver" << endl;
    cout << "+ Gain d'Honneur" << endl;
}

void MissionDefense::spawnSurvivors(int number) {
    int survivorsToAdd = number;
    for (int i = 0; i < survivorsToAdd; i++) {
        Npc* NpcToRescue;
        NpcToRescue = new Npc(
            "Survivant_" + to_string(i + 1),
            75,
            3,
            true,
            15,
            Role::CITIZEN,
            true
        );
        localSurvivors.push_back(NpcToRescue);
    }
}

void MissionDefense::spawnZombiesPerWave(int currentWave) {
    localZombies.clear();

    int zombiesPerWave = 0;
    int Multiplier = 0;
    if (getTargetLocation()->getInvasionLevel() == InvasionLevel::THREATENED) {
        zombiesPerWave = rand() % 8;
        Multiplier = 2;
    }
    else if (getTargetLocation()->getInvasionLevel() == InvasionLevel::INFESTED) {
        zombiesPerWave = rand() % 16;
        Multiplier = 4;
    }

    int totalZombie = zombiesPerWave + currentWave * Multiplier;

    for (int i = 0; i < totalZombie; i++) {

        int randomNumber = rand() % 100;

        string name = "Zombie";
        int health = 10;
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

void MissionDefense::cleanupDead() {
    localSurvivors.erase(
        remove_if(localSurvivors.begin(), localSurvivors.end(), [](Npc* c) { return c->getHealth() <= 0; }),
        localSurvivors.end());
    localZombies.erase(
        remove_if(localZombies.begin(), localZombies.end(), [](NpcZombie* z) { return z->getHealth() <= 0; }),
        localZombies.end());
}
