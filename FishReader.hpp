#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "Fish.hpp"

using namespace std;

class FishReader {
public:
    FishReader(string path) {
        path = path;
        readAll();
    }
    
    vector<Fish> getFishList() {
        return fishList;
    }

     
    Location stringToLocation(string str) {
        if(str == "ForestFarm") { return Location::ForestFarm; }
        if(str == "Ocean") { return Location::Ocean; }
        if(str == "CindersapForestPond") { return Location::CindersapForestPond; }
        if(str == "TownRiver") { return Location::TownRiver; }
        if(str == "ForestRiver") { return Location::ForestRiver; }
        if(str == "MountainLake") { return Location::MountainLake; }
        if(str == "ForestPond") { return Location::ForestPond; }
        if(str == "SecretWoods") { return Location::SecretWoods; }
        if(str == "Mines") { return Location::Mines; }
        if(str == "WitchSwamp") { return Location::WitchSwamp; }
        if(str == "Sewers") { return Location::Sewers; }
        if(str == "MutantBugLair") { return Location::MutantBugLair; }
        if(str == "Desert") { return Location::Desert; }
        if(str == "PirateCove") { return Location::PirateCove; }
        if(str == "GIPond") { return Location::GIPond; }
        if(str == "GIRiver") { return Location::GIRiver; }
        if(str == "GIOcean") { return Location::GIOcean; }
        if(str == "VolcanoCaldera") { return Location::VolcanoCaldera; }
        if(str == "NightMarket") { return Location::NightMarket; }
        return Location::Unknown;
    }



    Behavior  stringToBehavior(string str) {
        if(str == "Floater") { return Behavior::Floater; }
        if(str == "Mixed") { return Behavior::Mixed; }
        if(str == "Smooth") { return Behavior::Smooth; }
        if(str == "Sinker") { return Behavior::Sinker; }
        if(str == "Dart") { return Behavior::Dart; }
        return Behavior::Unknown;
    }

    Season stringToSeason(string str) {
        if(str == "Spring") { return Season::Spring; }
        if(str == "Summer") { return Season::Summer; }
        if(str == "Fall") { return Season::Fall; }
        if(str == "Winter") { return Season::Winter; }
        return Season::Unknown;
    }

private:
    string path;
    vector<Fish> fishList;

    Fish readFish(string line) {
        //Pufferfish;Inflates when threatened.;200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        string name = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        //Inflates when threatened.;200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        string description = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        //200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        vector<int> price;
        string temp = line.substr(0, line.find(";"));
        temp.append(",");
        line = line.substr(line.find(";") + 1);
        while(temp.find(',') != string::npos) {
            price.push_back(stoi(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        vector<Location> locations;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos) { 
            locations.push_back(stringToLocation(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int startTime = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int endTime = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        vector<Season> seasons;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos) { 
            seasons.push_back(stringToSeason(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        vector<Season> specialSeasons;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos){
            specialSeasons.push_back(stringToSeason(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        Location specialLocations = stringToLocation(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        bool rain = true;
        bool sun = true;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        if (temp == "Rainy") {
            sun = false;
        }
        if (temp == "Sunny") {
            rain = false;
        }
        //1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int minLength = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int maxLength = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int difficulty = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        Behavior behavior = stringToBehavior(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        
        int XP = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        vector<string> usedIn;
        while(line[0] != '\r') {
            usedIn.push_back(line.substr(0, line.find(";")));
            line = line.substr(line.find(";") + 1);
        }
        //Abigail(Loved);Aquatic Research Quest;
        //Aquatic Research Quest;
        //

        Fish fsh(
            name, 
            description, 
            price, 
            locations, 
            startTime, 
            endTime, 
            seasons, 
            specialSeasons, 
            specialLocations, 
            rain,
            sun, 
            minLength, 
            maxLength, 
            difficulty, 
            behavior, 
            XP, 
            usedIn
        );
        return fsh;
    }

    void readAll() {
        
        ifstream file("fish_database.csv");

        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return; 
        }

        string line;
        while (getline(file, line)) {
            Fish fsh = readFish(line);

            fishList.push_back(fsh);
        }
        
    }
    
};