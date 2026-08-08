#pragma once

// game
#include "../public/Player.h"
#include "../public/Npc.h"
#include "../public/NpcZombie.h"
#include "../public/MissionRescue.h"
#include "../public/CombatSystem.h"
#include "../public/QuestSystem.h"
#include "../Public/ZoneSystem.h"
#include "../public/LootSystem.h"

// cpp
#include <string>

class Game {
private:
    bool isRunning;
    Player player;
    ZoneSystem zoneSystem;
    LootSystem lootSystem;
    Map* map;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
	void run();
    void handlePlayerChoice(int choice);
};