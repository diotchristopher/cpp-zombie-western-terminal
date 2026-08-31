// game
#include "../public/MissionAmbush.h"
#include "../public/IFighter.h"

// cpp
#include <iostream>
#include <algorithm>

using namespace std;

MissionAmbush::MissionAmbush(Player* player, Location* targetLocation, MissionType missionType, string title, bool isActive, bool isCompleted, bool hasSurvived) : Mission(player, targetLocation, missionType, title, false, false), 
hasSurvived(false), missionScenario(MissionAmbushScenario::NPC_ZOMBIE) {
}

bool MissionAmbush::getHasSurvived() const { return hasSurvived; }

void MissionAmbush::start() {
    isActive = true;

    const int random = rand() % 100;
    if (getTargetLocation()->getLocationType() == LocationType::FOREST 
        || getTargetLocation()->getLocationType() == LocationType::PLAINS
        || getTargetLocation()->getLocationType() == LocationType::FARM) {
        missionScenario = MissionAmbushScenario::ANIMAL_ZOMBIE;
        spawnAnimalZombies();
    } else if (getTargetLocation()->getLocationType() == LocationType::ROAD ) { // || getTargetLocation()->getLocationType() == LocationType::
        missionScenario = MissionAmbushScenario::NPC_ZOMBIE;
        spawnNpcZombies();
    }

    if (missionScenario != MissionAmbushScenario::ANIMAL_ZOMBIE && missionScenario != MissionAmbushScenario::NPC_ZOMBIE) {
        isActive = false;
    }
}

void MissionAmbush::update() {
    if (!isActive || isCompleted) {
        return;
    }

    // ajout de l'equipe A dans IFighter : Joueur
    vector<IFighter*> teamA;

    if (player && player->getHealth() > 0) {
        teamA.push_back(player);
    }

    // ajout de l'equipe B dans IFighter : Npc Zombie ou Animals Zombie
    vector<IFighter*> teamB;

    if (missionScenario == MissionAmbushScenario::ANIMAL_ZOMBIE) {
        for (AnimalsZombie* animalsZombie : localAnimalZombies) {
            if (animalsZombie && animalsZombie->getHealth() > 0) {
                teamB.push_back(animalsZombie);
            }
        }
    }
    else {
        for (NpcZombie* npcZombie : localNpcZombies) {
            if (npcZombie && npcZombie->getHealth() > 0) {
                teamB.push_back(npcZombie);
            }
        }
    }

    // maj quand joueur mort
    if (teamA.empty())
    {
        cout << "Tu es mort. Repousse des Zombie échouée.\n";
        isActive = false;
        isCompleted = true;
        hasSurvived = false;
        return;
    }

    // maj quand tous les npc zombie ou animal zombie son mort termine reussie
    if (teamB.empty()) {
        hasSurvived = true;
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
    }
}

bool MissionAmbush::checkCompletion() {
    return hasSurvived == true;
}

void MissionAmbush::spawnNpcZombies() {
    localNpcZombies.clear();

    int totalZombie = 0;

    if (getTargetLocation()->getInvasionLevel() == InvasionLevel::SAFE) {
        totalZombie = rand() % 2 + 2;
    }
    else if (getTargetLocation()->getInvasionLevel() == InvasionLevel::THREATENED) {
        totalZombie = rand() % 4 + 3;
    }
    else if (getTargetLocation()->getInvasionLevel() == InvasionLevel::INFESTED) {
        totalZombie = rand() % 7 + 5;
    }

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

        localNpcZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}

void MissionAmbush::spawnAnimalZombies() {
    localAnimalZombies.clear();

    int totalAnimals = 0;

    if (getTargetLocation()->getLocationType() == LocationType::FOREST) {
        int roll = rand() % 100;
        if (roll < 70) { // 70% Loups
            int packSize = rand() % 4 + 2; // 3-5
            for (int i = 0; i < packSize; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Loup Zombie",
                    25, 4, true, 8,
                    AnimalName::WOLF,
                    true,
                    Type::STANDARD,
                    Rarety::COMMON
                ));
            }
        }
        else if (roll < 90) { // 20% Puma
            localAnimalZombies.push_back(new AnimalsZombie(
                "Puma Zombie",
                40, 6, true, 12,
                AnimalName::PUMA,
                true,
                Type::STANDARD,
                Rarety::RARE
            ));
        }
        else { // 10% Ours
            localAnimalZombies.push_back(new AnimalsZombie(
                "Ours Zombie",
                80, 2, true, 20,
                AnimalName::BEAR,
                true,
                Type::STANDARD,
                Rarety::EPIC
            ));
        }
    } else if (getTargetLocation()->getLocationType() == LocationType::PLAINS) {
        int roll = rand() % 100;
        if (roll < 70) { // 70% Cerfs
            int herdSize = rand() % 3 + 1;
            for (int i = 0; i < herdSize; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Cerf Zombie",
                    30, 5, true, 6,
                    AnimalName::DEER,
                    true,
                    Type::STANDARD,
                    Rarety::COMMON
                ));
            }
        }
        else { // 30% Vautours
            int flockSize = rand() % 2;
            for (int i = 0; i < flockSize; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Vautour Zombie",
                    15, 7, true, 4,
                    AnimalName::VULTURE,
                    true,
                    Type::FLYING,
                    Rarety::UNCOMMON
                ));
            }
        }
    } else if (getTargetLocation()->getLocationType() == LocationType::FARM) {
        int roll = rand() % 100;

        if (roll < 25) { // 25% chiens (1-2)
            totalAnimals = rand() % 2 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Chien Zombie", 20, 5, true, 6,
                    AnimalName::DOG, true, Type::STANDARD, Rarety::COMMON));
            }
        }
        else if (roll < 50) { // 25% chevaux (2-3)
            totalAnimals = rand() % 2 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Cheval Zombie", 35, 4, true, 10,
                    AnimalName::HORSE, true, Type::STANDARD, Rarety::UNCOMMON));
            }
        }
        else if (roll < 75) { // 25% vaches (2-4, passives sauf si attaquées)
            totalAnimals = rand() % 4 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Vache Zombie", 40, 2, true, 8,
                    AnimalName::COW, false, Type::STANDARD, Rarety::COMMON));
            }
        }
        else { // 25% cochons (2-3, passifs sauf si attaqués)
            totalAnimals = rand() % 3 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Cochon Zombie", 25, 2, true, 5,
                    AnimalName::PIG, false, Type::STANDARD, Rarety::COMMON));
            }
        }
    }
}

void MissionAmbush::cleanupDead() {
    localNpcZombies.erase(
        remove_if(localNpcZombies.begin(), localNpcZombies.end(), [](NpcZombie* z) { return z->getHealth() <= 0; }),
        localNpcZombies.end());
    localAnimalZombies.erase(
        remove_if(localAnimalZombies.begin(), localAnimalZombies.end(), [](AnimalsZombie* a) { return a->getHealth() <= 0; }),
        localAnimalZombies.end()); // Npc* au lieu de AnimalsZombie
}