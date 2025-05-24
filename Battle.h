#pragma once

#include <string>

#include "Hero.h"
#include "Opponent.h"
#include "Database.h"

class Battle {
    public:
        Battle(Hero &newHero, const Opponent &opponent, Database &database);
        ~Battle();

        bool startBattle();
        void awaitEnter();

    private:
        Hero &hero;
        const Opponent &opponent;
        Database &database;
};

