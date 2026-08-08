#pragma once

// game
#include "../public/Location.h" // correctif final : virgule interdit ;

// cpp
#include "string"

enum class Region { WESTELIZABETH }; // correctif final : WestElizabeth

enum class Territory { GREATPLAINS, TALLTREES }; // correctif final : GreatPlains, TallTrees

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
    Territory territory; 
    Location location; 
    WeatherCondition weatherCondition;
    bool isAccessible;

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Map(Region region, Territory territory, Location location, WeatherCondition weatherConditions, bool isAccessible); // correctif finale : suppression champs inutile

    Region getRegion() const;
    Territory getTerritory() const;
    Location getLocation() const;
    WeatherCondition getWeatherCondition() const; // remplacement de int et mise au singulier de condition
    bool getIsAccessible() const; // correctif finale : ajoute de la fonction

    std::string getWeatherDescription(WeatherCondition weather);
};