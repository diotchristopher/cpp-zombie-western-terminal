#pragma once

// game
#include "../public/Player.h"
#include "../public/Map.h"
#include "../Public/ZoneSystem.h"
#include "../public/CombatSystem.h"
#include "../public/LootSystem.h"
#include "../public/QuestSystem.h"
#include "../Public/Location.h"
#include "../public/Mission.h"
#include "../public/MissionRescue.h"

// cpp
#include <string>
#include <vector>
#include <memory>

class Game {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    bool isRunning;
    Player player;
    Map worldMap;
    ZoneSystem zoneSystem;
    LootSystem lootSystem;
    QuestSystem* questSystem;
    CombatSystem combatSystem;

    Location* currentLocation;

    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void displayMenu();
    void handleExplorer();
    void handleResearch();
    void handleMission();
    void moveToLocation(Location* location);

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Game(const std::string& playerName);
    ~Game(); // oublie

	void run();
};