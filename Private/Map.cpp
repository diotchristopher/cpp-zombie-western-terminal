// game
#include "../public/Map.h"

// cpp
#include <iostream>

using namespace std;

Map::Map(Region region, Territory territory, Location location, WeatherCondition weatherCondition, bool isAccessible) : region(region), territory(territory), location(location), weatherCondition(weatherCondition), isAccessible(isAccessible) {}
// correctif finale : suppression champs inutile

Region Map::getRegion() const { return region; }
Territory Map::getTerritory() const { return territory; }
Location Map::getLocation() const { return location; }
WeatherCondition Map::getWeatherCondition() const { return weatherCondition; }
bool Map::getIsAccessible() const { return isAccessible; }

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