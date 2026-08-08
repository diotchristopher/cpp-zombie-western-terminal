#pragma once

// game
#include "../Public/Player.h"
#include "../Public/NpcZombie.h"
#include "../Public/AnimalsZombie.h"

// cpp
#include <vector>
#include <string>

class CombatSystem {
private:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void DisplayStatus(const Player& player, const std::vector<Character*>& enemies);

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void StartCombat(Player& player, std::vector<Character*>& enemies);
};
