// game
#include "../public/MissionAmbush.h"
#include "../public/CombatSystem.h"

// cpp
#include <iostream>

using namespace std;

MissionAmbush::MissionAmbush(Player* player, Location* targetLocation, MissionType missionType, string title, bool isActive, bool isCompleted)
    : Mission(player, targetLocation, missionType, title, isActive, isCompleted) {
}

void MissionAmbush::start() {
    cout << "[MissionAmbush] Vous tombez dans une embuscade de zombies !\n";
    isActive = true;
}

void MissionAmbush::update() {
    if (!isActive) return;

    int zombieCount = 5 + (rand() % 5);
    CombatSystem::startCombat(*player, zombieCount);

    cout << "[MissionAmbush] Vous avez survécu à l'embuscade.\n";
    isActive = false;
}

bool MissionAmbush::checkCompletion() {
    return !isActive;
}
