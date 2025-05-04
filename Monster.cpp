#include "Monster.h"
#include <iostream>

using namespace std;

Monster::Monster(string name, int hp, int strength, int xp)
    : Opponent(name, hp, strength, xp) {}

Monster::~Monster() {}

void Monster::display() const {
    cout << "- " << getName() << " (HP: " << getHp() << ", Strength: " << getStrength() << ", XP: " << getXp() << ")" << endl;
}