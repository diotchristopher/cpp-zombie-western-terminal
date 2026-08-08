#pragma once

// game
#include "../public/Player.h" // correctif final : virgule interdit ;
#include "../public/Mission.h" // correctif final : virgule interdit ;
#include "../public/MissionRescue.h"

// cpp
#include <string>
#include <vector>
#include <algorithm>

struct MissionList {
	LocationType locationType; // mauvais appelle Location* targetLocation; 
	MissionType missionType;
	std::string title;
	int waveCount; 
	int currentWave;
	int waveRemaining; 
	int zombiesPerWave; 
};

class QuestSystem {
private:
	//======================================================================================
	// PROPERTIES & VARIABLES
	//======================================================================================
	Player* player;
	std::vector<MissionList> availableMission; // oublie de std et pointer * en trop, enlever
	std::vector<Mission*> activeMission; // oublie de std

public:
	//======================================================================================
	// FUNCTIONS
	//======================================================================================
	QuestSystem(Player* player); // remplacer le pointer de player par une reference et ajouter &
	// enlever vector<Mission*>& activeMissions, ce vector dois etre gerer en interne

	Player* getPlayer() const;
	// vector<Mission*> getActiveMissions() const; // fonction inutile

	void loadMissons();
	void generateMission(Player* player, Location* location);
	void startMission(Mission* mission);
	void updateMissions();
};