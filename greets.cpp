#include "greet.h"
#include <iostream>
#include <string>
#include <cctype>
#include <ctime>

std::string greetPlayer(std::string playerName) {
    return "Welcome, " + playerName + ", to the one and only, legendary, brain-bending, fun, fabled Heroes of the Mist!";
}

std::string listClass(std::string playerClass) {
    return "It seems that you have selected " + playerClass + " as your class for today's playsession. This is a wise choice! I hope you will have lots of fun!";
}

void closingMessage(std::string playerName, std::string playerClass, int level, int startPlaytime) {
    std::cout << "Well, " << playerName << " it seems that your time playing has come to an end. I hope you had a great time playing as a / an " << playerClass << ". At the end of this, your maximum level you reached was level " << level << ". That's pretty good! And, your total playtime was " << time(nullptr) - startPlaytime << ". I hope you come back to play again! Goodbye." << std::endl;
}