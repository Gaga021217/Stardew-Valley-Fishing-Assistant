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
            str.append(eh.locationToString(Locations[i]));
            if (i != Locations.size() - 1) {
                str.append(", ");
            }
        }


        return str;
    }
    string getNote() {
        return Note;
    }
    string getAvailableTime() {
        string str = "";
        if (StartTime[0] == 6 && EndTime[0] == 26) {
            str.append("All Day");
            return str;
        }
        for (int i = 0; i < StartTime.size(); i++) {
            str.append(to_string(StartTime[i]));
            str.append(".00 - ");
            if (EndTime[i] == 26) {
                str.append("2");
            }
            else if (EndTime[i] == 25) {
                str.append("1");
            }
            else if (EndTime[i] == 24) {
                str.append("0");
            }
            else {
                str.append(to_string(EndTime[i]));
            }
            str.append(".00");
            if (i != StartTime.size() - 1) {
                str.append("; ");
            }

        }
        return str;
    }
    string getSeasons() {
        string str = "";
        if (Seasons.size() == 4) {
            str.append("All Seasons");
            return str;
        }
        for (int i = 0; i < Seasons.size(); i++) {
            str.append(eh.seasonToString(Seasons[i]));
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
        str.append(eh.behaviorToString(Behave));
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

    //Returns whether the fish is available in given season
    bool isAvailable(Season season) {
        for (int i = 0; i < Seasons.size(); i++) {
            if (Seasons[i] == season) {
                return true;
            }
        }
        return false;
    }
    //Returns whether the fish is available at a given location
    bool isAvailable(vector<string> locs) {
        for (int i = 0; i < locs.size(); i++) {
            for (int j = 0; j < Locations.size(); j++) {
                if (eh.stringToLocation(locs[i]) == Locations[j]) {
                    return true;
                }
            }
        }
        return false;
    }
    //Returns whether the fish is available in a given weather
    bool isAvailable(bool rain, bool sun) {
        if (Rain == rain || Sun == sun) {
            return true;
        }
        return false;
    }
    //Returns whether the fish is available at a given time
    bool isAvailable(int time) {
        if (time < 6 || time > 26) {
            return true;
        }
        if (StartTime[0] == 6 && EndTime[0] == 26) {
            return true;
        }
        if (time >= StartTime[0] && time < EndTime[0]) {
            return true;
        }
        if (StartTime.size() > 1) {
            if (time >= StartTime[1] && time < EndTime[1]) {
                return true;
            }
        }

        return false;
    }


    void printFishDetails(vector<string> properties, double fisher) {
        // /*debug*/cout << properties.size();

        string str;
        cout << "\n---------------------------------------------\n";
        cout << YELLOW << "Name:\t\t" << RESET << getName() << endl;
        if (properties[0] == "Description") {
            cout << YELLOW << "Description:\t" << RESET << getDescription() << endl;
            properties.erase(properties.begin());
        }
        if ((properties.size() > 0) && (properties[0] == "Price")) {
            cout << YELLOW << "Price:\t\t" << RESET << getPrice(fisher) << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Locations") {
            cout << YELLOW << "Locations:\t" << RESET << getLocations() << endl;
            properties.erase(properties.begin());
            
        }
        if(Note != "") {
            cout << YELLOW << "Note:\t\t" << RESET << getNote() << endl;
        }
        if (properties[0] == "Time") {
            cout << YELLOW << "Catch between:\t" << RESET << getAvailableTime() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Season") {
            cout << YELLOW << "In season:\t" << RESET << getSeasons() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Weather") {
            cout << YELLOW << "In weathers:\t" << RESET << getWeathers() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Size") {
            cout << YELLOW << "Size:\t\t" << RESET << getSizeRange() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Difficulty") {
            cout << YELLOW << "Difficulty:\t" << RESET << getDifficulty() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "XP") {
            cout << YELLOW << "XP:\t\t" << RESET << getXP() << endl;
            properties.erase(properties.begin());
        }
        if (properties[0] == "Uses") {
            cout << YELLOW << "Use it for:\t" << RESET << getUsedIn() << endl;
            properties.erase(properties.begin());
        }

        cout << "---------------------------------------------\n";
    }





    //Constructor for a fish
    //String - name of the fish.
    //String - description of the fish.
    //Vector<int> - price of the fish, in order: normal, silver, gold, iridium.
    //Vector<Location> - locations where the fish can be caught.
    //Int - When does the fish appear?
    //Int - When does the fish disappear?
    //Vector<Season> Seasons when the fish can be caught
    //Bool - Does this fish have special availability
    //Bool - Can this fish be caught in rainy weather
    //Bool - Can this fish be caught in sunny weather
    //Int - Smallest this fish can be
    //Int - Biggest this fish can be
    //Int - Difficulty level of this fish
    //Behavior - Behavior type of the fish
    //Int - how much XP you gain for catching the fish
    //Vector<string> - uses of the fish
    Fish(string name, string description, vector<int> price, vector<Location> locations, string note, vector<int> startTime, vector<int> endTime, vector<Season> seasons, bool rain, bool sun, int minSize, int maxSize, int difficulty, Behavior behave, int xp, vector<string> usedIn) {
        Name = name;
        Description = description;
        Price = price;
        Locations = locations;
        Note = note;
        StartTime = startTime;
        EndTime = endTime;
        Seasons = seasons;
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
    string Name;   // Name of the fish
    string Description; // Description of the fish
    vector<int> Price; // Prices of the fish in order: Basic, Silver, Gold, Iridium
    vector<Location> Locations; // Locations where the fish can be caught
    string Note; // Note about the fish; might be empty
    vector<int> StartTime; // Start time of when the fish can be caught
    vector<int> EndTime; // End time of when the fish can be caught
    vector<Season> Seasons; // Seasons when the fish is available
    bool Rain; // Whether you can catch it in rainy weather
    bool Sun; // Whether you can catch it in sunny weather
    int MinSize; // Minimum size of the fish
    int MaxSize; // Maximum size of the fish
    int Difficulty; // Difficulty of the fish
    Behavior Behave; // Behavior type of the fish
    int XP; // Experience points for catching the fish
    vector<string> UsedIn; // What recipes the fish is used in

    EnumHelper eh;

};