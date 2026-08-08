// game
#include "../public/Player.h"

// cpp
#include <iostream>

using namespace std;

Player::Player(string name, int health, int speed, bool gender, int strength, int stamina, int deadEyes) : Character(name, health, speed, gender, strength), stamina(stamina), deadEyes(deadEyes) {}

int Player::getStamina() const { return stamina; } // oublie de Player::
int Player::getDeadEyes() const { return deadEyes; }

int Player::getAmmo() const { return ammo; }
void Player::AddAmmo(int amount) { ammo += amount; }


void Player::heal(int amount) { // oublie de Player:: et oublie de amount
	takeDamage(-amount);
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
	if (amount > 100) deadEyes = 100;
}