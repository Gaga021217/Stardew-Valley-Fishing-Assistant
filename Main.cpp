#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <termios.h>
#include <unistd.h>

#include "Fish.hpp"
#include "FishReader.hpp"
#include "Menu.hpp"

using namespace std;

int main() {

    FishReader fr("fish_database.csv");    
    vector<Fish> fishList = fr.getFishList();
    

    system("clear");
    Menu m(fishList);
    Farmer farmer = m.Config();
    while (true) {
        int choice = m.MainMenu();
        
        if (choice == 0) {
            break;
        }
        if (choice == 1) {
            choice = m.PrintAllFish();
        }
        while(choice == 2) {
            
        }
        if(choice == 3) {
           
        }
        system("clear");
    }

}