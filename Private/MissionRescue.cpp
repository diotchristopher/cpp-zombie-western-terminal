// game
#include "../public/MissionRescue.h"
#include "../public/IFighter.h"

// cpp
#include <iostream>
#include <algorithm>

using namespace std;

MissionRescue::MissionRescue(Player* player, Location* targetLocation, const string& title) : Mission(player, targetLocation, MissionType::RESCUE, title, false, false),
waveCount(0), currentWave(0), zombiesPerWave(8), 
isRescued(false), missionScenario(MissionRescueScenario::CAMP) {} // enlever int waveRemaining
// enlever MissionType missionType, ..., bool isActive, bool isCompleted, int waveCount, int currentWave, int zombiesPerWave, bool isRescued


int MissionRescue::getWaveCount() const { return waveCount;}
int MissionRescue::getCurrentWave() const { return currentWave;}
int MissionRescue::getZombiesPerWave() const { return zombiesPerWave;}
bool MissionRescue::getIsRescued() const { return isRescued;}


void MissionRescue::start() {
    isActive = true;

    const int survivorsPlanned = rand() % 4;
    // 60% pour une mission de sauvetage classique (plusieurs survivants, vagues de zombies).
    // 30 % pour une embuscade de bandits(un survivant, pas de zombies).
    // 10 % pour un sauvetage simple(un survivant, une vague de zombies).

    if (survivorsPlanned == 1) { // 0 au lieu de 1
        missionScenario = MissionRescueScenario::SOLO;
        waveCount = 1;
        currentWave = 1;

        spawnSoloSurvivor();
        spawnZombiesPerWave(currentWave);

        cout << "Un bruit de cri a l'aide. Un survivants est attaquer." << endl;
        cout << "Objectif : Protégez le survivant !" << endl;
    }
    else {
        const int hostile = rand() % 100;
        if (hostile < 15) {
            missionScenario = MissionRescueScenario::HOSTILE;
            waveCount = 1;
            currentWave = 1;
            zombiesPerWave = 0;

            spawnCampSurvivors(survivorsPlanned);
            int number = rand() % 4;
            spawnHostileBandits(number);

            cout << "Un bruit de cri a l'aide. Un survivants est attaquer." << endl;
        } else {
            missionScenario = MissionRescueScenario::CAMP;
            waveCount = 2;
            currentWave = 1;

            spawnCampSurvivors(survivorsPlanned);
            spawnZombiesPerWave(currentWave);

            cout << "Un bruit de cri a l'aide. " << survivorsPlanned << " survivants sont attaquer." << endl;
            cout << "Objectif : Protégez les survivants !" << endl;
        }
    }
    // enlever ajout de survivant ici, creer des fonctions et permettre le choix ici
}

void MissionRescue::update() {
    if (!isActive || isCompleted) {
        return;
    }

    // ajout de l'equipe A dans IFighter : Joueur et Allie
    vector<IFighter*> teamA;

    if (player && player->getHealth() > 0) {
        teamA.push_back(player);
    }

    for (Npc* survivor : localSurvivors) { // difficultes a trouve le Npc*, pensais a const auto, etc...
        if (survivor && survivor->getHealth() > 0) {
            teamA.push_back(survivor);
        }
    }

    // ajout de l'equipe B dans IFighter : Zombie ou Hostile
    vector<IFighter*> teamB;

    if (missionScenario == MissionRescueScenario::HOSTILE) { // localBandits.empty()
        for (Npc* bandit : localBandits) {
            if (bandit && bandit->getHealth() > 0) {
                teamB.push_back(bandit);
            }
        }
    } else {
        for (NpcZombie* zombie : localZombies) {
            if (zombie && zombie->getHealth() > 0) {
                teamB.push_back(zombie);
            }
        }
    }

    // maj quand survivant mort
    if (teamA.empty()) // remplace localSurvivors.empty()
    {
        cout << "Les survivants sont morts. Mission échouée.\n";
        isActive = false;
        isCompleted = true;
        isRescued = false;
        return;
    }

    // maj quand tous les zombie ou hostile son mort vague suivante, quand tous les vague termine reussie
    if (teamB.empty()) { // remplace localZombies.empty()
        if (currentWave < waveCount) {
            currentWave++;
            spawnZombiesPerWave(currentWave);
        }
    }

    // on combat si il reste des membres dans teamA et dans teamB
    if (!teamA.empty() && !teamB.empty()) {
        CombatSystem combat;
        combat.StartCombat(teamA, teamB);
    }

    // nettoyage des morts
    cleanupDead();


    if (checkCompletion()) {
        cout << "Les survivants ont été sauvés." << endl;
        isCompleted = true;
        isActive = false;
        isRescued = true;
    }
}

bool MissionRescue::checkCompletion() {
    return currentWave == waveCount; // remplace waveRemaining
}

void MissionRescue::giveReward(Player& player) {
    int ammoNumber = rand() % 6;
    player.addAmmo(ammoNumber);
    cout << "+" << player.getAmmo() << " Munitions de revolvers" << endl;
    int moneyNumber = rand() % 15 + 5;
    if (rand() % 100 < 50) {
        player.addMoney(moneyNumber);
        cout << "+$" << player.getMoney() << endl;
    }
    player.addReputation(50);
    cout << "+ Gain d'Honneur" << endl;
}

