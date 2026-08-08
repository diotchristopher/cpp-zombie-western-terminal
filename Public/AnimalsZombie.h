#pragma once

// game
#include "../public/Animals.h"

// cpp
#include <string>

class AnimalsZombie : public Animals {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    AnimalsZombie(std::string name, int health, int speed, bool gender, int strength, AnimalName animalName, bool isAggressive,
        Type type, Rarety rarety);
};