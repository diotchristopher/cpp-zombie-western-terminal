// game
#include "../Public/ZoneSystem.h"

// cpp
#include <iostream>
#include <cstdlib> // oublie
#include <ctime> // oublie

using namespace std;


ZoneSystem::ZoneSystem(Map* map) : worldMap(map) {
    // remove this plus besoin
    // srand((unsigned)time(nullptr)); // oublie
}

void ZoneSystem::setMap(Map* map) { worldMap = map; }

vector<NpcZombie*>& ZoneSystem::getNpcZombies() { return localNpcZombies; } //  oublie ZoneSystem::
vector<AnimalsZombie*>& ZoneSystem::getAnimalZombies() { return localAnimalZombies; }//  oublie ZoneSystem::

vector<Character*> ZoneSystem::spawnZombiesForRoute(const Location& from, const Location& to) {
    vector<Character*> enemies;

    // probabilité de rencontre basée sur invasion level moyen
    int baseChance = 15;
    int fromLevel = static_cast<int>(from.getInvasionLevel()); // oublie de static_cast<int>
    int toLevel = static_cast<int>(to.getInvasionLevel()); // oublie de static_cast<int>
    int avg = (fromLevel + toLevel) / 2;
    int encounterChance = baseChance + avg * 25; // SAFE ~15, INFESTED ~65

    int randomNumber = rand() % 100;
    if (randomNumber >= encounterChance) {
        // pas d'ennemi
        return enemies;
    }

    // Spawn 1..(1 + avg*2) ennemis, stats simples
    int count = 1 + rand() % (1 + avg * 2 + 1);
    for (int i = 0; i < count; ++i) {
        int hp = 10 + rand() % (10 + avg * 5);
        int speed = 1 + rand() % 3;
        int strength = 2 + rand() % 4;
        string name = "Zombie_" + to_string(rand() % 1000);
        // on utilise Character comme ennemi simple
        Character* z = new Character(name, hp, speed, false, strength);
        enemies.push_back(z);
    }
    cout << "[ZoneSystem] Rencontre ! " << enemies.size() << " ennemis sur la route entre " << from.getName() << " et " << to.getName() << std::endl;
    return enemies;
}

vector<NpcZombie*> ZoneSystem::spawnNpcZombies(const Location& location) {
    vector<NpcZombie*> localNpcZombies;

    int totalZombie = 0;

    if (location.getInvasionLevel() == InvasionLevel::SAFE) {
        totalZombie = rand() % 2 + 2;
    } else if (location.getInvasionLevel() == InvasionLevel::THREATENED) {
        totalZombie = rand() % 4 + 3;
    } else if (location.getInvasionLevel() == InvasionLevel::INFESTED) {
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
        } else if (randomNumber < 75) { // 25%
            name = "Un zombie rapide";
            health = 20;
            speed = 5;
            gender = true;
            strength = 7;
            role = Role::FARMER;
            type = ZombieType::RUNNER;
        } else if (randomNumber < 90) { // 15%
            name = "Un zombie cracheur";
            health = 25;
            speed = 3;
            gender = true;
            strength = 5;
            role = Role::PROSTITUTE;
            type = ZombieType::SPITTER;
        } else { // 10%
            name = "Un zombie brutal";
            health = 40;
            speed = 1;
            gender = true;
            strength = 20;
            role = Role::BANDIT;
            type = ZombieType::BRUTAL;
        }

        localNpcZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }

    return localNpcZombies;
}

vector<AnimalsZombie*> ZoneSystem::spawnAnimalZombies(const Location& location) {
    vector<AnimalsZombie*> localAnimalZombies;

    int totalAnimals = 0;

    if (location.getLocationType() == LocationType::FOREST) {
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
        } else if (roll < 90) { // 20% Puma
            localAnimalZombies.push_back(new AnimalsZombie(
                "Puma Zombie",
                40, 6, true, 12,
                AnimalName::PUMA,
                true,
                Type::STANDARD,
                Rarety::RARE
            ));
        } else { // 10% Ours
            localAnimalZombies.push_back(new AnimalsZombie(
                "Ours Zombie",
                80, 2, true, 20,
                AnimalName::BEAR,
                true,
                Type::STANDARD,
                Rarety::EPIC
            ));
        }
    } else if (location.getLocationType() == LocationType::PLAINS) {
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
        } else { // 30% Vautours
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
    } else if (location.getLocationType() == LocationType::FARM) {
        int roll = rand() % 100;

        if (roll < 25) { // 25% chiens (1-2)
            totalAnimals = rand() % 2 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Chien Zombie", 20, 5, true, 6,
                    AnimalName::DOG, true, Type::STANDARD, Rarety::COMMON));
            }
        } else if (roll < 50) { // 25% chevaux (2-3)
            totalAnimals = rand() % 2 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Cheval Zombie", 35, 4, true, 10,
                    AnimalName::HORSE, true, Type::STANDARD, Rarety::UNCOMMON));
            }
        } else if (roll < 75) { // 25% vaches (2-4, passives sauf si attaquées)
            totalAnimals = rand() % 4 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Vache Zombie", 40, 2, true, 8,
                    AnimalName::COW, false, Type::STANDARD, Rarety::COMMON));
            }
        } else { // 25% cochons (2-3, passifs sauf si attaqués)
            totalAnimals = rand() % 3 + 1;
            for (int i = 0; i < totalAnimals; i++) {
                localAnimalZombies.push_back(new AnimalsZombie(
                    "Cochon Zombie", 25, 2, true, 5,
                    AnimalName::PIG, false, Type::STANDARD, Rarety::COMMON));
            }
        }
    }
    return localAnimalZombies;
}

void ZoneSystem::cleanupDead() {
    auto& localNpcZombies = getNpcZombies(); // ajoute de ca pour resoudre le probleme
    localNpcZombies.erase(
        remove_if(localNpcZombies.begin(), localNpcZombies.end(),
            [](NpcZombie* z) {
                if (z->getHealth() <= 0) {
                    delete z;
                    return true;
                }
                return false;
            }),
        localNpcZombies.end());

    auto& localAnimalZombies = getAnimalZombies(); // ajoute de ca pour resoudre le probleme

    localAnimalZombies.erase(
        remove_if(localAnimalZombies.begin(), localAnimalZombies.end(),
            [](AnimalsZombie* a) {
                if (a->getHealth() <= 0) {
                    delete a;
                    return true;
                }
                return false;
            }),
        localAnimalZombies.end());
}
