#pragma once

// cpp
#include <string>

class IFighter {
public: // oublie d'indiquer la porter
	virtual ~IFighter() {}; // oublie de le mettre et oublie des parenthese
	virtual void takeDamage(int damage) = 0;
	virtual void performAttack(IFighter* target) = 0; // oublie de remplacer Character* par IFighter*

	virtual std::string getName() const = 0; // ajout complementaire, acces impossible via autre class
	virtual int getHealth() const = 0; // ajout complementaire, acces impossible via autre class
	virtual int getStrength() const = 0; // ajout complementaire, acces impossible via autre class
	virtual bool isAlive() const = 0; // oublie de const
	virtual bool isPlayerControlled() const = 0; // ajout pour identifier le joueur
	virtual bool isLootable() const = 0;
};