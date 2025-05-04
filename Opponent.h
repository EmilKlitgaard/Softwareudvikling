#pragma once

#include <string>

using namespace std;

class Opponent {
    public:
        Opponent(string name, int hp, int strength, int xp);
        virtual ~Opponent();

        string getName() const;
        int getHp() const;
        int getStrength() const;
        int getXp() const;

        void takeDamage(int damage);
        bool isAlive() const;

    protected:
        string name;
        int hp;
        int strength;
        int xp;
};