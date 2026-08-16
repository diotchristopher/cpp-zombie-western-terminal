// game
#include "../Public/MissionDefense.h"
#include "../Public/CombatSystem.h"

// cpp
#include <iostream>

using namespace std;

MissionDefense::MissionDefense(Player* player, Location* targetLocation, MissionType missionType, string title, bool isActive, bool isCompleted)
    : Mission(player, targetLocation, missionType, title, isActive, isCompleted), wavesRemaining(3) {
}

void MissionDefense::start() {
    cout << "Défendez " << targetLocation->getName()
        << " contre des vagues de zombies !\n";
    isActive = true;
}

void MissionDefense::update() {
    if (!isActive) return;

    cout << "Vague restante : " << wavesRemaining << "\n";
    int zombieCount = 3 + (rand() % 5);

    CombatSystem::startRescueCombat(*player, targetLocation, zombieCount);

    wavesRemaining--;

    if (wavesRemaining <= 0) {
        cout << "[MissionDefense] Zone sécurisée !\n";
        targetLocation->setSafeZone(true);
        isActive = false;
    }
}

bool MissionDefense::checkCompletion() {
    return !isActive;
}
