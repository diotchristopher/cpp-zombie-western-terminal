#pragma once

// game
#include "../public/Player.h"
#include "../public/Location.h"

// cpp
#include <string>

enum class MissionType {
    ESCORT, DELIVERY, AMBUSH, DEFENSE, RESCUE };

class Mission {
protected: // remplacer private par protected et pas utiliser des setter
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    Player* player;
    Location* targetLocation;
    MissionType missionType;
    std::string title;
    bool isActive;
    bool isCompleted;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Mission(Player* player, Location* targetLocation, MissionType missionType, std::string title, bool isActive, bool isCompleted);

    // get
    Player* getPlayer() const;
    Location* getTargetLocation() const;
    MissionType getMissionType() const;
    std::string getTitle() const;
    bool getIsActive() const;
    bool getIsCompleted() const;


    virtual void start() = 0; // oublie les = 0

    virtual void update() = 0;;

    virtual bool checkCompletion() = 0;

    virtual ~Mission() {}
};