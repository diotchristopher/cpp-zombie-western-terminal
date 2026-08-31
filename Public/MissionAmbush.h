#pragma once

// game
#include "../public/Mission.h"
#include "../public/Player.h"
#include "../public/Location.h"
#include "../Public/NpcZombie.h"
#include "../Public/AnimalsZombie.h"
#include "../Public/CombatSystem.h"

// cpp
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

enum class MissionAmbushScenario { ANIMAL_ZOMBIE, NPC_ZOMBIE };

class MissionAmbush : public Mission {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    std::vector<NpcZombie*> localNpcZombies;
    std::vector<AnimalsZombie*> localAnimalZombies;

    bool hasSurvived;

    MissionAmbushScenario missionScenario;

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void spawnNpcZombies();
    void spawnAnimalZombies();

    void cleanupDead();

public:
    MissionAmbush(Player* player, Location* targetLocation, MissionType missionType, std::string title, bool isActive, bool isCompleted, bool hasSurvived);

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    bool getHasSurvived() const;

    void start() override;
    void update() override;
    bool checkCompletion() override;
};