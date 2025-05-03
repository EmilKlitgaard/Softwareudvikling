#pragma once

#include <vector>

#include "Monster.h"

using namespace std;

class Dungeon {
    public:
        Dungeon(string name, int gold, vector<Monster> enemies);

        void display() const;
        vector<Monster>& getEnemies();
        int getGold() const;
        string getName() const;

    private:
        string name;
        int gold;
        vector<Monster> enemies;
};
