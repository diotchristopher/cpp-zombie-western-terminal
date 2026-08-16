#pragma once
#include "../public/Mission.h"
#include "../public/Location.h"
#include "../public/AnimalZombie.h"
#include <vector>
#include <string>

class MissionHunting : public Mission {
private:
    Location* targetLocation;
    int animalsToHunt;
    int animalsKilled;

public:
    MissionHunting(const std::string& description, int reward, Location* targetLocation, int animalsToHunt);

    void start() override;
    void update() override;
    bool isCompleted() const override;

    // Pour faciliter le debug/affichage
    int getRemainingAnimals() const;
};
