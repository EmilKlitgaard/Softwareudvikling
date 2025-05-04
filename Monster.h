#pragma once

#include "Opponent.h"

class Monster : public Opponent {
    public:
        Monster(string name, int hp, int strength, int xp);
        ~Monster();

        void display() const;
};

