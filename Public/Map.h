#pragma once

// game
#include "../public/Location.h" // correctif final : virgule interdit ;

// cpp
#include <string> // utilisation de " au lieu de >
#include <vector>

enum class Region { WEST_ELIZABETH }; // correctif final : WestElizabeth

// enum class Territory { GREATPLAINS, TALLTREES }; // correctif final : GreatPlains, TallTrees
// deplacement de Territory dans 
enum class WeatherCondition {
    CLEAR,
    FOGGY,
    RAINY,
    STORMY,
    WINDY,
    SNOWY,
    NIGHT_FOG
};

class Map {
private:
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
    Region region; 
    // Location location; // erreur remplacer location par plusieurs location
    WeatherCondition weatherCondition;
    bool isAccessible;
    std::vector<Location> locations;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Map(Region region, WeatherCondition weatherConditions, bool isAccessible, const std::vector<Location>& locations); // correctif finale : suppression champs inutile

    Region getRegion() const;
    // Territory getTerritory() const; // enlever deplacer dans la derniere version
    // Location getLocation() const; // enlever inutile dans derniere version
    WeatherCondition getWeatherCondition() const; // remplacement de int et mise au singulier de condition
    bool getIsAccessible() const; // correctif finale : ajoute de la fonction
    const std::vector<Location>& getLocations() const;

    static std::string getWeatherDescription(WeatherCondition weather);

    static Map loadDefaultMap();

    // Méthodes utilitaires
    const Location* findLocationByName(const std::string& name) const;  // nullptr si absent
    std::vector<const Location*> getLocationByTerritorry(Territory territory) const;

    // util: get index-safe
    Location* getLocationAt(size_t index);
    size_t size() const;
};