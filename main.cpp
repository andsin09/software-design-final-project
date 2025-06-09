/*
Name: Andrew Sinha
Date: 6/3/2025
Program Title: Final Project - Heroes of the Mist
*/

//necessary imports
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

class Character {
protected:
    string charName;
    int hitpoints;
    int maxHitpoints;
    int str, dex, cha, con, wis, inte;
    int level;

    virtual int rollingDice() const = 0;

    int calculateHP() const {
        int constitutionModifier = getMod(con);
        int baseHitPoints = rollingDice() + constitutionModifier;
        if (baseHitPoints < 1){
            baseHitPoints = 1;
        }
        return baseHitPoints * level;
    }

    static int getMod(int modStat) {
        return static_cast<int>(floor((modStat - 10) / 2.0));
    }

public:
    Character(const string& className, int stre, int dext, int cons, int intel, int wisd, int chari, int levell = 1)
        : charName(className), str(stre), dex(dext), con(cons), inte(intel), wis(wisd), cha(chari), level(levell), hitpoints(0), maxHitpoints(0)
    {
    }

    virtual ~Character() = default;

    virtual void showStats() const {
        cout << "Your selected class: " << charName << " (Current Level: " << level << ") and Hit Points: " << hitpoints << "/" << maxHitpoints << "\n";
        cout << "Stats:\n";
        cout << "Strength: " << str << " modified by: " << showModifier(str) << "\n";
        cout << "Dexterity: " << dex << " modified by: " << showModifier(dex) << "\n";
        cout << "Constitution: " << con << " modified by: " << showModifier(con) << "\n";
        cout << "Intelligence: " << inte << " modified by: " << showModifier(inte) << "\n";
        cout << "Wisdom: " << wis << " modified by: " << showModifier(wis) << "\n";
        cout << "Charisma: " << cha << " modified by: " << showModifier(cha) << "\n";
    }

    static string showModifier(int modifiedStat) {
        int modifier = getMod(modifiedStat);
        return (modifier >= 0 ? "+" : "") + to_string(modifier);
    }

    virtual void attack(Character& target) const = 0;

    virtual void takeDamage(int damage) {
        hitpoints -= damage;
        if (hitpoints < 0) hitpoints = 0;
        cout << charName << " takes " << damage << " damage! Remaining HP: " << hitpoints << "/" << maxHitpoints << "\n";
    }

    virtual void levelUp() {
        level++;
        maxHitpoints = calculateHP();
        hitpoints = maxHitpoints;
        cout << charName << " is now at level " << level << "! Your hitpoints have increased to " << hitpoints << "/" << maxHitpoints << "\n";
    }

    void healFull() {
        hitpoints = maxHitpoints;
        cout << charName << " has been healed to full! Current HP: " << hitpoints << "/" << maxHitpoints << "\n";
    }

    int getLevel() const { return level; }
    int getHitpoints() const { return hitpoints; }
    const string& getCharName() const { return charName; }

    int getStr() const { return str; }
    int getDex() const { return dex; }
    int getCon() const { return con; }
    int getInt() const { return inte; }
    int getWis() const { return wis; }
    int getCha() const { return cha; }
};

//fighter
class Fighter : public Character {
protected:
    int rollingDice() const override {
        return 10;
    }

public:
    Fighter(int level = 1)
        : Character("Fighter", 16, 12, 14, 10, 11, 9, level)
    {
        maxHitpoints = calculateHP();
        hitpoints = maxHitpoints;
    }

    void showStats() const override {
        Character::showStats();
        cout << "Fighters are best at melee combat and using heavy armor. Their damage primarily is based off of their strength ability score.\n";
    }

    void attack(Character& target) const override {
        int damage = 1 + getMod(str) + (rand() % rollingDice());
        if (damage < 1) damage = 1;
        cout << charName << " slices with their sword. Rolling for hit.\n";
        int damageRoll = rand() % 21;
        if (damageRoll >= 14) {
            cout << "The hit is successful! You do " << damage << " damage!\n";
            target.takeDamage(damage);
        }
        else {
            cout << "The hit is a fail.\n";
        }
    }
};

//wizard
class Wizard : public Character {
protected:
    int rollingDice() const override {
        return 6;
    }

    int mana;

public:
    Wizard(int level = 1)
        : Character("Wizard", 8, 14, 10, 18, 13, 12, level), mana(10 * level)
    {
        maxHitpoints = calculateHP();
        hitpoints = maxHitpoints;
    }

    void showStats() const override {
        Character::showStats();
        cout << "Wizards are best at magical combat and spell casting. Their damage primarily is based off of their intelligence ability score.\n";
    }

