#pragma once

// game
#include "../Public/Map.h"
#include "../Public/Location.h"
#include "../public/Character.h"

// cpp
#include <vector>
#include <cstdlib>
#include <ctime>

class ZoneSystem { // partie la plus difficile
private:
    Map* worldMap; // non-owned

public:
    ZoneSystem(Map* map = nullptr);
    void setMap(Map* map);

    std::vector<Character*> spawnZombiesForRoute(const Location& from, const Location& to);

    void updateZones();
};