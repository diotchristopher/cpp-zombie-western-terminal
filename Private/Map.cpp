// game
#include "../public/Map.h"

// cpp
#include <iostream>

using namespace std;

Map::Map(Region region, WeatherCondition weatherCondition, bool isAccessible, const vector<Location>& locations) : // oublie de const
    region(region), weatherCondition(weatherCondition), isAccessible(isAccessible), locations(locations) {} // enlever territory
// correctif finale : suppression champs inutile

Region Map::getRegion() const { return region; }
// Location Map::getLocation() const { return location; } // remplacement plus utile
WeatherCondition Map::getWeatherCondition() const { return weatherCondition; }
bool Map::getIsAccessible() const { return isAccessible; }
const vector<Location>& Map::getLocations() const { return locations; }

string Map::getWeatherDescription(WeatherCondition weather) {
    switch (weather) {
    case WeatherCondition::CLEAR:
        return "Le temps est clair et calme. Ça n'arrive pas souvent.";
    case WeatherCondition::FOGGY:
        return "Un épais brouillard empêche de voir à plus de dix mètres. Un zombie peut venir de n'importe où.";
    case WeatherCondition::NIGHT_FOG:
        return "La nuit est tombée avec un épais brouillard.";
    case WeatherCondition::RAINY:
        return "La pluie tombe tellement fort. On entend les pas des zombies arriver sur l'eau.";
    case WeatherCondition::STORMY:
        return "Un orage violent fait rage. Les eleclaires illumine les silouhette";
    case WeatherCondition::WINDY:
        return "Le vent souffle à travers les arbres. On apercoit quelque chose bouger dans l'ombre.";
    case WeatherCondition::SNOWY:
        return "LA neige tombe, mais le froid n'empeche pas les mort vivant d'attaquer";
    default:
        return "Conditions météorologiques inconnues.";
    }
} // correctif finale : oublie de }

Map Map::loadDefaultMap() {
    vector<Location> locations; // oublie de cette ligne de ce vector

    // GREAT PLAINS
    locations.emplace_back("William's Hope", LocationType::FARM, 5, InvasionLevel::SAFE, Territory::GREAT_PLAINS, true);
    locations.emplace_back("Sweetwater", LocationType::TOWN, 15, InvasionLevel::INFESTED, Territory::GREAT_PLAINS, false);
    locations.emplace_back("Sweetwater Cimetery", LocationType::CEMETERY, 15, InvasionLevel::INFESTED, Territory::GREAT_PLAINS, false);
    locations.emplace_back("Fletcher's Ranch", LocationType::FARM, 10, InvasionLevel::THREATENED, Territory::GREAT_PLAINS, false);
    locations.emplace_back("Great Flats", LocationType::PLAINS, 10, InvasionLevel::THREATENED, Territory::GREAT_PLAINS, false);
    locations.emplace_back("Great Flats Road", LocationType::ROAD, 10, InvasionLevel::THREATENED, Territory::GREAT_PLAINS, false);

    // TALL TREES
    locations.emplace_back("Deadwood Post", LocationType::OUTPOST, 8, InvasionLevel::THREATENED, Territory::TALL_TREES, false);
    locations.emplace_back("Elk Basin", LocationType::CAMP, 0, InvasionLevel::SAFE, Territory::TALL_TREES, false);
    locations.emplace_back("Lobo Road", LocationType::ROAD, 0, InvasionLevel::SAFE, Territory::TALL_TREES, false);
    locations.emplace_back("Bear Falls", LocationType::FOREST, 0, InvasionLevel::SAFE, Territory::TALL_TREES, false);

    return Map(Region::WEST_ELIZABETH, WeatherCondition::CLEAR, true, locations);
}

const Location* Map::findLocationByName(const std::string& name) const { // oublie de Map:: et la reference &
    for (auto& location : locations) {
        if (location.getName() == name) return &location;
    }
    return nullptr;
}

vector<const Location*> Map::getLocationByTerritorry(Territory territory) const {
    std::vector<const Location*> result;
    for (const auto& loc : locations) {
        if (loc.getTerritory() == territory)
            result.push_back(&loc);
    }
    return result;
}

Location* Map::getLocationAt(size_t index) {
    if (index >= locations.size()) return nullptr;
    return &locations[index];
}

size_t Map::size() const { return locations.size(); }