#pragma once

#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>

#include "Fish.hpp"

#define FISHER 1.25
#define ANGLER 1.5

using namespace std;

struct Farmer {
    string name;
    double profession;
    vector<string> detailedOptions;
    vector<string> lessDetailedOptions;
};

class Menu {
public:
    Menu(vector<Fish> fl) { fishList = fl; }
    ~Menu() {}

    
    Farmer Config() {
        fstream file;
        file.open("config.txt");

        // if there is no config file, create it and set it up
        if(!file.is_open()) {
            cout << "This seems to be the first time you are running this program. \nPlease enter your name: ";
            string name;
            getline(cin, name);
            cout << "Do you have the fisher profession? (y/n): ";
            string ans;
            getline(cin, ans);
            double fisher = 1;
            if(ans == "y") {
                fisher = FISHER;
                cout << "Do you have the angler profession? (y/n): ";
                getline(cin, ans);
                if(ans == "y") {
                    fisher = ANGLER;
                }

            }
            file.open("config.txt", std::ios::out | std::ios::app);
            file << name << endl;
            file << fisher << endl;

            vector<string> options = {"Description", "Price", "Locations", "Time", "Season", "Weather", "Size", "Difficulty", "XP", "Uses"};
            ArrowCheckList(
                {"What details would you like to see on a DETAILED fish search?\n"},
                &options
            );

            file << options.size() << endl;
            for (string s : options) {
                file << s << endl;
            }

            options.clear();
            options =  {"Description", "Price", "Locations", "Time", "Season", "Weather", "Size", "Difficulty", "XP", "Uses"};
            ArrowCheckList( 
                {"What details would you like to see on a less detailed fish search?"},
                &options
            );

            file << options.size() << endl;
            for (string s : options) {
                file << s << endl;
            }

            file.close();
        }
        
        file >> farmer.name;
        file >> farmer.profession;
        int size;
        file >> size;
        for(int i = 0; i <= size; i++) {
            string s;
            file >> s;
            farmer.detailedOptions.push_back(s);
        }
        file >> size;
        for(int i = 0; i <= size; i++) {
            string s;
            file >> s;
            farmer.lessDetailedOptions.push_back(s);
        }

        file.close(); 
        return farmer;
    }

    int MainMenu() {
        // /*debug*/cin.ignore();
        system("clear");
        cout << "What would you like to do?" << endl;
        cout << "1. List all fish names" << endl;
        cout << "2. Search for a fish" << endl;
        cout << "3. What fish can I catch right now?" << endl;
        cout << "4. What fish can I catch today?" << endl;
        cout << "5. Update config file" << endl;
        cout << "0. Exit" << endl;
        int choice = 1;
        cin >> choice;
        cin.ignore();

        return choice;

    }

    int PrintAllFish() {
        for (int i = 0; i < fishList.size(); i++) {
            cout << fishList[i].getName() << endl;
        }
        cout << "Would you like to print the details of any? (y/N): ";
        string ans;
        getline(cin, ans);
        if(ans == "y") {
            return 2;
        }
        return 1;
    }

    int Search() {
        cout << "Enter the name of the fish you want to search for: ";
        string name;
        getline(cin, name);
        string ans;
        bool found = false;

        for (int i = 0; i < fishList.size(); i++) {
            if (fishList[i].getName() == name) {
                fishList[i].printFishDetails(farmer.detailedOptions, farmer.profession);
                found = true;
                break;
            }
        }
        if(!found) { cout << RED << "Fish not found!\n" << RESET; }
        cout << "Would you like to search for another fish? (y/N): ";
        getline(cin, ans);
        if(ans == "y") {
            return 2;
        }
        return 0;
    }

