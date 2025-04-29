#pragma once

#include <string>

#include "Hero.h"
#include "Enemy.h"

class Battle {
    public:
        Battle(Hero &newHero, Enemy &newEnemy);
        ~Battle();

        void startBattle();
        void gameOver();

    private:
        Hero &hero;
        Enemy &enemy;
};

