#include <iostream>

#include "Monster.h"

using namespace std;

Monster::Monster(string name, int hp, int strength, int xp)
    : name(name), hp(hp), strength(strength), xp(xp) {}

void Monster::display() const {
    cout << name << " (HP: " << hp << ", STR: " << strength << ", XP: " << xp << ")\n";
}

int Monster::getHp() const { return hp; }
int Monster::getStrength() const { return strength; }
int Monster::getXp() const { return xp; }
string Monster::getName() const { return name; }
