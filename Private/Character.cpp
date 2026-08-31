// game
#include "../public/Character.h"

// cpp
#include <iostream>

using namespace std;

Character::Character(string name, int health, int speed, bool gender, int strength) : name(name), health(health), speed(speed), gender(gender), strength(strength) {}

string Character::getName() const { return name; }
int Character::getHealth() const { return health; }
int Character::getSpeed() const { return speed; }
bool Character::getGender() const { return gender;  }
int Character::getStrength() const { return strength; }

bool Character::isAlive() const { // oublie de Character::
	return health > 0;
}

bool Character::isPlayerControlled() const { // oublie de Character::
	return false;
}

bool Character::isLootable() const {
	return false;
}

void Character::takeDamage(int damage) {
	health -= damage;
	if (health < 0) { health = 0; }
}

void Character::performAttack(IFighter* target) { // oublie de remplacer Character* target
	if (target != nullptr) { // oublie nullptr
		target->takeDamage(getStrength()); // erreur parce que oublie d'indiquer la porte dans IFighter
	}
}