#pragma once

#include <string>

#include "Hero.h"
#include "Enemy.h"

class Battle {
    public:
        Battle(Hero &newHero, Enemy &newEnemy);
        ~Battle();

        bool startBattle();
        void gameOver();
        void awaitEnter();

    private:
        Hero &hero;
        Enemy &enemy;
};

