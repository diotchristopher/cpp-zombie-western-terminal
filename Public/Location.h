#pragma once

// game
#include "../public/Npc.h"

// cpp
#include <string> // oublie de include string
#include <vector>
#include <algorithm>

enum class InvasionLevel { INFESTED, THREATENED, SAFE };

enum class LocationType { TOWN, OUTPOST, ROAD, FARM }; // TWON au lieu de TOWN, ajout de FARM, OTHER, enlever


class Location { // Class et fichier appeller Location au lieu de 
private: 
    //======================================================================================
    // PROPERTIES & VARIABLES
    //======================================================================================
	std::string name;
	// enlever bool invaded
    LocationType locationType; // oublie de ;
	int numberOfSurvivors; // renommage de survivor
    InvasionLevel invasionLevel;
	// enlever bool loots
	bool isSafeZone;
	// enlever bool isAccessible

    std::vector<Npc*> survivors; // correctif final : oublie de std

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
	Location(std::string name, LocationType locationType, int numberOfSurvivors, InvasionLevel invasionLevel, bool isSafeZone);
    // correctif final : oublie de std a name, cause erreur

    // suppression, ajout et reorganisation
    std::string getName() const; // correctif final : Mauvais type 
    LocationType getLocationType() const; // correctif final : mauvais nom getLocation, au lieu de getLocationType et mauvais type Location au lieu de LocationType
    int getNumberOfSurvivors() const;
    InvasionLevel getInvasionLevel() const;
    bool getIsSafeZone() const;

    void setIsSafeZone(bool value);
    void setInvasionLevel(InvasionLevel level);
    void setNumberOfSurvivors(int count);

    std::vector<Npc*> getSurvivors() const; // utiliser vector au debut ensuite a cause d'erreur remplacer par Npc*, mais npc n'Est pas bon donc remplacer par vector

    void addSurvivor(Npc* npc); // correctif final : doit pas renvoyer de liste, ajoute seulement un élément, donc enlever vector<Npc*>

};