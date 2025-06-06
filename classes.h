#include <iostream>;

#ifndef CLASSES_H
#define CLASSES_H
class Base {
    public:
        std::string charName;
        
        int hitpoints;
        
        int str, dex, cha, con, wis, inte;

        int level; 
        
        void attack(){
            std::cout << charName << " attacks the enemy! Rolling to see if you hit!" << std::endl;
        }

        void damageTaken(int dmg){
            hitpoints -= dmg;
            std::cout << charName << " has taken " << dmg << " points of damage!" << std::endl;
        }
        Base();

};


#endif