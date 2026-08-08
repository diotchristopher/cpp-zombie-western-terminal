// game
#include "../public/NpcZombie.h"

// cpp
#include <iostream>

using namespace std;

NpcZombie::NpcZombie(string name, int health, int speed, bool gender, int strength, Role role, bool isMilitia, ZombieType zombieType) : Npc(name, health, speed, gender, strength, role, isMilitia), zombieType(zombieType) {}

ZombieType NpcZombie::getZombieType() const { return zombieType; }

string NpcZombie::getZombieTypeAsString() const {
    switch (zombieType) {
    case ZombieType::STANDARD: return "Standard";
    case ZombieType::RUNNER: return "Runner";
    case ZombieType::SPITTER: return "Spitter";
    case ZombieType::BRUTAL: return "Brutal";
    default: return "Unknown";
    }
}