void MissionRescue::spawnSoloSurvivor() {
    Npc* NpcToRescue;
    NpcToRescue = new Npc(
        "Survivant01",
        80,
        3,
        true,
        5,
        Role::CITIZEN,
        true
        );
    localSurvivors.push_back(NpcToRescue);
}

void MissionRescue::spawnCampSurvivors(int number) {
    int survivorsToAdd = number;
    for (int i = 0; i < survivorsToAdd; i++) {
        Npc* NpcToRescue;
        NpcToRescue = new Npc(
            "Survivant_" + to_string(i + 1),
            100,
            3,
            true,
            1,
            Role::CITIZEN,
            true
        );
        localSurvivors.push_back(NpcToRescue);
        // targetLocation->addSurvivor(NpcToRescue);
    }
    // localSurvivors = targetLocation->getSurvivors(); // erreur : C++ no operator matches these operands parce que fonction getSurvivor pas vector
}

void MissionRescue::spawnHostileBandits(int number) {
    int hostileToAdd = number;
    for (int i = 0; i < hostileToAdd; i++) {
        Npc* NpcToKill;
        NpcToKill = new Npc(
            "Survivant_Hostile_" + to_string(i + 1),
            100,
            3,
            true,
            1,
            Role::BANDIT,
            true
        );
        localBandits.push_back(NpcToKill);
    }
}

void MissionRescue::spawnZombiesPerWave(int currentWave) {
    localZombies.clear();

    int totalZombie = zombiesPerWave + currentWave * 2;

    for (int i = 0; i < totalZombie; i++) {

        int randomNumber = rand() % 100;

        string name = "Zombie";
        int health = 10;
        int speed = 10;
        bool gender = true;
        int strength = 10;
        Role role = Role::CITIZEN;
        ZombieType type = ZombieType::STANDARD;

        if (randomNumber < 50) { // 50%
            name = "Un zombie normal";
            health = 30;
            speed = 2;
            gender = true;
            strength = 10;
            role = Role::CITIZEN;
            type = ZombieType::STANDARD;
        }
        else if (randomNumber < 75) { // 25%
            name = "Un zombie rapide";
            health = 20;
            speed = 5;
            gender = true;
            strength = 7;
            role = Role::FARMER;
            type = ZombieType::RUNNER;
        }
        else if (randomNumber < 90) { // 15%
            name = "Un zombie cracheur";
            health = 25;
            speed = 3;
            gender = true;
            strength = 5;
            role = Role::PROSTITUTE;
            type = ZombieType::SPITTER;
        }
        else { // 10%
            name = "Un zombie brutale";
            health = 40;
            speed = 1;
            gender = true;
            strength = 20;
            role = Role::BANDIT;
            type = ZombieType::BRUTAL;
        }

        localZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}

void MissionRescue::cleanupDead() {
    localSurvivors.erase(
        remove_if(localSurvivors.begin(), localSurvivors.end(), [](Npc* c) { return c->getHealth() <= 0; }),
        localSurvivors.end());
    localZombies.erase(
        remove_if(localZombies.begin(), localZombies.end(), [](NpcZombie* z) { return z->getHealth() <= 0; }),
        localZombies.end());
    localBandits.erase(
        remove_if(localBandits.begin(), localBandits.end(), [](Npc* b) { return b->getHealth() <= 0; }),
        localBandits.end());
}

/*
void MissionRescue::spawnZombies() {
    localZombies.clear();

    int totalZombie = zombiesPerWave + currentWave * 2;

    for (int i = 0; i < totalZombie; i++) {


        int randomNumber = rand() % 100; // renomme aleatoire en randomNumber

        string name = "Zombie";
        int health = 10; // Oublie de declarer avant la boucle les variables pour les utiliser en dehors
        int speed = 10;
        bool gender = true;
        int strength = 10;
        Role role = Role::CITIZEN;
        ZombieType type = ZombieType::STANDARD;

        if (randomNumber < 50) { // 50%
            name = "Un zombie normal";
            health = 30;
            speed = 2;
            gender = true;
            strength = 10;
            role = Role::CITIZEN;
            type = ZombieType::STANDARD;
        }
        else if (randomNumber < 75) { // 25%
            name = "Un zombie rapide";
            health = 20;
            speed = 5;
            gender = true;
            strength = 7;
            role = Role::FARMER;
            type = ZombieType::RUNNER;
        }
        else if (randomNumber < 90) { // 15%
            name = "Un zombie cracheur";
            health = 25;
            speed = 3;
            gender = true;
            strength = 5;
            role = Role::PROSTITUTE;
            type = ZombieType::SPITTER;
        }
        else { // 10%
            name = "Un zombie brutale";
            health = 40;
            speed = 1;
            gender = true;
            strength = 20;
            role = Role::BANDIT;
            type = ZombieType::BRUTAL;
        }

        localZombies.push_back(new NpcZombie(name, health, speed, gender, strength, role, false, type));
    }
}
*/