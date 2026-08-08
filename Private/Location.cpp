// game
#include "../Public/Location.h"

// cpp
#include <iostream>

using namespace std;

Location::Location(string name, LocationType locationType, int numberOfSurvivors, InvasionLevel invasionLevel, bool isSafeZone) : name(name), locationType(locationType), numberOfSurvivors(numberOfSurvivors), invasionLevel(invasionLevel), isSafeZone(isSafeZone) {}
// correctif final : mauvaise implementation de Location au lieu de LocationType / ; apres numberOfSurvivors(numberOfSurvivors)

// GET
string Location::getName() const { return name; } // correctif final : oublie de std dans .h cause erreur
LocationType Location::getLocationType() const { return locationType; } // mauvais type Location et mauvais nom de variable location et fonction getLocation
int Location::getNumberOfSurvivors() const { return numberOfSurvivors; }
InvasionLevel Location::getInvasionLevel() const { return invasionLevel; }
bool Location::getIsSafeZone() const { return isSafeZone; }

// SET
void Location::setNumberOfSurvivors(int count) { numberOfSurvivors = count; }
void Location::setInvasionLevel(InvasionLevel level) { invasionLevel = level; }
void Location::setIsSafeZone(bool value) { isSafeZone = value; }

vector<Npc*> Location::getSurvivors() const {
	return survivors;
}

void Location::addSurvivor(Npc* npc) {  // correctif final : oublie de Location::
	survivors.push_back(npc); // correctif final : void donc pas besoin de return
}