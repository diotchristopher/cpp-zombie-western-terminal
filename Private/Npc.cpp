// game
#include "../public/Npc.h"

// cpp
#include <iostream>

using namespace std;

Npc::Npc(string name, int health, int speed, bool gender, int strength, Role role, bool isMilitia)
    : Character(name, health, speed, gender, strength), role(role), isMilitia(isMilitia) {
}

Role Npc::getRole() const { return role; }

bool Npc::getIsMilitia() const { return isMilitia; }

string Npc::getRoleAsString() {
    switch (role) {
    case Role::SHERIFF: return "Shérif";
    case Role::BANDIT: return "Bandit";
    case Role::PROSTITUTE: return "Prostituer";
    case Role::MERCHANT: return "Marchand";
    case Role::FARMER: return "Fermier";
    case Role::CITIZEN: return "Citoyen";
    case Role::PRIEST: return "Prêtre";
    case Role::DOCTOR: return "Docteur";
    default: return "Citoyen";
    }
}