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
		// targetLocation, missionType, title, waveCount, currentWave, waveRemaining, zombiesPerWave
		{LocationType::ROAD, MissionType::RESCUE, "Sauvetage 1", 3, 1, 3, 8}, // ajoute de trop de {} pour chaque variable
		{LocationType::ROAD, MissionType::RESCUE, "Sauvetage 2", 3, 1, 3, 8},
	};
}

void QuestSystem::generateMission(Player* player, Location* location) { // correctif finale: oublie de Player* player (megat dur a trouver)
	Mission* newMission = nullptr;

	for (const auto& mission : availableMission)
	if (mission.locationType == location->getLocationType()) {
		switch (mission.missionType)
		{
		case MissionType::RESCUE:
			newMission = new MissionRescue(player, location, mission.missionType, mission.title, false, false, mission.waveCount, mission.currentWave, mission.waveRemaining, mission.zombiesPerWave, false);
			// Player* player, Location* targetLocation, MissionType missionType, std::string title, bool isActive, bool isCompleted, int waveCount, int currentWave, int waveRemaining, int zombiesPerWave, bool isRescued
			break;
		default:
			break;
		}

		if (newMission) break; // oublie
	}
	if (newMission) { // oublie de verifier
		activeMission.push_back(newMission);
	}
}

void QuestSystem::startMission(Mission* mission) {
	if (!mission->getIsActive() && !mission->getIsCompleted()) {
		mission->start(); // erreur utilisation de return alors que fonction void
		cout << "Mission démarrée : " << mission->getTitle() << endl;
	}
}

void QuestSystem::updateMissions() {
	for (const auto& mission : activeMission)
	if (mission->getIsActive() && !mission->getIsCompleted()) {
		mission->update(); // erreur utilisation de return alors que fonction void
	}
}