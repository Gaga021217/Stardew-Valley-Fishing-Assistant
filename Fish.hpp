#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Enums.hpp"


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

using namespace std;

class Fish {
public:
    string getName() { 
        return Name; 
    }
    string getDescription() { 
        return Description; 
    }
    string getPrice(double fisher) { 
        string str = "";
        str.append("Normal: ");
        str.append(to_string(int(floor(Price[0] * fisher))));
        str.append("\n\t\tSilver: ");
        str.append(to_string(int(floor(Price[1] * fisher))));
        str.append("\n\t\tGold: ");
        str.append(to_string(int(floor(Price[2] * fisher))));
        str.append("\n\t\tIridium: ");
        str.append(to_string(int(floor(Price[3] * fisher))));
        return str;
        
    }
    string getLocations() { 
        string str = "";
        for (int i = 0; i < Locations.size(); i++) {
            str.append(locationToString(Locations[i]));
            if (i != Locations.size() - 1) {
                str.append(", ");
            }
        }
        

        return str;
    }
    string getAvailableTime() {
        string str = "";
        if(StartTime == 6 && EndTime == 26) {
            str.append("All Day");
            return str;
        }
        str.append(to_string(StartTime));
        str.append(" - ");
        if(EndTime == 26) {
            str.append("2");
        } else if(EndTime == 25) {
            str.append("1");
        } else if(EndTime == 24) {
            str.append("0");
        }else {
            str.append(to_string(EndTime));
        }
        return str;
    }
    string getSeasons() { 
        string str = "";
        if(Seasons.size() == 4) {
            str.append("All Seasons");
            return str;
        }
        for (int i = 0; i < Seasons.size(); i++) {
            str.append(seasonToString(Seasons[i]));
            if (i != Seasons.size() - 1) {
                str.append(", ");
            }
        }
        return str;
    }
    string getWeathers() { 
        string str = "";
        if (Rain && !Sun) {
            str.append("Rainy");
            return str;
        }
        if (!Rain && Sun) {
            str.append("Sunny");
            return str;
        }
        str.append("Any Weather");

        return str;
    }
    string getSizeRange() { 
        string str = "";
        str.append(to_string(MinSize));
        str.append(" - ");
        str.append(to_string(MaxSize));
        return str;
    }
    string getDifficulty() {
        string str = "";
        str.append(to_string(Difficulty));
        str.append(" ");
        str.append(behaviorToString(Behave));
        return str;
    }
    int getXP() { 
        return XP; 
    }
    string getUsedIn() { 
        string str = "";
        for (int i = 0; i < UsedIn.size(); i++) {
            str.append(UsedIn[i]);
            if (i != UsedIn.size() - 1) {
                str.append(", ");
            }
        }
        return str;
    }

    bool isAvailable(Season season) {
        for (int i = 0; i < Seasons.size(); i++) {
            if(Seasons[i] == season) {
                return true;
            }
        }
        return false;
    }

    bool isAvailable(Location loc) {
        for (int i = 0; i < Locations.size(); i++) {
            if(Locations[i] == loc) {
                return true;
            }
        }
        return false;
    }

    bool isAvailable(bool rain, bool sun) {
        if(Rain == rain || Sun == sun) {
            return true;
        }
        return false;
    }

    bool isAvailable(int time) {
        if(time < 6 || time > 26) {
            return true;
        }
        if(StartTime == 6 && EndTime == 26) {
            return true;
        }
        if(time >= StartTime && time < EndTime) {
            return true;
        }

        return false;
    }



    void printFish() {
        string str;
        str.append("\n---------------------------------------------\nName: ");
        str.append(getName());
        str.append("\nCatch between: ");
        str.append(getAvailableTime());
        str.append("\nIn weathers: ");
        str.append(getWeathers());
            
        str.append("\nLocations:");
        str.append(getLocations());
        
        str.append("\nIn season: ");
        str.append(getSeasons());

        if(SpecialSeasons.size() != 0) {
            str.append("\nOr, catch at ");
            str.append(locationToString(SpecialLocation));
            str.append(" in ");
            if(SpecialSeasons.size() == 4) {
                str.append("any season.");
            }
            else {
                for (int i = 0; i < SpecialSeasons.size(); i++) {
                    str.append(seasonToString(SpecialSeasons[i]));
                    if (i != Seasons.size() - 1) {
                        str.append(", ");
                    }
                }
            }
        }
         
        str.append("\nDifficulty: ");
        str.append(getDifficulty());
        str.append("\nYou can use it for: ");
        str.append(getUsedIn());
        str.append("\n---------------------------------------------\n");
        cout << str;
    }

