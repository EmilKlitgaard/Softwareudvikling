#pragma once

#include <string>

using namespace std;

class Hero {
    public:
        Hero();
        ~Hero();
        
        Hero(const string, const int, const int, const int, const int);
        
        string getName();
        int getHp();
        int getStrength();
        int getXp();
        int getLevel();
        
        void addXp(const int);
        int levelUp();
        
    private:
        string name;
        int level;
        int hp;
        int strength;
        int xp;
    };
