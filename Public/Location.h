#pragma once

// game
// deplacement de #include "../public/Npc.h" dans le cpp

// cpp
#include <string> // oublie de include string
#include <vector>
#include <algorithm>

class Npc; // accélère la compilation et réduit les dépendances croisées.

enum class LocationType { TOWN, CEMETERY, OUTPOST, ROAD, FARM, FOREST, CAMP, PLAINS }; // TWON au lieu de TOWN, ajout de FARM et FORESET, OTHER, enlever

enum class InvasionLevel { SAFE, THREATENED, INFESTED }; // reorganisation et ajoute de valeur final

enum class Territory { TALL_TREES, GREAT_PLAINS }; // GREAT_PLAINS, TALL_TREES

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
    Territory territory;
	// enlever bool loots
	bool isSafeZone;
	// enlever bool isAccessible

    std::vector<Npc*> survivors; // correctif final : oublie de std

public:
    //======================================================================================
    // FUNCTIONS
    //======================================================================================
    Location(const std::string& name, LocationType locationType, int numberOfSurvivors, InvasionLevel invasionLevel, Territory territory, bool isSafeZone);
    // correctif final : oublie de std a name, cause erreur

    // suppression, ajout et reorganisation
    const std::string& getName() const; // correctif final : Mauvais type + apres oublie de const
    LocationType getLocationType() const; // correctif final : mauvais nom getLocation, au lieu de getLocationType et mauvais type Location au lieu de LocationType
    int getNumberOfSurvivors() const;
    InvasionLevel getInvasionLevel() const;
    Territory getTerritory() const;
    bool getIsSafeZone() const;
    // const char[] transformé en std::string

    void setInvasionLevel(InvasionLevel level);
    /* // inutile
    void setIsSafeZone(bool value);
    void setNumberOfSurvivors(int count);
    */

    std::vector<Npc*> getSurvivors() const; // utiliser vector au debut ensuite a cause d'erreur remplacer par Npc*, mais npc n'Est pas bon donc remplacer par vector

    void addSurvivor(Npc* npc); // correctif final : doit pas renvoyer de liste, ajoute seulement un élément, donc enlever vector<Npc*>

    std::string toString() const;

};