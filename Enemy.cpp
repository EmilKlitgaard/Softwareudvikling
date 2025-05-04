#include "Enemy.h"

Enemy::Enemy(string name, int hp, int strength, int xp)
    : Opponent(name, hp, strength, xp) {}

Enemy::~Enemy() {}