#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include "Fish.cpp"

#define FISHER 1.25
#define ANGLER 1.5
 
Location stringToLocation(std::string str) {
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

Behavior  stringToBehavior(std::string str) {
    if(str == "Floater") { return Behavior::Floater; }
    if(str == "Mixed") { return Behavior::Mixed; }
    if(str == "Smooth") { return Behavior::Smooth; }
    if(str == "Sinker") { return Behavior::Sinker; }
    if(str == "Dart") { return Behavior::Dart; }
    return Behavior::Unknown;
}

Season stringToSeason(std::string str) {
    if(str == "Spring") { return Season::Spring; }
    if(str == "Summer") { return Season::Summer; }
    if(str == "Fall") { return Season::Fall; }
    if(str == "Winter") { return Season::Winter; }
    return Season::Unknown;
}

void printOptions(const std::vector<std::string>& options, int selectedOption, std::string q) {
    // ANSI escape codes for colors
    const std::string selectedColor = "\033[1;32m"; // Green for selected option
    const std::string defaultColor = "\033[0m"; // Default color

    system("clear"); // Clear screen
    
    std::cout << q << std::endl;
    for (int i = 0; i < options.size(); ++i) {
        if (i == selectedOption) {
            std::cout << selectedColor << "> " << options[i] << defaultColor << std::endl; // Highlight selected option
        } else {
            std::cout << "  " << options[i] << std::endl;
        }
    }
}

void printOptionsChecklist(const std::vector<std::string>& options, int selectedOption, std::vector<bool> selectedOptions, std::string q) {
    // ANSI escape codes for colors
    const std::string selectedColor = "\033[1;32m"; // Green for selected option
    const std::string defaultColor = "\033[0m"; // Default color

    system("clear"); // Clear screen
    
    std::cout << q << std::endl;
    for (int i = 0; i < options.size(); i++) {
        if (i == selectedOption) {
            std::cout << selectedColor << "> " << options[i] << defaultColor << std::endl; // Highlight selected option
        }
        else if(selectedOptions[i]) {
            std::cout << selectedColor << "  " << options[i] << defaultColor << std::endl; // Highlight selected option
        }           
        else {
            std::cout << "  " << options[i] << std::endl;
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

int main() {

    std::vector<Fish> fishList;
    std::ifstream file("fish_database.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        //Pufferfish;Inflates when threatened.;200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        std::string name = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        //Inflates when threatened.;200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::string description = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        //200,250,300,400;Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::vector<int> price;
        std::string temp = line.substr(0, line.find(";"));
        temp.append(",");
        line = line.substr(line.find(";") + 1);
        while(temp.find(',') != std::string::npos) {
            price.push_back(std::stoi(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //Ocean,GIOcean;12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::vector<Location> locations;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != std::string::npos) { 
            locations.push_back(stringToLocation(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //12;16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int startTime = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //16;Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int endTime = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Summer;Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::vector<Season> seasons;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != std::string::npos) { 
            seasons.push_back(stringToSeason(temp.substr(0, temp.find(","))));
            temp = temp.substr(temp.find(",") + 1);
        }
        //Spring,Summer,Fall,Winter;GIOcean;Sunny;1;37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::vector<Season> specialSeasons;
        temp = line.substr(0, line.find(";"));
        line = line.substr(line.find(";") + 1);
        temp.append(",");
        while (temp.find(',') != std::string::npos){
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

        int minLength = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //37;80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int maxLength = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //80;Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        int difficulty = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Floater;29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        Behavior behavior = stringToBehavior(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //29;Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;
        
        int XP = std::stoi(line.substr(0, line.find(";")));
        line = line.substr(line.find(";") + 1);
        //Specialty Fish Bundle;Abigail(Loved);Aquatic Research Quest;

        std::vector<std::string> usedIn;
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

        fishList.push_back(fsh);
        
    }

    system("clear");
    std::cout << "Welcome to Stardew Valley Fish Guide!" << std::endl;
    while (true) {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. List all fish names" << std::endl;
        std::cout << "2. Search for a fish" << std::endl;
        std::cout << "3. What fish can I catch right now?" << std::endl;
        std::cout << "0. Exit" << std::endl;
        int choice = 1;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            for (int i = 0; i < fishList.size(); i++) {
                std::cout << fishList[i].getName() << std::endl;
                
            }
            std::cout << "Would you like to list any? (y/n): ";
            std::string ans;
            std::getline(std::cin, ans);
            if(ans == "y") {
                choice = 2;
            }
        }
        while(choice == 2) {
            std::cout << "Enter the name of the fish you want to search for: ";
            std::string name;
            std::getline(std::cin, name);

            double fisher = 1;
            std::cout << "Do you have the fisher profession? (y/n): ";
            std::string ans;
            std::getline(std::cin, ans);
            if(ans == "y") {
                fisher = FISHER;
                std::cout << "Do you have the angler profession? (y/n): ";
                std::getline(std::cin, ans);
                if(ans == "y") {
                    fisher = ANGLER;
                }
            }

            for (int i = 0; i < fishList.size(); i++) {
                if (fishList[i].getName() == name) {
                    fishList[i].printFishAllDetails(fisher);
                    break;
                }
            }
            std::cout << "Would you like to search for another fish? (y/n): ";
            std::getline(std::cin, ans);
            if(ans == "n") {
                choice = 0;
            }
        }
        if(choice == 3) {
            std::vector<Fish> filteredFish = fishList;

        /*--------------------------SEASON--------------------------*/
            std::vector<std::string> options = {"Any", "Spring", "Summer", "Fall", "Winter"};
            int selectedOption = 0;
            std::string question = "What season is it?";
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
                    if(!filteredFish[i].isAvailable(stringToSeason(options[selectedOption]))) {
                        filteredFish.erase(filteredFish.begin() + i);
                        i--;
                    }
                }
            }

        /*--------------------------LOCATION--------------------------*/
            system("clear");
            std::cout << question;
            options.clear();
            int count = 0;
            options = {"Any", "Forest Farm", "Ocean", "Cindersap Forest Pond", "Town", "Forest River", "Forest Pond", "Secret Woods", "Mountain", "Mines", "Witch's Swamp", "Sewers", "Mutant Bug Lair", "Desert", "Pirate Cove", "Ginger Island Pond", "Ginger Island River", "Ginger Island Ocean", "Volcano Caldera", "Night Market"};
            std::vector<bool> selectedOptions;
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


            for(int i = 0; i < selectedOptions.size(); i++) {
                if(selectedOptions[i]) {
                    question.append(options[i]);
                    if(i != selectedOptions.size() - 1) {
                        question.append(", ");
                    }
                }
            }

            options.clear();
            options = {"Any", "ForestFarm", "Ocean", "CindersapForestPond", "TownRiver", "ForestRiver", "ForestPond", "SecretWoods", "Mountain", "Mines", "WitchSwamp", "Sewers", "MutantBugLair", "Desert", "PirateCove", "GIPond", "GIRiver", "GIOcean", "VolcanoCaldera", "NightMarket"};
            bool keep = false;
            for(int i = 0; i < filteredFish.size(); i++) {
                for(int j = 0; j < options.size(); j++) {
                    if(selectedOptions[j]) {
                        if(filteredFish[i].isAvailable(stringToLocation(options[j]))) {
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

        /*--------------------------WEATHER--------------------------*/
            system("clear");
            std::cout << question;
            std::cout << "\nIs it raining? ((y)es/((n)o/doesn't m(a)tter): ";
            std::string ans;
            std::getline(std::cin, ans);
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
            std::cout << question;
            std::cout << "\nWhat time is it? (6-23, 0-2): ";
            int time;
            std::cin >> time;
            if(time == 0) { time = 24;}
            if(time == 1) { time = 25;}
            if(time == 2) { time = 26;}
            std::cin.ignore();
            question.append("\nWhat time is it? ");
            question.append(std::to_string(time));
            question.append("\n");

            system("clear");
            std::cout << question;

            for(int i = 0; i < filteredFish.size(); i++) {
                if(!filteredFish[i].isAvailable(time)) {
                    filteredFish.erase(filteredFish.begin() + i);
                    i--;
                }
            }

            std::cout << "You can catch the following fish right now: " << std::endl;
            for(int i = 0; i < filteredFish.size(); i++) {
                filteredFish[i].printFish();
            }
        

            std::cout << "Press any key to continue...";
            std::cin.ignore();
  
        }
        system("clear");
    }

}