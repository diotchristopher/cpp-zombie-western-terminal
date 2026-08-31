// game
#include "../Public/Mission.h" // correctif final : virgule interdit ;
#include "../Public/LootSystem.h"

// cpp
#include <iostream>

using namespace std;

Mission::Mission(Player* player, Location* targetLocation, MissionType missionType,
    std::string title, bool isActive, bool isCompleted)
    : player(player), targetLocation(targetLocation), missionType(missionType),
    title(title), isActive(isActive), isCompleted(isCompleted) {
} // forgot to add the : maVariable(maVariable)

Player* Mission::getPlayer() const { return player; }
Location* Mission::getTargetLocation() const { return targetLocation; }
MissionType Mission::getMissionType() const { return missionType; }
std::string Mission::getTitle() const { return title; } // oublie de Mission::
bool Mission::getIsActive() const { return isActive; }
bool Mission::getIsCompleted() const { return isCompleted; }



