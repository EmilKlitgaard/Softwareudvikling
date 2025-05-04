#include "Opponent.h"

Opponent::Opponent(string name, int hp, int strength, int xp)
    : name(name), hp(hp), strength(strength), xp(xp) {}

Opponent::~Opponent() {}

string Opponent::getName() const { return name; }
int Opponent::getHp() const { return hp; }
int Opponent::getStrength() const { return strength; }
int Opponent::getXp() const { return xp; }

void Opponent::takeDamage(int damage) { hp -= damage; }
bool Opponent::isAlive() const { return hp > 0; }