#include "Database.h"
#include "Hero.h"
#include <iostream>

Database::Database(const string &databaseFile) {
    if (sqlite3_open(databaseFile.c_str(), &database) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(database) << endl;
    }
}

Database::~Database() {
    sqlite3_close(database);
}

void Database::initializeDatabase() {
    const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS heroes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            level INTEGER,
            hp INTEGER,
            strength INTEGER,
            xp INTEGER,
            gold INTEGER
        );
    )";
    sqlite3_exec(database, createTableSQL, nullptr, nullptr, nullptr);
}

// Implement saveHero, loadHeroes, and analyzeGame...