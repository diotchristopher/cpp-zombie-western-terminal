// game
#include "../Public/Location.h"
#include "../public/Npc.h"

// cpp
#include <iostream>
#include <sstream>

using namespace std;

Location::Location(string& name, LocationType locationType, int numberOfSurvivors, InvasionLevel invasionLevel, Territory territory, bool isSafeZone) : name(name), locationType(locationType), numberOfSurvivors(numberOfSurvivors), invasionLevel(invasionLevel), territory(territory), isSafeZone(isSafeZone) {}
// correctif final : mauvaise implementation de Location au lieu de LocationType / ; apres numberOfSurvivors(numberOfSurvivors)

// GET
const string& Location::getName() const { return name; } // correctif final : oublie de std dans .h cause erreur
LocationType Location::getLocationType() const { return locationType; } // mauvais type Location et mauvais nom de variable location et fonction getLocation
int Location::getNumberOfSurvivors() const { return numberOfSurvivors; }
InvasionLevel Location::getInvasionLevel() const { return invasionLevel; }
Territory Location::getTerritory() const { return territory; }
bool Location::getIsSafeZone() const { return isSafeZone; }

// SET
void Location::setInvasionLevel(InvasionLevel level) { invasionLevel = level; }
/* // inutile
void Location::setNumberOfSurvivors(int count) { numberOfSurvivors = count; }
void Location::setIsSafeZone(bool value) { isSafeZone = value; }
*/

vector<Npc*> Location::getSurvivors() const {
	return survivors;
}

void Location::addSurvivor(Npc* npc) {  // correctif final : oublie de Location::
	survivors.push_back(npc); // correctif final : void donc pas besoin de return
}

string Location::toString() const {
    ostringstream ss;
    ss << name << " (";
    switch (locationType) {
    case LocationType::TOWN: ss << "Town"; break;
    case LocationType::OUTPOST: ss << "Outpost"; break;
    case LocationType::ROAD: ss << "Road"; break;
    case LocationType::FARM: ss << "Farm"; break;
    case LocationType::FOREST: ss << "Forest"; break;
    }
    // ss << ") - Survivors: " << survivors;
    ss << " - Invasion: ";
    switch (invasionLevel) {
    case InvasionLevel::SAFE: ss << "SAFE"; break;
    case InvasionLevel::THREATENED: ss << "THREATENED"; break;
    case InvasionLevel::INFESTED: ss << "INFESTED"; break;
    }
    if (isSafeZone) ss << " - SAFE ZONE";
    return ss.str();
}