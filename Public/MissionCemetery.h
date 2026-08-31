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

class MissionCemetery : public Mission {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    std::vector<NpcZombie*> localZombies;
    
    int totalCoffins;
    int burnedCoffins;
    bool finalWaveSpawned;
    bool isPurified;

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void spawnZombiesPerCoffins(int burnedCoffins);
    void spawnLastZombies(int burnedCoffins);
    void cleanupDead();

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    MissionCemetery(Player* player, Location* targetLocation, const std::string& title = "Purifier le cimetiere");

    int getTotalCoffins() const;
    int getBurnedCoffins() const;
    bool getIsPurified() const;

    void start() override;
    void update() override;
    bool checkCompletion() override;

    void giveReward(Player& player) override;
};
