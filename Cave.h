#pragma once

#include <vector>

#include "Monster.h"

using namespace std;

class Cave {
    public:
        Cave(string name, int level, int gold, vector<Monster> enemies);

        void display() const;
        
        string getName() const;
        int getLevel();
        int getGold() const;
        
        const vector<Monster>& getMonsters() const;

    private:
        string name;
        int level;
        int gold;
        vector<Monster> monsters;
};
