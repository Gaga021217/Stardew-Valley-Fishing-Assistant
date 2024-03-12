#pragma once

#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>

#include "Fish.hpp"
#include "FishReader.hpp"

#define FISHER 1.25
#define ANGLER 1.5

using namespace std;

struct Farmer {
    string name;
    double profession;
};

class Menu {
public:
    Menu(vector<Fish> fl) { fishList = fl; }
    ~Menu() {}

    
    Farmer Config() {
        fstream file("config.txt");
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

            ArrowList(
                "What details would you like to see on a DETAILED fish search?\n",
                {"Description", "Price", "Locations", "Available time", "Season", "Weather", "Size", "Difficulty", "XP", "Uses"}
            );

            cout << "What details would you like to see on a less detailed fish search?" << endl;


            file.open("config.txt");
            file << name << endl;
            file << fisher << endl;
            file.close();
        }
        string name;
        double fisher;
        file >> farmer.name;
        file >> farmer.profession;
        file.close();
        return farmer;
        

            
    }

    int MainMenu() {
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
        cout << "Would the details of any? (y/n): ";
        string ans;
        getline(cin, ans);
        if(ans == "y") {
            return 2;
        }
    }

    int Search() {
        cout << "Enter the name of the fish you want to search for: ";
        string name;
        getline(cin, name);
        string ans;
            
        for (int i = 0; i < fishList.size(); i++) {
            if (fishList[i].getName() == name) {
                fishList[i].printFishAllDetails(farmer.profession);
                break;
            }
        }
        cout << "Would you like to search for another fish? (y/n): ";
        getline(cin, ans);
        if(ans == "n") {
            return 0;
        }
    }

    int CatchRN() {
        vector<Fish> filteredFish = fishList;
        FishReader fr("fish_database.csv");

        /*--------------------------SEASON--------------------------*/
            vector<string> options = {"Any", "Spring", "Summer", "Fall", "Winter"};
            int selectedOption = 0;
            string question = "What season is it? \t";
            printOptions(options, selectedOption, question);

            setNonBlocking(true); // Enable non-blocking input

            char key;
            do {
                key = getchar(); // Read a single character (non-blocking)

                // Handle arrow key presses
                switch (key) {
                    case 65: // Up arrow key
                        if (selectedOption > 0) {
                            selectedOption--;
                        }
                        break;
                    case 66: // Down arrow key
                        if (selectedOption < options.size() - 1) {
                            selectedOption++;
                        }
                        break;
                }
                printOptions(options, selectedOption, question);
            } while (key != 10); // Repeat until Enter key is pressed

            setNonBlocking(false); // Disable non-blocking input

            question.append(options[selectedOption]);
            question.append("\n");
            if(options[selectedOption] != "Any") {
                for(int i = 0; i < filteredFish.size(); i++) {
                    if(!filteredFish[i].isAvailable(fr.stringToSeason(options[selectedOption]))) {
                        filteredFish.erase(filteredFish.begin() + i);
                        i--;
                    }
                }
            }

        /*--------------------------LOCATION--------------------------*/
            system("clear");
            cout << question;
            options.clear();
            int count = 0;
            options = {"Any", "Forest Farm", "Ocean", "Cindersap Forest Pond", "Town", "Forest River", "Forest Pond", "Secret Woods", "Mountain", "Mines", "Witch's Swamp", "Sewers", "Mutant Bug Lair", "Desert", "Pirate Cove", "Ginger Island Pond", "Ginger Island River", "Ginger Island Ocean", "Volcano Caldera", "Night Market"};
            vector<bool> selectedOptions;
            for(int i = 0; i < options.size(); i++) {
                selectedOptions.push_back(false);
            }
            selectedOption = 0;
            question.append("Where are you fishing? ");
            printOptionsChecklist(options, selectedOption, selectedOptions, question);
            setNonBlocking(true); // Enable non-blocking input
            do {
                key = getchar(); // Read a single character (non-blocking)

                // Handle arrow key presses
                switch (key) {
                    case 65: // Up arrow key
                        if (selectedOption > 0) {
                            selectedOption--;
                        }
                        break;
                    case 66: // Down arrow key
                        if (selectedOption < options.size() - 1) {
                            selectedOption++;
                        }
                        break;
                    case 32: // Space key
                        selectedOptions[selectedOption] = !selectedOptions[selectedOption];
                        if(selectedOption == 0) {
                            for(int i = 1; i < selectedOptions.size(); i++) {
                                selectedOptions[i] = selectedOptions[0];
                            }
                        }

                        break;

                }
                printOptionsChecklist(options, selectedOption, selectedOptions, question);
            } while (key != 10); // Repeat until Enter key is pressed

            setNonBlocking(false); // Disable non-blocking input
            
            bool boolSum = true;
            if(!selectedOptions[0]) {
                for(int i = 0; i < selectedOptions.size(); i++) {
                    if(selectedOptions[i]) {
                        question.append(options[i]);
                        boolSum = boolSum | selectedOptions[i];
                        if(i != selectedOptions.size() - 1) {
                            question.append(", ");
                        }
                    }
                }
            }
            else {
                question.append("Any");
            }
            if(!boolSum) {
                question.append(options[selectedOption]);
                selectedOptions[selectedOption] = true;
                if(selectedOption == 0) {
                    for(int i = 1; i < selectedOptions.size(); i++) {
                        selectedOptions[i] = selectedOptions[0];
                    }
                }
            }

            options.clear();
            options = {"Any", "ForestFarm", "Ocean", "CindersapForestPond", "TownRiver", "ForestRiver", "ForestPond", "SecretWoods", "MountainLake", "Mines", "WitchSwamp", "Sewers", "MutantBugLair", "Desert", "PirateCove", "GIPond", "GIRiver", "GIOcean", "VolcanoCaldera", "NightMarket"};
            bool keep = false;
            for(int i = 0; i < filteredFish.size(); i++) {
                for(int j = 1; j < options.size(); j++) {
                    if(selectedOptions[j]) {
cout << j << " ";
                        if(filteredFish[i].isAvailable(fr.stringToLocation(options[j]))) {
                            keep |= true;
                            break;
                            
                        }
                    }
                }
                if(!keep) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }
cin.ignore();

        /*--------------------------WEATHER--------------------------*/
            system("clear");
            cout << question;
            cout << "\nIs it raining? ((y)es/((n)o/doesn't m(a)tter): ";
            string ans;
            getline(cin, ans);
            bool isRain = false;    
            bool isSun = false;
            if(ans == "y") {
                isRain = true;
            }
            if(ans == "a") {
                isRain = true;
                isSun = true;
            }
            if(ans == "n") {
                isSun = true;
            }
            question.append("\nIs it raining? ");
            if(ans == "y") {
                question.append("Yes");
            }
            if(ans == "n") {
                question.append("No");
            }
            if(ans == "a") {
                question.append("Doesn't matter");
            }
            question.append("\n");

            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(isRain, isSun)) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }
         
            /*--------------------------TIME--------------------------*/
            system("clear");
            cout << question;
            cout << "\nWhat time is it? (6-23, 0-2): ";
            int time;
            cin >> time;
            if(time == 0) { time = 24;}
            if(time == 1) { time = 25;}
            if(time == 2) { time = 26;}
            cin.ignore();
            question.append("\nWhat time is it? ");
            question.append(to_string(time));
            question.append("\n");

            system("clear");
            cout << question;

            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(time)) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }

            cout << "You can catch the following fish right now: " << endl;
            for(int i = 0; i < filteredFish.size(); i++) {
                filteredFish[i].printFish();
            }
        

            cout << "Press any key to continue...";
            cin.ignore();
  
    }









