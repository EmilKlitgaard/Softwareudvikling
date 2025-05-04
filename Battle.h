#pragma once

#include <string>

#include "Hero.h"
#include "Enemy.h"
#include "Monster.h"

class Battle {
    public:
        Battle(Hero &newHero, Enemy &newEnemy);
        Battle(Hero &newHero, const Monster &newMonster);
        ~Battle();

        bool startBattle();
        void awaitEnter();

    private:
        Hero &hero;
        Enemy *enemy = nullptr;
        const Monster *monster = nullptr;
};

