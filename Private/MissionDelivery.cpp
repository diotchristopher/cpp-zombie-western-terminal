#include "../Public/MissionDelivery.h"
#include "../Public/CombatSystem.h"

#include <iostream>

MissionDelivery::MissionDelivery(Player* p, Location* start, Location* end)
    : Mission(p, start), destination(end) {
}

void MissionDelivery::start() {
    std::cout << "[MissionDelivery] Livrez le colis de "
        << targetLocation->getName() << " à "
        << destination->getName() << ".\n";
    isActive = true;
}

void MissionDelivery::update() {
    if (!isActive) return;

    int zombieCount = rand() % 4;
    if (zombieCount > 0) {
        std::cout << "Des zombies attaquent en chemin !\n";
        CombatSystem::startCombat(*player, zombieCount);
    }

    std::cout << "Colis livré à " << destination->getName() << " !\n";
    isActive = false;
}

bool MissionDelivery::isCompleted() const {
    return !isActive;
}