private:
    vector<Fish> fishList;
    Farmer farmer;

    void printOptions(const vector<string>& options, int selectedOption, string q) {
        system("clear"); // Clear screen

        cout << q << endl;
        for (int i = 0; i < options.size(); ++i) {
            if (i == selectedOption) {
                cout << GREEN << "> " << options[i] << RESET << endl; // Highlight selected option
            } else {
                cout << "  " << options[i] << endl;
            }
        }
    }

    void printOptionsChecklist(const vector<string>& options, int selectedOption, vector<bool> selectedOptions, string q) {
        // ANSI escape codes for colors
        const string selectedColor = "\033[1;32m"; // Green for selected option
        const string defaultColor = "\033[0m"; // Default color

        system("clear"); // Clear screen

        cout << q << endl;
        for (int i = 0; i < options.size(); i++) {
            if (i == selectedOption) {
                cout << selectedColor << "> " << defaultColor << options[i] << endl; // Highlight selected option
            }
            else 
            {
                cout << selectedColor << "  ";
            }
                if(selectedOptions[i]) {
                cout << selectedColor << "  " << options[i] << defaultColor << endl; // Highlight selected option
            }           
            else {
                cout << "  " << options[i] << endl;
            }

        }
    }

    // Function to enable non-blocking input
    void setNonBlocking(bool enable) {
        struct termios ttystate;
        tcgetattr(STDIN_FILENO, &ttystate);
        if (enable) {
            ttystate.c_lflag &= ~ICANON; // Disable canonical mode
            ttystate.c_cc[VMIN] = 1; // Minimum number of characters to read
        } else {
            ttystate.c_lflag |= ICANON; // Enable canonical mode
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

    void ArrowList(string question, vector<string> options) {
        system("clear");
        //init variables
        vector<bool> selectedOptions;
        for(int i = 0; i < options.size(); i++) {
            selectedOptions.push_back(false);
        }
        int selectedOption = 0;

        
        char key;
        setNonBlocking(true); // Enable non-blocking input
        do {
            printOptionsChecklist(options, selectedOption, selectedOptions, question);
            key = getchar(); // Read a single character (non-blocking)
            // Handle arrow key presses
            switch (key) {
                case 65: // Up arrow key
                    if (selectedOption > 0) {
                        selectedOption--;
                    }
                    break;
                case 66: // Down arrow key
                    if (selectedOption < options.size() - 1) {
                        selectedOption++;
                    }
                    break;
                case 32: // Space key
                    selectedOptions[selectedOption] = !selectedOptions[selectedOption];
                    break;
            }
        } while (key != 10); // Repeat until Enter key is pressed
        setNonBlocking(false); // Disable non-blocking input

        //produce selection
        for(int i = 0; i < selectedOptions.size(); i++) {
            if(!selectedOptions[i]) {
                options.erase(options.begin() + i);
                selectedOptions.erase(selectedOptions.begin() + i);
                i--;
                
            }
        }

        for(int i = 0; i < options.size(); i++) {
            cout << options[i] << endl;
        }



    }


};