    int CatchRN() {
        vector<Fish> filteredFish = fishList;
        vector<string> dialogue;
        vector<string> options;
        int answer;

        /*--------------------------SEASON--------------------------*/
        dialogue.push_back("What season is it?");
        options = {"Any", "Spring", "Summer", "Fall", "Winter"};
        answer = ArrowList(dialogue, &options);

        dialogue.push_back(options[answer]);
        if(options[answer] != "Any") {
            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(eh.stringToSeason(options[answer]))) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }
        }
        
        
        /*--------------------------LOCATION--------------------------*/
        options.clear();
        dialogue.push_back("Where are you fishing? ");
        options = {"Any", "Forest Farm", "Ocean", "Town River", "Forest River", "Forest Pond", "Secret Woods", "Mountain Lake", "Mines", "Witch's Swamp", "Sewers", "Mutant Bug Lair", "Desert", "Pirate Cove", "Ginger Island Pond", "Ginger Island River", "Ginger Island Ocean", "Volcano Caldera", "Night Market"};
        ArrowCheckList(dialogue, &options);

        dialogue.push_back("");
        if(options[0] != "Any") {
            for(int i = 0; i < options.size(); i++) {
                dialogue[dialogue.size() - 1].append(options[i]);
                if(i != options.size() - 1) {
                    dialogue[dialogue.size() - 1].append(", ");
                }
                if(i + 1 % 5 == 0) {
                    dialogue[dialogue.size() - 1].append("\n\t\t");
                }
            }
            for(int j = 0; j < filteredFish.size(); j++) {
                if(!filteredFish[j].isAvailable(options)) {
                    filteredFish.erase(filteredFish.begin() + j);
                    j--;
                }
            }
        }
        else {
            dialogue[dialogue.size() - 1].append("Any");
        }

        /*--------------------------WEATHER--------------------------*/
            dialogue.push_back("What's the weather?");
            options.clear();
            options = {"Any", "Rainy", "Sunny"};
            int ans = ArrowList(dialogue, &options);
            bool isRain = false;    
            bool isSun = false;
            if(ans == 1) {
                isRain = true;
                dialogue.push_back("Rainy");
            }
            if(ans == 0) {
                isRain = true;
                isSun = true;
                dialogue.push_back("Any");
            }
            if(ans == 2) {
                isSun = true;
                dialogue.push_back("Sunny");
            }
            if(!isRain || !isSun) {
                for(int i = 0; i < filteredFish.size(); i++) {
                    if(!filteredFish[i].isAvailable(isRain, isSun)) {
                        filteredFish.erase(filteredFish.begin() + i);
                        i--;
                    }
                }
            }
         
            /*--------------------------TIME--------------------------*/
            system("clear");
            printDialogue(dialogue);
            cout << YELLOW << "What time is it? (6-23, 0-2): " << RESET;
            int time;
            while (true) {
                cin >> time;
                cin.ignore();
                if(time == 0) { time = 24;}
                if(time == 1) { time = 25;}
                if(time == 2) { time = 26;}
                if(time < 6 || time > 26) {
                    cout << "Invalid time. What time is it? (6-23, 0-2):";
                }
                else {
                    break;
                }
            }
            dialogue.push_back("What time is it? ");
            dialogue.push_back(to_string(time));

            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(time)) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }

            system("clear");
            printDialogue(dialogue);
            if(filteredFish.size() == 0) {
                cout << "There are no fish available right now. Press any key to continue...";
                cin.ignore();
                return 3;
            }
            cout << "You can catch " << filteredFish.size() << " fish right now: " << endl;
            for(int i = 0; i < filteredFish.size(); i++) {
                cout << filteredFish[i].getName() << endl;
            }
        

            cout << "Press any key to continue...";
            cin.ignore();
            return 3;
  
    }

    int CatchToday() {
        vector<Fish> filteredFish = fishList;
        vector<string> dialogue;
        vector<string> options;
        int answer;

        /*--------------------------SEASON--------------------------*/
        dialogue.push_back("What season is it?");
        options = {"Any", "Spring", "Summer", "Fall", "Winter"};
        answer = ArrowList(dialogue, &options);

        dialogue.push_back(options[answer]);
        if(options[answer] != "Any") {
            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(eh.stringToSeason(options[answer]))) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }
        }
        
        
        /*--------------------------LOCATION--------------------------*/
        options.clear();
        dialogue.push_back("Where are you fishing? ");
        options = {"Any", "Forest Farm", "Ocean", "Town River", "Forest River", "Forest Pond", "Secret Woods", "Mountain Lake", "Mines", "Witch's Swamp", "Sewers", "Mutant Bug Lair", "Desert", "Pirate Cove", "Ginger Island Pond", "Ginger Island River", "Ginger Island Ocean", "Volcano Caldera", "Night Market"};
        ArrowCheckList(dialogue, &options);

        dialogue.push_back("");
        if(options[0] != "Any") {
            for(int i = 0; i < options.size(); i++) {
                dialogue[dialogue.size() - 1].append(options[i]);
                if(i != options.size() - 1) {
                    dialogue[dialogue.size() - 1].append(", ");
                }
                if(i + 1 % 5 == 0) {
                    dialogue[dialogue.size() - 1].append("\n\t\t");
                }
            }
            for(int j = 0; j < filteredFish.size(); j++) {
                if(!filteredFish[j].isAvailable(options)) {
                    filteredFish.erase(filteredFish.begin() + j);
                    j--;
                }
            }
        }
        else {
            dialogue[dialogue.size() - 1].append("Any");
        }
            

        /*--------------------------WEATHER--------------------------*/
        dialogue.push_back("What's the weather?");
        options.clear();
        options = {"Any", "Rainy", "Sunny"};
        int ans = ArrowList(dialogue, &options);
        bool isRain = false;    
        bool isSun = false;
        if(ans == 1) {
            isRain = true;
            dialogue.push_back("Rainy");
        }
        if(ans == 0) {
            isRain = true;
            isSun = true;
            dialogue.push_back("Any");
        }
        if(ans == 2) {
            isSun = true;
            dialogue.push_back("Sunny");
        }
        if(!isRain || !isSun) {
            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(isRain, isSun)) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }
        }

        system("clear");
        printDialogue(dialogue);
        if(filteredFish.size() == 0) {
            cout << "There are no fish available right now. Press any key to continue...";
            cin.ignore();
            return 3;
        }
        cout << "You can catch " << filteredFish.size() << " fish right now: " << endl;
        for(int i = 0; i < filteredFish.size(); i++) {
            cout << filteredFish[i].getName() << endl;
        }
    
        cout << "Press any key to continue...";
        cin.ignore();
  
        return 4;
    }

    int UpdateConfig(Farmer f) {
        remove("config.txt");
        f = Config();
        return 5;
    }

