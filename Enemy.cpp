#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
    : name("Enemy"), hp(10), strength(2), xp(0) {}

Enemy::Enemy(const string newName, const int newHp, const int newStrength, const int newXp)
    : name(newName), hp(newHp), strength(newStrength), xp(newXp) {}

Enemy::~Enemy() {}

string Enemy::getName() {
    return name;
}

int Enemy::getHp() {
    return hp;
}

int Enemy::getStrength() {
    return strength;
}

int Enemy::getXp() {
    return xp;
}

