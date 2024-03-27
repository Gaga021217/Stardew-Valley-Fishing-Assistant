#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <termios.h>
#include <unistd.h>

#include "FishReader.hpp"
#include "Menu.hpp"

using namespace std;

int main() {

    FishReader fr;    
    vector<Fish> fishList = fr.getFishList("FishDatabase.csv");
        
    Menu m(fishList);
    Farmer farmer = m.Config();


    do {
        int choice = m.MainMenu();

        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            choice = m.PrintAllFish();
        }
        while(choice == 2) {
            choice = m.Search();
        }
        if(choice == 3) {
           choice = m.CatchRN();
        }
        if(choice == 4) {
            choice = m.CatchToday();
        }
        if(choice == 5) {
            choice = m.UpdateConfig(farmer);
        }
        // system("clear");
    } while (true);

}