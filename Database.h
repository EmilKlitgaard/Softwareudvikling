#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

#include "Hero.h"

using namespace std;

class Database {
    public:
        Database(const string &databaseFile);
        ~Database();

        void initializeDatabase();
        void saveHero(const Hero &hero);
        int saveWeapon(const Weapon &weapon, int heroId);
        void loadHeroes(vector<Hero> &heroes);
        void heroDefeated(const Hero &hero);

        void incrementMonsterDefeated(int heroId, int weaponId);
        void decrementWeaponDurability(int weaponId);

        void getHeroesOrderedByName();
        void getTotalMonstersDefeatedByHero();
        void getMonstersDefeatedByWeapon(vector<Hero> &heroes);
        void getTopHeroPerWeapon();
        Weapon getWeapon(const int weaponId);

    private:
        sqlite3 *database;
};