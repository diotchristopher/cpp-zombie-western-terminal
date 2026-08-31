#pragma once

// game
#include "../public/Character.h"

// cpp
#include <string>

enum class AnimalName {
    WOLF, PUMA, BEAR,      // forêt / montagne
    DEER, VULTURE,         // plaines
    DOG, HORSE, COW, PIG   // ferme
};

enum class Type {
    STANDARD,
    FLYING
};

enum class Rarety {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC
};

class AnimalsZombie : public Character {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    AnimalName animalName;
    bool aggressive;
    Type type;
    Rarety rarety;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    AnimalsZombie(std::string name, int health, int speed, bool gender, int strength, AnimalName animalName, bool isAggressive,
        Type type, Rarety rarety);

    AnimalName getAnimalName() const;
    bool getIsAggressive() const;
    Type getType() const;
    Rarety getRarety() const;
};