#include <iostream>

#include "Hero.h"

Hero::Hero() 
    : name("Default"), level(1), hp(10), strength(2), xp(0) {}
    
Hero::Hero(const string newName, const int newLevel, const int newHp, const int newStrength, const int newXp)
    : name(newName), level(newLevel), hp(newHp), strength(newStrength), xp(newXp) {}

Hero::~Hero() {}

string Hero::getName() const {
    return name;
}

int Hero::getHp() const {
    return hp;
}

int Hero::getStrength() const {
    return strength;
}

int Hero::getXp() const {
    return xp;
}

int Hero::getLevel() const {
    return level;
}

void Hero::addXp(int addXp) {
    xp += addXp;
}

int Hero::levelUp() {
    xp -= level * 1000;
    level++;
    strength += 1;
    hp += 2;
    cout << name << " leveled up to " << level << "!" << endl;
    return level;
}
