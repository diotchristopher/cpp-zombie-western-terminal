#pragma once

// game
#include "../public/IFighter.h"

// cpp
#include <string>

class Character : public IFighter {
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
    Character(std::string name, int health, int speed, bool gender, int strength); // erreur ici ajoute de .... : .... au lieu de le mettre dans le cpp
    virtual ~Character() = default; // oublie obligatoire parce que methode virtuel

    std::string getName() const override;
    int getHealth() const override;
    int getSpeed() const;
    bool getGender() const;
    int getStrength() const override;

    bool isAlive() const override; // oublie de const
    virtual bool isPlayerControlled() const override; // oublie de override
    virtual bool isLootable() const override;

    void takeDamage(int damage) override; // nouveau systeme de combat : ajout de override et virtual
    void performAttack(IFighter* target) override; // oublie de remplacer Character* target


};