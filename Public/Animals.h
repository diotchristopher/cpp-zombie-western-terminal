#pragma once

// game
#include "../public/Character.h"

// cpp
#include <string>

enum class AnimalName { BEAR, WOLF, COUGAR, BOAR };

enum class Type { BIRD, HERBIVORE, CARNIVORE, OMNIVORE };

enum class Rarety { COMMON, RARE, LEGENDARY, UNIQUE };

class Animals : public Character { // oublie de : public Character
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    AnimalName animalName;
    bool isAggressive;
    Type type;
    Rarety rarety;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Animals(std::string name, int health, int speed, bool gender, int strength, AnimalName animalName, bool isAggressive, Type type, Rarety rarety);

    AnimalName getAnimalName() const;
    bool getIsAggressive() const;
    Type getType() const;
    Rarety getRarety() const;
};