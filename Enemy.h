#pragma once

#include "Opponent.h"

class Enemy : public Opponent {
    public:
        Enemy(string name, int hp, int strength, int xp);
        ~Enemy();
};