// game
#include "../Public/ZoneSystem.h"

// cpp
#include <iostream>
#include <cstdlib> // oublie
#include <ctime> // oublie

using namespace std;


ZoneSystem::ZoneSystem(Map* map) : worldMap(map) {
    srand((unsigned)time(nullptr)); // oublie
}

void ZoneSystem::setMap(Map* map) { worldMap = map; }

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

void ZoneSystem::updateZones() {
    // Parcours non-const : utilise getLocationAt(i) pour obtenir Location* modifiable
    for (size_t i = 0; i < worldMap->size(); ++i) {
        Location* location = worldMap->getLocationAt(i);
        if (!location) continue;

        // Exemple de logique : petite chance de montée du niveau d'invasion
        int random = std::rand() % 100;
        if (random < 10) { // 10% de chance d'augmenter le danger local
            InvasionLevel invasionLevel = location->getInvasionLevel();
            if (invasionLevel == InvasionLevel::SAFE) location->setInvasionLevel(InvasionLevel::THREATENED);
            else if (invasionLevel == InvasionLevel::THREATENED) location->setInvasionLevel(InvasionLevel::INFESTED);
            // si HIGH, on reste HIGH
        }
    }
}
