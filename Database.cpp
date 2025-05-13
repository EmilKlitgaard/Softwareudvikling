#include "Database.h"
#include "Hero.h"
#include <iostream>

Database::Database(const string &databaseFile) {
    if (sqlite3_open(databaseFile.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void DatabaseManager::initializeDatabase() {
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
    sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);
}

// Implement saveHero, loadHeroes, and analyzeGame...