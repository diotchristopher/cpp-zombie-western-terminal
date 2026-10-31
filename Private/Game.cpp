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
    player(playerName, 100, 5, true, 20, 100, 0, 10), 
    worldMap(Map::loadDefaultMap()), // ajoute du nouveau systeme
    zoneSystem(&worldMap),
    questSystem(nullptr),
    currentLocation(nullptr)
{ 
    // worldMap.loadDefaultMap(); // enlever l'ancien systeme
    if (worldMap.size() > 0) {
        currentLocation = worldMap.getLocationAt(0);
    }

    questSystem = new QuestSystem(&player);

    cout << "Bienvenue dans Zombie Western " << player.getName() << " !\n";
    srand(static_cast<unsigned>(time(nullptr))); // Pour les zombies aléatoires et tous ce qui est aléatoire
}

Game::~Game() {
    if (questSystem) delete questSystem;
}

void Game::run() { // oublie Game::
    // srand deplacer dans le constructeur, pas besoin ici
    cout << endl;
    cout << "Tu te trouves actuellement à : " << currentLocation->getName() << endl;

    displayMenu();
    while (isRunning) { // remplce true 
        cout << endl;
        cout << "Choix : ";
        int choice = 0;
        if (!(cin >> choice)) { // ajoute de test pour pas bug quand lettres au lieu de nombres
            if (cin.eof()) break;
            cin.clear();
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // recup sur projet de magasin
        cout << endl;
        switch (choice) {
        case 1: handleExplorer(); break;
        case 2: handleResearch(); break;
        case 3: handleMission(); break;
        case 4: isRunning = false; break;
        default:
            cout << "Choix inconnu.\n"; // Unknown choice.
        }
	}

    // questSystem->updateMissions(); // remove this
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
    cout << endl;
    cout << "Choisir une destination (-1 annuler) : ";
    int idx;
    if (!(cin >> idx)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrée invalide.\n";
        return;
    }
    cout << endl;
    if (idx < 0) {
        cout << "Exploration annulée.\n";
        return;
    }
    Location* dest = worldMap.getLocationAt(static_cast<size_t>(idx)); // oublie de static_cast<size_t>
    if (!dest) {
        cout << "Index hors plage.\n";
        return;
    }
    if (dest == currentLocation) {
        cout << "Tu es déjà à " << dest->getName() << ".\n";
        return;
    }

    bool eventHappened = moveToLocation(&player, dest); // remplace moveToLocation(&player, dest);

    // questSystem->tryGenerateMission(dest); // suppr parce que double appel
    
    if (!isRunning) return; // ajoute bloque mission si mort

    Mission* rescue = questSystem->tryGenerateMission(dest);
    if (rescue) {
        questSystem->startMission(rescue);
        runMission(rescue);
    }
    else if (!eventHappened) {
        cout << "Rien à voir ici.\n";
    }
}

void Game::handleResearch() {
    cout << "Tu fouilles la zone...\n";
    lootSystem.HandleLoot(player);
}

void Game::handleMission() { 
    cout << "Missions / Sauvetage :\n";
    if (questSystem == nullptr) {
        cout << "Système de quêtes non initialisé (prototype).\n";
        return;
    }
}

bool Game::moveToLocation(Player* player, Location* location) { // ajout de Player* player, // autre maj, remplace void par bool
    if (!player || !location) {  // erreur ajoute !player || dans update
        cout << "Destination invalide.\n";
        return false;
    }

    bool eventHappened = false;

    cout << "Vous partez de " << (currentLocation ? currentLocation->getName() : "nulle part") << " vers " << location->getName() << "...\n";

    currentLocation = location;

    // gestion rencontre sur la route

    // ajout de l'equipe A dans IFighter : Joueur
    vector<IFighter*> teamA;

    if (player->getHealth() > 0) { // suppr player && apres ajoute !player || dans moveToLocation
        teamA.push_back(player);
    }

    // ajout de l'equipe B dans IFighter : Npc Zombie ou Animals Zombie
    vector<IFighter*> teamB;

    int randomNumber = rand() % 100;

    if (location->getLocationType() == LocationType::FOREST ||
        location->getLocationType() == LocationType::PLAINS ||
        location->getLocationType() == LocationType::FARM)
    {
        if (randomNumber < 50) {
            auto spawnedAnimalsZombie = zoneSystem.spawnAnimalZombies(*location); // auto difficile a trouver
            for (auto* animalsZombie : spawnedAnimalsZombie) {
                if (animalsZombie && animalsZombie->getHealth() > 0) {
                    teamB.push_back(animalsZombie);
                }
            }
        }
    } else if (location->getLocationType() == LocationType::TOWN ||
        location->getLocationType() == LocationType::OUTPOST)
    {
        if (randomNumber < 50) {
            auto spawnedNpcZombie = zoneSystem.spawnNpcZombies(*location);
            for (auto* npcZombie : spawnedNpcZombie) {
                if (npcZombie && npcZombie->getHealth() > 0) {
                    teamB.push_back(npcZombie);
                }
            }
        }
    }

    if (!teamA.empty() && !teamB.empty()) {
        eventHappened = true;
        CombatSystem combat;
        combat.StartCombat(teamA, teamB);

        zoneSystem.cleanupDead();
    }

    if (player->getHealth() <= 0) {
        cout << "Le joueur est mort. Fin du jeu.\n";
        isRunning = false;
        return true;
    }

    cout << "Vous arrivez à " << currentLocation->getName() << ".\n";

    if (location->getIsSafeZone()) { // ajoute strat de survie
        eventHappened = true;
        player->heal(100);
        cout << "Santé du joueur régénérée : " << player->getHealth() << " points.\n";
    }

    // questSystem->autoTriggerMission(currentLocation); remplacer par runMission(...)
    Mission* mission = questSystem->autoTriggerMission(currentLocation);
    if (mission) {
        eventHappened = true;
        runMission(mission);
    }

    return eventHappened;
}

void Game::runMission(Mission* mission) { // ajout pour resoudre un probleme de maj
    while (mission && mission->getIsActive() && !mission->getIsCompleted() && player.getHealth() > 0) {
        mission->update();
    }

    if (player.getHealth() <= 0) {
        cout << "Le joueur est mort. Fin du jeu.\n";
        isRunning = false;
    }
}
