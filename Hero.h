#pragma once

#include <string>

using namespace std;

class Hero {
    public:
        Hero();
        ~Hero();
        
        Hero(const string, const int, const int, const int, const int, const int);
        
        string getName() const;
        int getLevel() const;
        int getHp() const;
        int getStrength() const;
        int getXp() const;
        int getGold() const;
        
        void addXp(const int);
        void addGold(const int);

        int levelUp();
        
    private:
        string name;
        int level;
        int hp;
        int strength;
        int xp;
        int gold;
    };
