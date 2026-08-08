// ============================
// Inventory.h
// ============================
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Inventory {
private:
    std::unordered_map<std::string, int> items;

public:
    void addItem(const std::string& itemName, int quantity = 1);
    bool hasItem(const std::string& itemName, int quantity = 1) const;
    bool removeItem(const std::string& itemName, int quantity = 1);
    void printInventory() const;
};

// ============================
// Inventory.cpp
// ============================
#include "../public/Inventory.h"
#include <iostream>

void Inventory::addItem(const std::string& itemName, int quantity) {
    items[itemName] += quantity;
}

bool Inventory::hasItem(const std::string& itemName, int quantity) const {
    auto it = items.find(itemName);
    return it != items.end() && it->second >= quantity;
}

bool Inventory::removeItem(const std::string& itemName, int quantity) {
    if (hasItem(itemName, quantity)) {
        items[itemName] -= quantity;
        if (items[itemName] <= 0) {
            items.erase(itemName);
        }
        return true;
    }
    return false;
}

void Inventory::printInventory() const {
    std::cout << "\nInventaire du joueur :" << std::endl;
    for (const auto& pair : items) {
        std::cout << " - " << pair.first << " x" << pair.second << std::endl;
    }
    if (items.empty()) {
        std::cout << "(Vide)" << std::endl;
    }
}
