#pragma once

#include <string>
#include <iostream>

using namespace std;

enum class Behavior {
    Floater,
    Mixed,
    Smooth,
    Sinker,
    Dart,
    Unknown
};

enum class Location {
    ForestFarm ,
    Ocean,
    TownRiver, 
    ForestRiver, 
    MountainLake, 
    ForestPond, 
    SecretWoods, 
    Mines, 
    WitchSwamp, 
    Sewers, 
    MutantBugLair, 
    Desert, 
    PirateCove,
    GIPond,  
    GIRiver, 
    GIOcean,
    VolcanoCaldera,
    NightMarket,
    Unknown
};

enum class Season{
    Spring, 
    Summer, 
    Fall, 
    Winter,
    Unknown
};

class EnumHelper {
public:

    EnumHelper(){}

    Location stringToLocation(string str) {
        //"Mutant Bug Lair", "Desert", "Pirate Cove", "Ginger Island Pond", "Ginger Island River", "Ginger Island Ocean", "Volcano Caldera", "Night Market"};

        //remove the spaces and make the string lowercase
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ' ') {
                str.erase(i, 1);
                i--;
            }
            else {
                str[i] = tolower(str[i]);
            }
        }
        if (str == "forestfarm")            { return Location::ForestFarm; }
        if (str == "ocean")                 { return Location::Ocean; }
        if (str == "townriver")             { return Location::TownRiver; }
        if (str == "forestriver")           { return Location::ForestRiver; }
        if (str == "mountainlake")          { return Location::MountainLake; }
        if (str == "forestpond")            { return Location::ForestPond; }
        if (str == "secretwoods")           { return Location::SecretWoods; }
        if (str == "mines")                 { return Location::Mines; }
        if (str == "sewers")                { return Location::Sewers; }
        if (str == "mutantbuglair")         { return Location::MutantBugLair; }
        if (str == "desert")                { return Location::Desert; }
        if (str == "piratecove")            { return Location::PirateCove; }
        if (str == "witchswamp" || str == "witch'sswamp")       { return Location::WitchSwamp; }
        if (str == "gipond"     || str == "gingerislandpond")   { return Location::GIPond; }
        if (str == "giriver"    || str == "gingerislandriver")  { return Location::GIRiver; }
        if (str == "giocean"    || str == "gingerislandocean")  { return Location::GIOcean; }
        if (str == "volcanocaldera") { return Location::VolcanoCaldera; }
        if (str == "nightmarket") { return Location::NightMarket; }
        cout << "Error parsing string to location enum. (" << str << ")\n";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return Location::Unknown;
    }
    //Transforms the location in the argument into a string.
    //Location - the location to be transformed. 
    string locationToString(Location loc) {
        if (loc == Location::ForestFarm) { return "Forest Farm"; } 
        if (loc == Location::Ocean) { return "Ocean"; }
        if (loc == Location::TownRiver) { return "Town River"; }
        if (loc == Location::ForestRiver) { return "Forest River"; }
        if (loc == Location::MountainLake) { return "Mountain Lake"; }
        if (loc == Location::ForestPond) { return "Forest Pond"; }
        if (loc == Location::SecretWoods) { return "Secret Woods"; }
        if (loc == Location::Mines) { return "Mines"; }
        if (loc == Location::WitchSwamp) { return "Witch's Swamp"; }
        if (loc == Location::Sewers) { return "The Sewers"; }
        if (loc == Location::MutantBugLair) { return "Mutant Bug Lair"; }
        if (loc == Location::Desert) { return "The Desert"; }
        if (loc == Location::PirateCove) { return "Pirate Cove"; }
        if (loc == Location::GIPond) { return "Ginger Island Pond"; }
        if (loc == Location::GIRiver) { return "Ginger Island River"; }
        if (loc == Location::GIOcean) { return "Ginger Island Ocean"; }
        if (loc == Location::VolcanoCaldera) { return "Volcano Caldera"; }
        if (loc == Location::NightMarket) { return "Night Market"; }
        cout << "Error parsing location enum to string.";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return "Unknown";
    }

    Season stringToSeason(string str) {
        if (str == "Spring") { return Season::Spring; }
        if (str == "Summer") { return Season::Summer; }
        if (str == "Fall") { return Season::Fall; }
        if (str == "Winter") { return Season::Winter; }
        cout << "Error parsing string to season enum. (" << str << ")\n";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return Season::Unknown;
    }
    //Transforms the season in the argument into a string.
    //Season - the season to be transformed. 
    string seasonToString(Season season) {
        if(season == Season::Spring) { return "Spring"; }
        if(season == Season::Summer) { return "Summer"; }
        if(season == Season::Fall) { return "Fall"; }
        if(season == Season::Winter) { return "Winter"; }
        cout << "Error parsing season enum to string.";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return "Unknown";
    }

    Behavior  stringToBehavior(string str) {
        if (str == "Floater") { return Behavior::Floater; }
        if (str == "Mixed") { return Behavior::Mixed; }
        if (str == "Smooth") { return Behavior::Smooth; }
        if (str == "Sinker") { return Behavior::Sinker; }
        if (str == "Dart") { return Behavior::Dart; }
        cout << "Error parsing string to behavior enum. (" << str << ")\n";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return Behavior::Unknown;
    }
    //Transforms the behavior in the argument into a string.
    //Behavior - the behavior to be transformed. 
    string behaviorToString(Behavior behavior) {
        if(behavior == Behavior::Floater) { return "Floater"; }
        if(behavior == Behavior::Mixed) { return "Mixed"; }
        if(behavior == Behavior::Smooth) { return "Smooth"; }
        if(behavior == Behavior::Sinker) { return "Sinker"; }
        if(behavior == Behavior::Dart) { return "Dart"; }
        cout << "Error parsing behavior enum to string.";
        cout << "\nWaiting for key...\n";
        cin.ignore();
        return "Unknown";
    }
};