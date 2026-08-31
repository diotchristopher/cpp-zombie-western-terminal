#pragma once

// game
#include "../public/Mission.h" // correctif final : virgule interdit ;
#include "../public/Player.h"
#include "../public/Location.h"
#include "../public/Npc.h"
#include "../Public/NpcZombie.h"
#include "../Public/CombatSystem.h"

// cpp
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

enum class MissionRescueScenario {SOLO, CAMP, HOSTILE};

class MissionRescue : public Mission {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    std::vector<Npc*> localSurvivors;
    std::vector<NpcZombie*> localZombies;
    std::vector<Npc*> localBandits;
    
    int waveCount;
    int currentWave;
    // int waveRemaining; // enlever  int waveRemaining
    int zombiesPerWave;
    bool isRescued;

    MissionRescueScenario missionScenario;

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void spawnSoloSurvivor();
    void spawnCampSurvivors(int number);
    void spawnHostileBandits(int number);
    void spawnZombiesPerWave(int currentWave);

    void cleanupDead();

public: 
    MissionRescue(Player* player, Location* targetLocation, const std::string& title = "Defendre");
    // enlever MissionType missionType, ..., bool isActive, bool isCompleted, int waveCount, int currentWave, int zombiesPerWave, bool isRescued
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    int getWaveCount() const;
    int getCurrentWave() const;
    // int getWaveRemaining() const;
    int getZombiesPerWave() const;
    bool getIsRescued() const;

    // void spawnZombies(int number); // fonction deplacer en private et renomme
    
    void start() override;
    void update() override;
    bool checkCompletion() override;

    void giveReward(Player& player) override;
};

