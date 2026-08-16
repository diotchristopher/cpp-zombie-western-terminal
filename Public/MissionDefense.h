#pragma once

// game
#include "../public/Mission.h"
#include "../public/Location.h"
#include "../public/Player.h"

// cpp
#include <string>

class MissionDefense : public Mission {
public:
    MissionDefense(Player* player, Location* targetLocation, MissionType missionType, string title, bool isActive, bool isCompleted);
    void start() override;
    void update() override;
    bool checkCompletion() override;

private:
    int wavesRemaining;
};
