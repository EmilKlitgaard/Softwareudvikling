#pragma once

#include <string>

using namespace std;

class Database;

class Weapon {
    public:
        Weapon();
        Weapon(string name, int damage, int strengthModifier, int durability);
        ~Weapon();

        string getName() const;
        int getDamage() const;
        int getStrengthModifier() const;
        int getDurability() const;
        int getId() const;

        void useWeapon(Database &database);
        bool isBroken() const;

        void setId(const int id);

    private:
        string name;
        int damage;
        int strengthModifier;
        int durability;
        int weaponId;
};