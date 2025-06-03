/*
Name: Andrew Sinha
Date: 6/3/2025
Program Title: Final Project - Heroes of the Mist
*/

//necessary imports
#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <thread>
#include <chrono>

//use my header files
#include "greet.h"
#include "greets.cpp"

//convenient
using namespace std;

int main(){
    //get the time when they start the program
    time_t startPlaytime = time(nullptr);

    //cout << "Before we begin, please choose your class.\n 1. Rogue\n
}




















//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Classes

//parent
class playerClass {
    public: 
        int playerClass::Character(string name, int health, int level, int baseDMG){}
    
    protected:
        string name;
        int str;
        int dex;
        int con;
        int inte;
        int wis;
        int cha;
        
        int health;
        int baseDMG;
};


//children
//--------

class Rogue : public playerClass {
    public:
        void setName(string playerName){
            name = playerName;
        }

        
};