#ifndef GREET_
#define GREET_
#include <string>

std::string greetPlayer(std::string playerName);
std::string listClass(std::string playerClass);
void closingMessage(std::string playerName, std::string playerClass, int level, int startPlaytime);

#endif