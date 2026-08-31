#pragma once

// game
#include "../public/Player.h" // correctif final : virgule interdit ;
#include "../public/Location.h"
#include "../public/Mission.h" // correctif final : virgule interdit ;
#include "../public/MissionRescue.h"
#include "../public/MissionCemetery.h"
#include "../public/MissionDefense.h"
#include "../public/MissionAmbush.h"

// cpp
#include <string>
#include <vector>
#include <algorithm>

struct MissionList {
	LocationType locationType;
	MissionType missionType;
	std::string title;
	// plus besoin de int waveCount; int currentWave; int waveRemaining; int zombiesPerWave; 
};

class QuestSystem {
private:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	Player* player;
	std::vector<MissionList> availableMission;
	std::vector<Mission*> activeMissions;

public:
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	QuestSystem(Player* player); // remplacer le pointer de player par une reference et ajouter &
	// enlever vector<Mission*>& activeMissions, ce vector dois etre gerer en interne

	Player* getPlayer() const;
	// vector<Mission*> getActiveMissions() const; // fonction inutile

	void loadMissons();
	//void generateMission(Player* player, Location* location);
	void startMission(Mission* mission);
	void updateMissions();

	Mission* tryGenerateMission(Location* to);
	Mission* autoTriggerMission(Location* loc);
};