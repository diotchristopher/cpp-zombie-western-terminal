// game
#include "../public/Animals.h"

// cpp
#include <iostream>

using namespace std;

Animals::Animals(string name, int health, int speed, bool gender, int strength, AnimalName animalName, bool isAggressive, Type type, Rarety rarety) : Character(name, health, speed, gender, strength), animalName(animalName), isAggressive(isAggressive), type(type), rarety(rarety) {}

AnimalName Animals::getAnimalName() const { return animalName; }
bool Animals::getIsAggressive() const { return isAggressive; }
Type Animals::getType() const { return type; }
Rarety Animals::getRarety() const { return rarety; }