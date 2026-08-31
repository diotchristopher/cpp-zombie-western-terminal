#pragma once

// game
#include "../Public/Map.h"
#include "../Public/Location.h"
#include "../public/Character.h"
#include "../public/NpcZombie.h"
#include "../public/AnimalsZombie.h"

// cpp
#include <vector>
#include <cstdlib>
#include <ctime>

class ZoneSystem { // partie la plus difficile
private:
    Map* worldMap; // non-owned

    std::vector<NpcZombie*> localNpcZombies; // oublie de std::
    std::vector<AnimalsZombie*> localAnimalZombies; // oublie de std::

public:
    ZoneSystem(Map* map = nullptr);
    void setMap(Map* map);

    std::vector<Character*> spawnZombiesForRoute(const Location& from, const Location& to);

    std::vector<NpcZombie*> spawnNpcZombies(const Location& location);
    std::vector<AnimalsZombie*> spawnAnimalZombies(const Location& location);

    std::vector<NpcZombie*>& getNpcZombies();
    std::vector<AnimalsZombie*>& getAnimalZombies();

    void cleanupDead();
};