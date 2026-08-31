#pragma once

// game
#include "../public/Mission.h"
#include "../public/Player.h"
#include "../public/Location.h"
#include "../public/CombatSystem.h"
#include "../public/NpcZombie.h"

// cpp
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class MissionDefense : public Mission {
private:
    //======================================================================================
    // PROPERTIES
    //======================================================================================
    std::vector<Npc*> localSurvivors;
    std::vector<NpcZombie*> localZombies;

    int totalWaves;
    int currentWave;
    bool isDefenseSuccess;

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void spawnSurvivors(int number);
    void spawnZombiesPerWave(int currentWave);
    void cleanupDead();

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    MissionDefense(Player* player, Location* targetLocation, const std::string& title = "Defends la ville");

    int getTotalWaves() const;
    int getCurrentWave() const;
    bool getIsDefenseSuccess() const;

    void start() override;
    void update() override;
    bool checkCompletion() override;

    void giveReward(Player& player) override;
};