    void attack(Character& target) const override {
        int spellDamage = max(1, 1 + getMod(inte) + (rand() % rollingDice()));
        if (spellDamage < 1) spellDamage = 1;
        cout << charName << " casts a fireball. Rolling for hit.\n";
        int damageRoll = rand() % 21;
        if (damageRoll >= 14) {
            cout << "The hit is successful! You do " << spellDamage << " damage!\n";
            target.takeDamage(spellDamage);
        }
        else {
            cout << "The hit is a fail.\n";
        }
    }

    void levelUp() override {
        Character::levelUp();
        mana += 10;
        cout << charName << "'s mana points are increased to a total of " << mana << "\n";
    }
};

//rogue
class Rogue : public Character {
protected:
    int rollingDice() const override {
        return 8;
    }

public:
    Rogue(int level = 1)
        : Character("Rogue", 12, 18, 12, 13, 10, 14, level)
    {
        maxHitpoints = calculateHP();
        hitpoints = maxHitpoints;
    }

    void showStats() const override {
        Character::showStats();
        cout << "Rogues are best at stealth and quick strikes. Their damage primarily is based off of their dexterity ability score.\n";
    }

    void attack(Character& target) const override {
        int damage = 1 + getMod(dex) + (rand() % rollingDice());
        if (damage < 1) damage = 1;
        cout << charName << " stabs with their knife. Rolling for hit.\n";
        int damageRoll = rand() % 21;
        if (damageRoll >= 14) {
            cout << "The hit is successful! You do " << damage << " damage!\n";
            target.takeDamage(damage);
        }
        else {
            cout << "The hit is a fail.\n";
        }
    }
};

//eneym class
class Goblin : public Character {
protected:
    int rollingDice() const override {
        return 6;
    }

public:
    Goblin(int level = 1)
        : Character("Goblin", 10, 14, 10, 8, 7, 6, level)
    {
        maxHitpoints = calculateHP();
        hitpoints = maxHitpoints;
    }

    void attack(Character& target) const override {
        int damage = 1 + getMod(str) + (rand() % rollingDice());
        if (damage < 1) damage = 1;
        cout << "Goblin slashes with its crude dagger. Rolling for hit.\n";
        int damageRoll = rand() % 21;
        if (damageRoll >= 12) {
            cout << "The hit is successful! Goblin deals " << damage << " damage!\n";
            target.takeDamage(damage);
        }
        else {
            cout << "The Goblin's attack misses.\n";
        }
    }
};

//pause breaks between combta
void waitForUser() {
    while (true) {
        cout << "Type 'y' and press enter to advance combat: ";
        string input;
        getline(cin, input);
        if (!input.empty() && (input[0] == 'y' || input[0] == 'Y')) break;
    }
}

//combat loop
void combat(Character& player, Character& enemy) {
    while (player.getHitpoints() > 0 && enemy.getHitpoints() > 0) {
        cout << "\nRolling for your next hit...\n";
        waitForUser();
        player.attack(enemy);
        if (enemy.getHitpoints() <= 0) break;

        cout << "\nEnemy is preparing to attack...\n";
        waitForUser();
        enemy.attack(player);
    }

    if (player.getHitpoints() > 0) {
        cout << player.getCharName() << " has won the battle!\n";
    }
    else {
        cout << enemy.getCharName() << " has won the battle!\n";
    }
}

//main
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int selectedClass;
    cout << "Before we begin, please choose your class.\n 1. Rogue\n 2. Fighter\n 3. Wizard\n (Enter the corresponding number)\n";
    cin >> selectedClass;
    cin.ignore();

    Character* player = nullptr;

    switch (selectedClass) {
    case 1:
        player = new Rogue();
        cout << "Rogue. A wise choice. You favor quick strikes.\n";
        break;
    case 2:
        player = new Fighter();
        cout << "Fighter. A strong choice. You excel in melee combat.\n";
        break;
    case 3:
        player = new Wizard();
        cout << "Wizard. A wise choice. You command the arcane.\n";
        break;
    default:
        cout << "Invalid selection. Please restart the program.\n";
        return 1;
    }

    player->showStats();

    const int fightsPerLevel = 3;
    int fightsWon = 0;

    while (true) {
        Character* enemy = new Goblin(1);
        cout << "\nA wild goblin appears! Prepare yourself for a new battle.\n";

        combat(*player, *enemy);
        delete enemy;

        if (player->getHitpoints() <= 0) {
            cout << "You have been defeated... Game over.\n";
            break;
        }

        //let the player heal (im not a mean guy)
        player->healFull();

        fightsWon++;
        if (fightsWon % fightsPerLevel == 0) {
            cout << "\nYou have fought bravely in " << fightsWon << " fights and gained a level!\n";
            player->levelUp();
        }

        cout << "\nPrepare for the next fight!\n";
    }

    return 0;
}
