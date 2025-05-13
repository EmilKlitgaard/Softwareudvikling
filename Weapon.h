#pragma once

#include <string>

using namespace std;

class Weapon {
    public:
        Weapon();
        Weapon(string name, int damage, int strengthModifier, int durability);
        ~Weapon();

        string getName() const;
        int getDamage() const;
        int getStrengthModifier() const;
        int getDurability() const;

        void useWeapon();
        bool isBroken() const;

    private:
        string name;
        int damage;
        int strengthModifier;
        int durability;
};