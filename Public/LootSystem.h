#pragma once

// game
#include "../public/Player.h"

// cpp
#include <vector>
#include <string>

struct LootItem {
    std::string name;
    int quantity;
};

class LootSystem {
public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void HandleLoot(Player& player);
    std::vector<LootItem> GenerateLoot();
    void DisplayLoot(const std::vector<LootItem>& loot);
};