private:
    vector<Fish> fishList;
    Farmer farmer;
    EnumHelper eh;

    void printDialogue(vector<string> dialogue) {
        for (int i = 0; i < dialogue.size(); i++) {
            if(i % 2 == 0) {
                cout << YELLOW << dialogue[i] << RESET << "\t";
            }
            else {
                cout << dialogue[i] << endl;
            }
        }
    }

    void printOptions(const vector<string>& options, int selectedOption, vector<string> q) {
        system("clear");

        printDialogue(q);
        cout << endl;
        for (int i = 0; i < options.size(); ++i) {
            if (i == selectedOption) {
                cout << GREEN << "> " << options[i] << RESET << endl; 
            } else {
                cout << "  " << options[i] << endl;
            }
        }
    }

    void printOptionsChecklist(const vector<string>& options, int selectedOption, vector<bool> selectedOptions, vector<string> q) {
        system("clear");

        printDialogue(q);
        cout << endl;
        for (int i = 0; i < options.size(); i++) {
            if (i == selectedOption) {
                cout << GREEN << "> " ; 
            }
            else 
            {
                cout << GREEN << "  ";
            }
            if(selectedOptions[i]) {
                cout << GREEN << options[i] << RESET << endl; 
            }           
            else {
                cout << RESET << options[i] << endl;
            }

        }
    }

    void setNonBlocking(bool enable) {
        struct termios ttystate;
        tcgetattr(STDIN_FILENO, &ttystate);
        if (enable) {
            ttystate.c_lflag &= ~ICANON;
            ttystate.c_cc[VMIN] = 1;
        } else {
            ttystate.c_lflag |= ICANON;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

    int ArrowList(vector<string> dialogue, vector<string> *options) {
        system("clear");
        int selectedOption = 0;
        
        char key;
        setNonBlocking(true); 
        do {
            printOptions(*options, selectedOption, dialogue);
            key = getchar(); 
            switch (key) {
                case 65: 
                    if (selectedOption > 0) {
                        selectedOption--;
                    }
                    break;
                case 66: 
                    if (selectedOption < options->size() - 1) {
                        selectedOption++;
                    }
                    break;
            }
        } while (key != 10); 
        setNonBlocking(false); 
        return selectedOption;
    }

    void ArrowCheckList(vector<string> question, vector<string> *options) {
        system("clear");

        vector<bool> selectedOptions;
        for(int i = 0; i < options->size(); i++) {
            selectedOptions.push_back(false);
        }
        int selectedOption = 0;

        
        char key;
        setNonBlocking(true); 
        
        do {
            printOptionsChecklist(*options, selectedOption, selectedOptions, question);
            key = getchar(); 
           
            switch (key) {
                case 65: 
                    if (selectedOption > 0) {
                        selectedOption--;
                    }
                    break;
                case 66: 
                    if (selectedOption < options->size() - 1) {
                        selectedOption++;
                    }
                    break;
                case 32: 
                    selectedOptions[selectedOption] = !selectedOptions[selectedOption];
                    if(options->at(0) == "Any") {
                        if(selectedOption == 0) {
                            for(int i = 1; i < selectedOptions.size(); i++) {
                                selectedOptions[i] = selectedOptions[0];
                            }
                        }
                        else if(!selectedOptions[selectedOption]) {
                            selectedOptions[0] = false;
                        }
                        else {
                            for(int i = 1; i < selectedOptions.size(); i++) {
                                selectedOptions[0] = selectedOptions[0] && selectedOptions[i];
                            }
                        }
                    }
                    break;
            }
        } while (key != 10); 
        setNonBlocking(false); 
        //TODO: if no options are selected, the last one selected before enter should be selected
        int b;
        for(b = 0; b < selectedOptions.size(); b++) {
            if(selectedOptions[b]) {
                break;
            }
        }
        if(b == selectedOptions.size()) {
            selectedOptions[selectedOption] = true;
        }

        for(int i = 0; i < selectedOptions.size(); i++) {
            if(!selectedOptions[i]) {
                options->erase(options->begin() + i);
                selectedOptions.erase(selectedOptions.begin() + i);
                i--;
                
            }
        }



    }


};

