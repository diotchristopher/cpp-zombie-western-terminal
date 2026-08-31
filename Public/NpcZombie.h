#pragma once

// game
#include "../public/Npc.h"

enum class ZombieType {STANDARD, RUNNER, SPITTER, BRUTAL};

class NpcZombie : public Npc {
private:
	ZombieType zombieType;

public:
	NpcZombie(std::string name, int health, int speed, bool gender, int strength, Role role, bool isMilitia, ZombieType zombieType); // oublie du cosntructeur

	ZombieType getZombieType() const;

	bool isLootable() const override;

	std::string getZombieTypeAsString() const;
};