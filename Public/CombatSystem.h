#pragma once

// game
#include "../Public/Player.h"
#include "../Public/NpcZombie.h"
#include "../Public/AnimalsZombie.h"
#include "../public/IFighter.h"
#include "../public/LootSystem.h"

// cpp
#include <vector>
#include <string>

class CombatSystem {
private:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    // enlever pour le moment 
    // void DisplayStatus(std::vector<IFighter*>& teamA, std::vector<IFighter*>& teamB); // remplacement de const Player& player, const std::vector<Character*>& enemies

    // pas besoin parce que CombatSysteme pas proprietaire
    //std::vector<IFighter*>& teamA; 
    //std::vector<IFighter*>& teamB;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    void StartCombat(std::vector<IFighter*>& teamA, std::vector<IFighter*>& teamB);  // remplacement de const Player& player, const std::vector<Character*>& enemies
};
