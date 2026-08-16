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

class MissionRescue : public Mission { // inverser MissionRescue et Mission
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    std::vector<Npc*> localSurvivors; // oublie de std
    std::vector<NpcZombie*> localZombies; // oublie de std
    
    int waveCount;
    int currentWave;
    int waveRemaining;
    int zombiesPerWave;
    bool isRescued; // int au lieu de bool

public: 
    MissionRescue(Player* player, Location* targetLocation, MissionType missionType, std::string title, bool isActive, bool isCompleted, int waveCount, int currentWave, int waveRemaining, int zombiesPerWave, bool isRescued); // int isRescued au lieu de bool isRescued
    
    //======================================================================================
    // FUNCTIONS
    //======================================================================================

    int getWaveCount() const;
    int getCurrentWave() const;
    int getWaveRemaining() const;
    int getZombiesPerWave() const;
    bool getIsRescued() const; // int au lieu de bool 
    
    void spawnZombies();
    
    void start() override;

    void update() override;

    bool checkCompletion() override;
};

