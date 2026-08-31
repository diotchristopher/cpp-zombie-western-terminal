// game
#include "../public/LootSystem.h"

// cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void LootSystem::HandleLoot(Player& player) {

    // afficher message
    cout << "\nVous fouillez les cadavres..." << endl;
    
    // utiliser fonction de generation de loot
    vector<LootItem> loot = GenerateLoot();

    // parcourrir les loot et envoyer au joueur
    for (const LootItem& item : loot) {
        if (item.name == "Munitions") {
            player.addAmmo(item.quantity);
        }
        else if (item.name == "Stamina") {
            player.heal(item.quantity);
        }
        else if (item.name == "Dead Eyes") {
            // Recharge les Dead Eyes
            int current = player.getDeadEyes();
            player = Player(player.getName(), player.getHealth(), player.getSpeed(), player.getGender(), player.getStrength(), player.getStamina(), current + item.quantity, player.getAmmo()); //  ajoute de player.getAmmo() manquant
        } // std::string name, int health, int speed, bool gender, int strength, int stamina, int deadEyes, int ammo
    }

    DisplayLoot(loot);
}

vector<LootItem> LootSystem::GenerateLoot() {
    srand(static_cast<unsigned int>(time(0))); // ajoute de static_cast<unsigned int> en bonne pratique
    vector<LootItem> loot;

    int randomNumber = rand() % 100;

    if (randomNumber < 50) {
        loot.push_back({ "Munitions", 5 + rand() % 6 }); // oublie de comment faire push_back
    }
    if (randomNumber < 70) {
        loot.push_back({ "Stamina", 10 + rand() % 11 });
    }
    if (randomNumber > 60) {
        loot.push_back({ "Dead Eyes", 5 + rand() % 6 });
    }

    return loot;
}

void LootSystem::DisplayLoot(const vector<LootItem>& loot) {
    cout << "\nVous venez de ramasser :" << endl;
    for (const LootItem& item : loot) {
        cout << " - " << item.name << " x" << item.quantity << endl;
    }
}
