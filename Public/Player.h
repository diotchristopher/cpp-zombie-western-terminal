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
    int money;
    int reputation;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Player(std::string name, int health, int speed, bool gender, int strength, int stamina, int deadEyes, int ammo); // oublie de ammo

    int getStamina() const;
    int getDeadEyes() const;

    int getAmmo() const;
    void addAmmo(int amount); // remplacement du A majuscule

    int getMoney() const;
    void addMoney(int amount);

    int getReputation() const;
    void addReputation(int amount);

    bool isPlayerControlled() const override;

    void heal(int amount);
    void useStamina();
    void useDeadEyes();
    void rechargeDeadEye(int amount);
};