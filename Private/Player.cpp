// game
#include "../public/Player.h"

// cpp
#include <iostream>

using namespace std;

Player::Player(string name, int health, int speed, bool gender, int strength, int stamina, int deadEyes, int ammo) : Character(name, health, speed, gender, strength), stamina(stamina), deadEyes(deadEyes), ammo(ammo) {}
// oublie de ammo
int Player::getStamina() const { return stamina; } // oublie de Player::
int Player::getDeadEyes() const { return deadEyes; }

int Player::getAmmo() const { return ammo; }
void Player::addAmmo(int amount) { ammo += amount; }

int Player::getMoney() const { return money; }
void Player::addMoney(int amount) { money += amount; }

int Player::getReputation() const { return reputation; }
void Player::addReputation(int amount) { reputation += amount; }

bool Player::isPlayerControlled() const { return true; }


void Player::heal(int amount) { // oublie de Player:: et oublie de amount
	takeDamage(-amount);
	if (health > 100) { health = 100; } // ajoute limite a 100, la vie du joueur
}

void Player::useStamina() {
	if (stamina > 5) {
		stamina -= 5;
	}
}

void Player::useDeadEyes() {
	if (deadEyes > 5) {
		deadEyes -= 5;
	}
}

void Player::rechargeDeadEye(int amount) {
	deadEyes += amount;
	if (deadEyes > 100) { // erreur amount au lieu de deadEyes
		deadEyes = 100;
	}
}

/*
void Character::performAttack(Character* target) {
	if (target != nullptr) { // oublie nullptr
		target->takeDamage(getStrength());
	}
}
*/