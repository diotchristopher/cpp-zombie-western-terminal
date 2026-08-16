#include "../public/MissionHunting.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

MissionHunting::MissionHunting(const std::string& description, int reward, Location* targetLocation, int animalsToHunt)
    : Mission(description, reward), targetLocation(targetLocation), animalsToHunt(animalsToHunt), animalsKilled(0) {
}

void MissionHunting::start() {
    std::cout << "[Mission] Début de mission : " << description << std::endl;
    std::cout << "Objectif : éliminer " << animalsToHunt << " animaux zombies à " << targetLocation->getName() << "." << std::endl;

    // Simulation du spawn
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < animalsToHunt; ++i) {
        int type = std::rand() % 3; // 0=wolf, 1=bear, 2=cougar
        switch (type) {
        case 0: targetLocation->addEnemy(ZombieAnimal("Zombie Wolf")); break;
        case 1: targetLocation->addEnemy(ZombieAnimal("Zombie Bear")); break;
        case 2: targetLocation->addEnemy(ZombieAnimal("Zombie Cougar")); break;
        }
    }
}

void MissionHunting::update() {
    if (!targetLocation) return;

    // On compte les ennemis restants
    int remaining = 0;
    for (auto& enemy : targetLocation->getEnemies()) {
        if (enemy.isAlive()) {
            remaining++;
        }
    }

    animalsKilled = animalsToHunt - remaining;

    std::cout << "[Mission] Animaux zombies restants : " << remaining << std::endl;

    if (isCompleted()) {
        std::cout << "[Mission] Tous les animaux zombies ont été éliminés !" << std::endl;
    }
}

bool MissionHunting::isCompleted() const {
    return animalsKilled >= animalsToHunt;
}

int MissionHunting::getRemainingAnimals() const {
    return std::max(0, animalsToHunt - animalsKilled);
}
