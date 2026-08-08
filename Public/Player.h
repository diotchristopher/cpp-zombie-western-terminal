#pragma once

// game
#include "../public/Character.h"

// cpp
#include <string>

class Player : public Character {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    int stamina;
    int deadEyes;
    int ammo;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Player(std::string name, int health, int speed, bool gender, int strength, int stamina, int deadEyes);

    int getStamina() const;
    int getDeadEyes() const;

    int getAmmo() const;
    void AddAmmo(int amount);

    void heal(int amount);
    void useStamina();
    void useDeadEyes();
    void rechargeDeadEye(int amount);
};