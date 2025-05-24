#pragma once

#include <string>

#include "Weapon.h"

using namespace std;

class Hero {
    public:
        Hero();
        ~Hero();
        
        Hero(const string, const int, const int, const int, const int, const int, const int);
        
        string getName() const;
        int getLevel() const;
        int getHp() const;
        int getStrength() const;
        int getXp() const;
        int getGold() const;
        int getId() const;
        int getCurrentWeaponId() const;
        Weapon &getWeapon();
        
        void addXp(const int);
        void addGold(const int);

        int levelUp();

        void equipWeapon(Weapon &weapon);
        void unequipWeapon();
        bool haveWeapon();

        void setId(int id);
        void setCurrentWeaponId(int weaponId);
        
    private:
        string name;
        int level;
        int hp;
        int strength;
        int xp;
        int gold;
        int heroId;

        Weapon weapon;
        int currentWeaponId; // ID of the currently equipped weapon
    };
