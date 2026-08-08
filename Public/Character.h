#pragma once

// cpp
#include <string>

class Character {
protected: // private au lieu de protected
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    std::string name;
    int health;
    int speed;
    bool gender;
    int strength;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Character(std::string name, int health, int speed, bool gender, int strength); // ereur ici ajoute de .... : .... au lieu de le mettre dans le cpp

    std::string getName() const;
    int getHealth() const;
    int getSpeed() const;
    bool getGender() const;
    int getStrength() const;

    void takeDamage(int damage);
    void performAttack(Character* target);
};