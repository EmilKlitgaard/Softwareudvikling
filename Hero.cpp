#include <iostream>

#include "Hero.h"

Hero::Hero() 
    : name("Default"), level(1), hp(10), strength(2), xp(0), gold(0) {}
    
Hero::Hero(const string newName, const int newLevel, const int newHp, const int newStrength, const int newXp, const int newGold)
    : name(newName), level(newLevel), hp(newHp), strength(newStrength), xp(newXp), gold(newGold) {}

Hero::~Hero() {}

string Hero::getName() const { return name; }
int Hero::getHp() const { return hp; }
int Hero::getStrength() const { return strength; }
int Hero::getXp() const { return xp; }
int Hero::getLevel() const { return level; }
int Hero::getGold() const { return gold; }

void Hero::addXp(int addXp) {
    xp += addXp;
}

void Hero::addGold(int addGold) {
    gold += addGold;
}

int Hero::levelUp() {
    xp -= level * 1000;
    level++;
    strength += 1;
    hp += 2;
    cout << name << " leveled up to " << level << "!" << endl;
    return level;
}

void Hero::equipWeapon(const Weapon &newWeapon) {
    weapon = newWeapon;
}

Weapon Hero::getWeapon() const {
    return weapon;
}