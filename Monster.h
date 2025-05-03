#pragma once

#include <string>

using namespace std;

class Monster {
    public:
        Monster(string name, int hp, int strength, int xp);

        void display() const;

        int getHp() const;
        int getStrength() const;
        int getXp() const;
        string getName() const;
        
    private:
        string name;
        int hp;
        int strength;
        int xp;
};

