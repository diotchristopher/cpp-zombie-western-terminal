#pragma once

// game
#include "../public/Character.h"

// cpp
#include <string>

enum class Role { SHERIFF, BANDIT, PROSTITUTE, MERCHANT, FARMER, CITIZEN, PRIEST, DOCTOR }; // inverser class enum, et utilisation de struct au lieu de enum

class Npc : public Character {
private:
	Role role;
	bool isMilitia;

public:
	Npc(std::string name, int health, int speed, bool gender, int strength, Role role, bool isMilitia); // oublie constructuer parent

	Role getRole() const;
	bool getIsMilitia() const;

	bool isLootable() const override;

	std::string getRoleAsString();
};
