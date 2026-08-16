#pragma once

// game
#include "../public/Mission.h"
#include "../public/Location.h"
#include "../public/Player.h"

// cpp
#include <string>

class MissionAmbush : public Mission {
public:
    MissionAmbush(Player* player, Location* targetLocation, MissionType missionType, std::string title, bool isActive, bool isCompleted);
    
    void start() override;

    void update() override;

    bool checkCompletion() override;
};
