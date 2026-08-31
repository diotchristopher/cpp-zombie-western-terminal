// game
#include "../public/AnimalsZombie.h"

// cpp
#include <algorithm>
#include <iostream>

using namespace std;

AnimalsZombie::AnimalsZombie(std::string name, int health, int speed, bool gender, int strength,
    AnimalName animalName, bool isAggressive, Type type, Rarety rarety)
    : Character(name, health, speed, gender, strength),
    animalName(animalName),
    aggressive(isAggressive),
    type(type),
    rarety(rarety) {
}

AnimalName AnimalsZombie::getAnimalName() const { return animalName; }
bool AnimalsZombie::getIsAggressive() const { return aggressive; }
Type AnimalsZombie::getType() const { return type; }
Rarety AnimalsZombie::getRarety() const { return rarety; }