    void printFishAllDetails(double fisher) {
        string str;
        cout << "\n---------------------------------------------\n";
        cout << YELLOW << "Name:\t\t" << RESET << getName()  << endl;
        cout << YELLOW << "Description:\t" << RESET << getDescription() << endl;
        cout << YELLOW << "Price:\t\t" << RESET << getPrice(fisher) << endl;
        cout << YELLOW << "Catch between:\t" << RESET << getAvailableTime() << endl;
        cout << YELLOW << "In weathers:\t" << RESET << getWeathers() << endl;
        cout << YELLOW << "Locations:\t" << RESET << getLocations() << endl;
        cout << YELLOW << "In season:\t" << RESET << getSeasons() << endl;


        if(SpecialLocation != Location::Unknown) {
            cout << YELLOW << "Or, catch at\t" << RESET << locationToString(SpecialLocation) << " in ";
            if(SpecialSeasons.size() == 4) {
                cout << "any season." << endl;
            }
            else {
                for (int i = 0; i < SpecialSeasons.size(); i++) {
                    cout << seasonToString(SpecialSeasons[i]);
                    if (i != Seasons.size() - 1) {
                        cout << ", " << endl;
                    }
                }
            }
        }
        
        cout << YELLOW << "Size:\t\t" << RESET << getSizeRange() << endl;
        cout << YELLOW << "Difficulty:\t" << RESET << getDifficulty() << endl;
        cout << YELLOW << "XP:\t\t" << RESET << getXP() << endl;
        cout << YELLOW << "Use it for:\t" << RESET << getUsedIn() << endl;
        cout << "---------------------------------------------\n";
    }

    Fish(string name, string description, vector<int> price, vector<Location> locations, int startTime, int endTime, vector<Season> seasons, vector<Season> specialSeasons, Location specialLocation, bool rain, bool sun, int minSize, int maxSize, int difficulty, Behavior behave, int xp, vector<string> usedIn) {
            Name = name;
            Description = description;
            Price = price;
            Locations = locations;
            StartTime = startTime;
            EndTime = endTime;
            Seasons = seasons;
            SpecialSeasons = specialSeasons;
            SpecialLocation = specialLocation;
            Rain = rain;
            Sun = sun;
            MinSize = minSize;
            MaxSize = maxSize;
            Difficulty = difficulty;
            Behave = behave;
            XP = xp;
            UsedIn = usedIn;
        }

private:
    string Name;   //name of the fish
    string Description; //description of the fish
    vector<int> Price; //prices of the fish in order: Basic, Silver, Gold, Iridium
    vector<Location> Locations; //locations where the fish can be caught
    int StartTime; //start time of when the fish can be caught
    int EndTime; //end time of when the fish can be caught
    vector<Season> Seasons; //seasons when the fish is available
    vector<Season> SpecialSeasons; //special seasons when the fish is available
    Location SpecialLocation; //special location where the fish is available
    bool Rain; // whether you can catch it in rainy weather
    bool Sun; // whether you can catch it in sunny weather
    int MinSize; //minimum size of the fish
    int MaxSize; //maximum size of the fish
    int Difficulty; //difficulty of the fish
    Behavior Behave; //behavior type of the fish
    int XP; //experience points for catching the fish
    vector<string> UsedIn; //what recipes the fish is used in


    string locationToString(Location loc) {
        string str = "";
        switch (loc)
        {
            case Location::ForestFarm:
                return "Forest Farm";
                break;
            case Location::Ocean:
                return "Ocean";
                break;
            case Location::CindersapForestPond:
                return "Cindersap Forest Pond";
                break;
            case Location::TownRiver:
                return "Town River";
                break;
            case Location::ForestRiver:
                return "Forest River";
                break;
            case Location::MountainLake:
                return "Mountain Lake";
                break;
            case Location::ForestPond: 
                return "Forest Pond";
                break;
            case Location::SecretWoods:
                return "Secret Woods";
                break;
            case Location::Mines:
                return "Mines";
                break; 
            case Location::WitchSwamp:
                return "Witch Swamp";
                break; 
            case Location::Sewers:
                return "The Sewers";
                break;
            case Location::MutantBugLair:
                return "Mutant Bug Lair";
                break;
            case Location::Desert:
                return "The Desert";
                break;
            case Location::PirateCove:
                return "Pirate Cove";
                break;
            case Location::GIPond:
                return "Ginger Island Pond";
                break;
            case Location::GIRiver:
                return "Ginger Island River";
                break;
            case Location::GIOcean:
                return "Ginger Island Ocean";
                break;
            case Location::VolcanoCaldera:
                return "Volcano Caldera";
                break;
            case Location::NightMarket:
                return "Night Market";
                break;
            default:
                return "Unknown";
                break;
        }
        return str;
    }

    string seasonToString(Season season) {
        string str = "";
        switch (season)
        {
            case Season::Spring:
                return "Spring";
                break;
            case Season::Summer:
                return "Summer";
                break;
            case Season::Fall:
                return "Fall";
                break;
            case Season::Winter:
                return "Winter";
                break;
            default:
                return "Unknown";
                break;
        }
        return str;
    }

    string behaviorToString(Behavior behavior) {
        string str = "";
        switch (behavior)
        {
            case Behavior::Floater:
                return "Floater";
                break;
            case Behavior::Mixed:
                return "Mixed";
                break;
            case Behavior::Smooth:
                return "Smooth";
                break;
            case Behavior::Sinker:
                return "Sinker";
                break;
            case Behavior::Dart:
                return "Dart";
                break;
            default:
                return "Unkown";
                break;
        }
    }



};