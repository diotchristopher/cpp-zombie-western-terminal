#include "../Public/MissionEscort.h"
#include "../Public/CombatSystem.h"
#include <iostream>

MissionEscort::MissionEscort(Player* p, Location* start, Location* end)
    : Mission(p, start), destination(end), escortedNpc(nullptr) {
}

void MissionEscort::start() {
    escortedNpc = new Npc("Survivant à escorter", 100, 3, true, 1);
    std::cout << "[MissionEscort] Vous devez escorter "
        << escortedNpc->getName() << " jusqu'à "
        << destination->getName() << ".\n";
    isActive = true;
}

void MissionEscort::update() {
    if (!isActive) return;

    int zombieCount = rand() % 3;
    if (zombieCount > 0) {
        std::cout << "Des zombies attaquent votre groupe !\n";
        CombatSystem::startEscortCombat(*player, escortedNpc, zombieCount);
    }

    if (escortedNpc && escortedNpc->isAlive()) {
        std::cout << escortedNpc->getName()
            << " est arrivé à destination !\n";
    }
    else {
        std::cout << "[MissionEscort] Échec : l'escorte est morte.\n";
    }
    isActive = false;
}

bool MissionEscort::isCompleted() const {
    return !isActive;
}
