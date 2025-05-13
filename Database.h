#pragma once

#include <string>
#include <sqlite3.h>

using namespace std;

class Database {
    public:
        Database(const string &databaseFile);
        ~Database();

        void initializeDatabase();
        void saveHero(const Hero &hero);
        void loadHeroes(vector<Hero> &heroes);
        void analyzeGame();

    private:
        sqlite3 *database;
};