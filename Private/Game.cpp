// game
#include "../public/Game.h"

// cpp
#include <iostream>
#include <limits> // oublie 
#include <cstdlib> // oublie 
#include <ctime> // oublie 

using namespace std;

Game::Game(const std::string& playerName) 
    : isRunning(true),  // initialise les valeur des la construction
    player(playerName, 100, 5, true, 5, 100, 0, 10), 
    worldMap(Map::loadDefaultMap()), // ajoute du nouveau systeme
    zoneSystem(&worldMap),
    questSystem(nullptr),
    currentLocation(nullptr)
{ 
    // worldMap.loadDefaultMap(); // enlever l'ancien systeme
    if (worldMap.size() > 0) {
        currentLocation = worldMap.getLocationAt(0);
    }

    cout << "Bienvenue dans WestWorld " << player.getName() << "!\n";
    srand(static_cast<unsigned>(time(nullptr))); // Pour les zombies aléatoires et tous ce qui est aléatoire
}

Game::~Game() {
    if (questSystem) delete questSystem;
}

void Game::run() { // oublie Game::
    // srand deplacer dans le constructeur, pas besoin ici
	while (true) {
        displayMenu();

        cout << "Choix : ";
        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // recup sur projet de magasin

        switch (choice) {
        case 1: handleExplorer(); break;
        case 2: handleResearch(); break;
        case 3: handleMission(); break;
        case 4: isRunning = false; break;
        default:
            cout << "Unknown choice.\n";
        }
	}

    /* 
    while (isRunning) {
        printMainMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Entrée invalide.\n";
            continue;
        }
        switch (choice) {
            case 1: handleExplore(); break;
            case 2: handleResearch(); break;
            case 3: handleMissions(); break;
            case 4:
                std::cout << "Statut: " << player.getName() << " - PV: " << player.getHealth()
                          << " - Stamina: " << player.getStamina() << " - DeadEyes: " << player.getDeadEyes()
                          << " - Ammo: " << player.getAmmo() << "\n";
                break;
            case 0:
                isRunning = false;
                break;
            default:
                std::cout << "Choix inconnu.\n";
        }
    }
    std::cout << "Au revoir.\n";
    */
}

void Game::displayMenu() {
    cout << "\n-- Menu principal --\n";
    cout << "1. Explorer\n";
    cout << "2. Fouiller la zone\n";
    cout << "3. Quêtes\n";
    cout << "4. Quitter\n";
}

void Game::handleExplorer() {
    cout << "\n--- Lieux disponibles ---\n";
    const auto& locs = worldMap.getLocations();
    for (size_t i = 0; i < locs.size(); i++) {
        cout << i << ") " << locs[i].toString() << "\n";
    }
    cout << "Choisir index de destination (-1 annuler) : ";
    int idx;
    if (!(cin >> idx)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrée invalide.\n";
        return;
    }
    if (idx < 0) {
        cout << "Exploration annulée.\n";
        return;
    }
    Location* dest = worldMap.getLocationAt(static_cast<size_t>(idx)); // oublie de static_cast<size_t>
    if (!dest) {
        cout << "Index hors plage.\n";
        return;
    }
    moveToLocation(dest);
}

void Game::handleResearch() {
    cout << "Tu fouille la zone...\n";
    lootSystem.HandleLoot(player);
}

void Game::handleMission() { 
    cout << "Missions / Sauvetage :\n";
    if (questSystem == nullptr) {
        cout << "Système de quêtes non initialisé (prototype).\n";
        return;
    }
}

void Game::moveToLocation(Location* location) {
    if (!location) {
        cout << "Destination invalide.\n";
        return;
    }

    cout << "Vous partez de " << (currentLocation ? currentLocation->getName() : "nulle part") << " vers " << location->getName() << "...\n";

    // gestion rencontre sur la route
    vector<Character*> enemies = zoneSystem.spawnZombiesForRoute(*currentLocation, *location);
    if (!enemies.empty()) {
        combatSystem.StartCombat(player, enemies);
        // après combat, nettoyer ennemis alloués
        for (auto e : enemies) delete e;
        enemies.clear();
        // si joueur mort, arrêter
        if (player.getHealth() <= 0) {
            cout << "Le joueur est mort. Fin du jeu.\n";
            isRunning = false;
            return;
        }
    }

    currentLocation = location;
    cout << "Vous arrivez à " << currentLocation->getName() << ".\n";
}