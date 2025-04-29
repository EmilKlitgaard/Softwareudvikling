#pragma once

#include <string>

using namespace std;

class Enemy {
    public:
        Enemy();
        ~Enemy();

        Enemy(const string, const int, const int, const int);
        
        string getName();
        int getHp();
        int getStrength();
        int getXp();

    private:
        string name;
        int hp;
        int strength;
        int xp;
};

