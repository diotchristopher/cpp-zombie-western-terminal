// game
#include "../public/QuestSystem.h"

// cpp
#include <iostream>

using namespace std;

QuestSystem::QuestSystem(Player* player) : player(player) {
	loadMissons(); // oublie d'ajout de loadMissons qui creer directement les missions dont on a besoin
} // enlever vector<Mission*>& activeMissions, activeMissions(activeMissions)

Player* QuestSystem::getPlayer() const {
	return player;
}

/*
vector<Mission*> QuestSystem::getActiveMissions() const {  // fonction inutile
	return activeMissions;
}
*/

void QuestSystem::loadMissons() {
	availableMission = {
		// targetLocation, missionType, title
		{LocationType::ROAD, MissionType::RESCUE, "Sauvetage 1"},
		{LocationType::ROAD, MissionType::RESCUE, "Sauvetage 2"},
	};
}

/*
void QuestSystem::generateMission(Location* location) { // correctif finale: oublie de Player* player (megat dur a trouver)
	Mission* newMission = nullptr;

	for (const auto& mission : availableMission)
	if (mission.locationType == location->getLocationType()) {
		switch (mission.missionType)
		{
		case MissionType::RESCUE:
			newMission = new MissionRescue(player, location, mission.title); // enlever mission.missionType,
			// plus besoin de mission.waveCount, mission.currentWave, mission.waveRemaining, mission.zombiesPerWave,
			break;
		default:
			break;
		}

		if (newMission) break;
	}
	if (newMission) {
		activeMissions.push_back(newMission);
	}
}
*/

Mission* QuestSystem::tryGenerateMission(Location* to) {
	if (!to) {
		return nullptr;
	}


	// generer mission aleatoire en dehors de la ville et des postes avancer
	if (to->getLocationType() == LocationType::TOWN || to->getLocationType() == LocationType::OUTPOST)
		return nullptr;


	int chance = rand() % 100;
	if (chance < 30) {
		Mission* rescue = new MissionRescue(player, to, "Mission de sauvetage"); // ajout en trop MissionType::RESCUE, difficile a trouver
		return rescue;
	}
	return nullptr;
}

Mission* QuestSystem::autoTriggerMission(Location* location) {
	if (!location) {
		return nullptr;
	}

	if (location->getLocationType() == LocationType::CEMETERY) {
		Mission* cemetery = new MissionCemetery(player, location, "Mission de cimetière"); // ajout en trop MissionType::CEMETERY, difficile a trouver
		cemetery->start();
		activeMissions.push_back(cemetery);
		return cemetery;
	}


	if (location->getLocationType() == LocationType::TOWN && 
		(location->getInvasionLevel() == InvasionLevel::INFESTED || location->getInvasionLevel() == InvasionLevel::THREATENED)) {
		Mission* defense = new MissionDefense(this->player, location, "Mission de défense"); // ajout en trop MissionType::DEFENSE, difficile a trouver
		defense->start();
		activeMissions.push_back(defense);
		return defense;
	}

	return nullptr;
}

void QuestSystem::startMission(Mission* mission) {
	if (!mission) return; // oublie
	if (!mission->getIsActive() && !mission->getIsCompleted()) {
		mission->start();
		cout << "Mission démarrée : " << mission->getTitle() << endl;
		activeMissions.push_back(mission); // 
	}
}

void QuestSystem::updateMissions() {
	for (const auto& mission : activeMissions)
	if (mission->getIsActive() && !mission->getIsCompleted()) {
		mission->update();
	}
}
