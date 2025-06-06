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
#include <cstdlib>

//use my header files
#include "greet.h"
#include "greets.cpp"

//convenient
using namespace std;

int main(){
    int selectedClass;
    //get the time when they start the program
    time_t startPlaytime = time(nullptr);

    cout << "Before we begin, please choose your class.\n 1. Rogue\n 2. Fighter\n 3. Wizard\n (Enter the corresponding number)" << endl;
    cin >> selectedClass;
    switch(selectedClass){
        case 1: 
            Rogue newRogue;
            cout << "Rogue. A wise choice. You favor quick strikes." << endl;
            newRogue.showStats();

    }
}












//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Character Classes using OOP below

// Base class for all the specified classes that will be picked by the player :)
class Character {
    protected:
        std::string charName;
        
        int hitpoints;
        
        int str, dex, cha, con, wis, inte;

        int level; 

        //dice that will be rolled -- virtual helps with polymorphism in the child classes  
        virtual int rollingDice() const = 0;

        //calculate what your HP will be at on level up
        int calculateHP() const {
            int constitutionModifier = getMod(con);
            int baseHitPoints = rollingDice() + constitutionModifier;
            if (baseHitPoints < 1){
                baseHitPoints = 1;
            }
            return baseHitPoints * level;
        }
        
        //calculate the modifier for the stat that will be used in the situation
        static int getMod(int modStat) {
            return std::floor((modStat-10)/2.0);
        }
        
    public:
        //base construction
        Character(const std::string& className, int stre, int dext, int cons, int intel, int wisd, int chari, int levell = 1) : charName(className), str(stre), dex(dext), con(cons), inte(intel), wis(wisd), cha(chari), level(levell), hitpoints(0){
            hitpoints = calculateHP();
        }

        //lets user see current important information and basic information about their character
        virtual void showStats() const{
            cout << "Your selected class: " << charName << " (Current Level: " << level << ")" << " and Hit Points: " << hitpoints << std::endl;
            cout << "Stats: " << std::endl;
            cout << "Strength: " << str << " modified by: " << showModifier(str) << std::endl;
            std::cout << "Dexterity: " << dex << " modified by: " << showModifier(dex) << std::endl;
            std::cout << "Constitution: " << con << " modified by: " << showModifier(con) << std::endl;
            std::cout << "Intelligence: " << inte << " modified by: " << showModifier(inte) << std::endl;
            std::cout << "Wisdom: " << wis << " modified by: " << showModifier(wis) << std::endl;
            std::cout << "Charisma: " << cha << " modified by: " << showModifier(cha) << std::endl;
        }

        //formatting the modifier for the stat to make it display easier and prettier
        static std::string showModifier(int modifiedStat) {
            int modifier = getMod(modifiedStat);
            return (modifier >= 0 ? "+" : "") + std::to_string(modifier);
        }
        
        //virtual for the reason of being specified and implemented in the specified class
        virtual void attack() const = 0;

        //leveling up
        virtual void levelUp() {
            level++;
            hitpoints = calculateHP();
            std::cout << charName << " is now at level " << level << "! Your hitpoints have increased to " << hitpoints << std::endl;
        }

        //accessors for the protected stats
        int getLevel() const {return level;}
        int getHitpoints() const { return hitpoints; }
        std::string getCharName() const { return charName; }
        
        int getStr() const { return str; }
        int getDex() const { return dex; }
        int getCon() const { return con; }
        int getInt() const { return inte; }
        int getWis() const { return wis; }
        int getCha() const { return cha; }
};

class Fighter : public Character {
    protected:
        //specifying their dice for hp level up and more now - fighters use a d10
        int rollingDice() const override {
            return 10;
        }

    public:
        //creating a fighter
        Fighter(int level = 1) : Character("Fighter", 16, 12, 14, 10, 11, 9, level) {}

        //provides info on the class
        void showStats() const override {
            Character::showStats();
            std::cout << "Fighters are best at melee combat and using heavy armor. Their damage primarily is based off of their strength ability score." << std::endl;
        }

        //how to attack
        void attack() const override {
            int damage = 1 + getMod(str);
            if (damage < 1) damage = 1;
            std::cout << charName << " slices with their sword. Rolling for hit." << endl;
            int damageRoll = rand() % 21;
            if(damageRoll >= 14){
                std::cout << "The hit is successful! You do " << damage << " damage!" << std::endl;
            }

            else{
                std::cout << "The hit is a fail." << std::endl;
            }
        }

};

class Wizard : public Character {
    protected:
        //specifying their dice for hp level up and more now - wizards use a d6
        int rollingDice() const override {
            return 6;
        }
        
        //add mana since doing spell levels is too hard
        int mana;

    public:
        //creating a fighter
        Wizard(int level = 1) : Character("Wizard", 8, 14, 10, 18, 13, 12, level), mana(10 * level) {}

        //provides info on the class
        void showStats() const override {
            Character::showStats();
            std::cout << "Wizards are best at magical combat and spell casting. Their damage primarily is based off of their intelligence ability score." << std::endl;
        }

        //how to attack
        void attack() const override {
            int spellDamage = std::max(1, 1 + getMod(inte));
            if (spellDamage < 1) spellDamage = 1;
            std::cout << charName << " casts a fireball. Rolling for hit." << endl;
            int damageRoll = rand() % 21;
            if(damageRoll >= 14){
                std::cout << "The hit is successful! You do " << spellDamage << " damage!" << std::endl;
            }

            else{
                std::cout << "The hit is a fail." << std::endl;
            }
        }

        void levelUp() override {
            Character::levelUp();
            mana += 10;
            std::cout << charName <<"'s mana points are increased to a total of " << mana << std::endl;
        }

};

class Rogue : public Character {
    protected:
        //specifying their dice for hp level up and more now - rogues use a d8
        int rollingDice() const override {
            return 8;
        }

    public:
        //creating a fighter
        Rogue(int level = 1) : Character("Rogue", 12, 18, 12, 13, 10, 14, level) {}

        //provides info on the class
        void showStats() const override {
            Character::showStats();
            std::cout << "Rogues are best at stealth and quick strikes. Their damage primarily is based off of their dexterity ability score." << std::endl;
        }

        //how to attack
        void attack() const override {
            int damage = 1 + getMod(str);
            if (damage < 1) damage = 1;
            std::cout << charName << " stabs with their knife. Rolling for hit." << endl;
            int damageRoll = rand() % 21;
            if(damageRoll >= 14){
                std::cout << "The hit is successful! You do " << damage << " damage!" << std::endl;
            }

            else{
                std::cout << "The hit is a fail." << std::endl;
            }
        }

};