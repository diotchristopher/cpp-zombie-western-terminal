// game
#include "../public/AnimalsZombie.h"

// cpp
#include <iostream>

using namespace std;

AnimalsZombie::AnimalsZombie(string name, int health, int speed, bool gender, int strength, AnimalName animalName, bool isAggressive,
    Type type, Rarety rarety) : Animals(name, health, speed, gender, strength, animalName, isAggressive, type, rarety) {}