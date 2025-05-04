#pragma once

#include <string>

#include "Hero.h"
#include "Opponent.h"

class Battle {
    public:
        Battle(Hero &newHero, const Opponent &opponent);
        ~Battle();

        bool startBattle();
        void awaitEnter();

    private:
        Hero &hero;
        const Opponent &opponent;
};

