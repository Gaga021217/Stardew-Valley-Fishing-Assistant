#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Fish.hpp"

using namespace std;

class FishReader {
public:
    FishReader() {}

    vector<Fish> getFishList(string path) {
        ifstream file;

        vector<Fish> fishList;

        file.open(path);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return fishList;
        }

        string line;
        while (getline(file, line)) {
            Fish fsh = readFish(line);
            fishList.push_back(fsh);
        }

        file.close();


        return fishList;
    }

private:
    EnumHelper eh;
    
    Fish readFish(string line) {
        
        //Pufferfish;Inflates when threatened.;200,250,300,400;Ocean,GIOcean;;12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        string name = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);


        //Inflates when threatened.;200,250,300,400;Ocean,GIOcean;;12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        string description = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);

        //200,250,300,400;Ocean,GIOcean;;12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<int> price;
        string temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos) {
            price.push_back(stoi(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }

        //Ocean,GIOcean;;12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<Location> locations;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos) {
            locations.push_back(eh.stringToLocation(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }

        //;12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        string note = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);

        //12;16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<int> startTime;
        temp = line.substr(0, line.find(";"));
        temp.append(",");
        while(temp.find(',') != string::npos) {
            startTime.push_back(stoi(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        line = line.substr(line.find(";") + 1);

        //16;Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<int> endTime;
        temp = line.substr(0, line.find(";"));
        temp.append(",");
        while(temp.find(',') != string::npos) {
            endTime.push_back(stoi(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        line = line.substr(line.find(";") + 1);

        //Summer;true;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<Season> seasons;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != string::npos) {
            seasons.push_back(eh.stringToSeason(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }

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
        int minLength = 0;
        minLength = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);

        //37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        int maxLength = 0;
        maxLength = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);

        //80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        int difficulty = 0;
        difficulty = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);

        //Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        Behavior behavior = eh.stringToBehavior(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);

        //29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        int XP = 0;
        XP = stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);

        //Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        vector<string> usedIn;
        while (line[0] != '\r') {
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
            note,
            startTime,
            endTime,
            seasons,
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

};