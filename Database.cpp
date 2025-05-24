#include "Database.h"
#include "Hero.h"
#include <iostream>

Database::Database(const string &databaseFile) {
    if (sqlite3_open(databaseFile.c_str(), &database) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(database) << endl;
    } else {
        cout << "Initializing database." << endl;
        initializeDatabase();
    }
}

Database::~Database() {
    sqlite3_close(database);
}

void Database::initializeDatabase() {
    const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS heroes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE,
            level INTEGER NOT NULL,
            hp INTEGER NOT NULL,
            strength INTEGER NOT NULL,
            xp INTEGER DEFAULT 0,
            gold INTEGER DEFAULT 0,
            current_weapon_id INTEGER,
            defeated BOOLEAN DEFAULT FALSE,
            monsters_defeated INTEGER DEFAULT 0,
            FOREIGN KEY (current_weapon_id) REFERENCES weapons(id)
        );
        CREATE TABLE IF NOT EXISTS weapons (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            damage INTEGER NOT NULL,
            strength_modifier INTEGER NOT NULL,
            durability INTEGER NOT NULL,
            hero_id INTEGER NOT NULL,
            monsters_defeated INTEGER DEFAULT 0,
            FOREIGN KEY (hero_id) REFERENCES heroes(id)
        );
    )";
    sqlite3_exec(database, createTableSQL, nullptr, nullptr, nullptr);
}

// ----- ANALYSIS FUNCTIONS ----- //
// 1) Alfabetisk liste over helte
void Database::getHeroesOrderedByName() {
    const char *sql = R"(
        SELECT name, level, hp, strength, xp, gold, defeated
        FROM heroes
        ORDER BY name ASC;
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "\nHeroes:\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *name     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int         level    = sqlite3_column_int(stmt, 1);
            int         hp       = sqlite3_column_int(stmt, 2);
            int         strength = sqlite3_column_int(stmt, 3);
            int         xp       = sqlite3_column_int(stmt, 4);
            int         gold     = sqlite3_column_int(stmt, 5);
            bool        defeated = sqlite3_column_int(stmt, 6) != 0;
            cout << "- " << name << " | Level: "<< level << " | HP: " << hp << " | Strength: " << strength << " | Xp: " << xp << " | Gold: " << gold << (defeated ? " [DEFEATED]" : "") << endl;
        }
        sqlite3_finalize(stmt);
    }
}

// 2) Hvor mange monstre hver hero har besejret 
void Database::getTotalMonstersDefeatedByHero() {
    const char *sql = R"(
        SELECT name, monsters_defeated
        FROM heroes
        ORDER BY name ASC;
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "\nMonsters defeated by hero:\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int kills = sqlite3_column_int(stmt, 1);
            cout << "- " << name << ": " << kills << "\n";
        }
        sqlite3_finalize(stmt);
    }
}

// 3) For en given hero: hvor mange monstre hvert våben har besejret
void Database::getMonstersDefeatedByWeapon(vector<Hero> &heroes) {
    for (Hero hero : heroes) {
        string heroName = hero.getName();
        const char *sql = R"(
            SELECT w.name, w.monsters_defeated
            FROM weapons w
            JOIN heroes h ON w.hero_id = h.id
            WHERE h.name = ?
            ORDER BY w.monsters_defeated DESC;
        )";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, heroName.c_str(), -1, SQLITE_STATIC);
            cout << "\nMonsters defeated with each weapon welded by '" << heroName << "':\n";
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                string wname = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
                int cnt = sqlite3_column_int(stmt,1);
                cout << "- " << wname << ": " << cnt << "\n";
            }
            sqlite3_finalize(stmt);
        }
        cout << endl;
    }
}

// 4) For hvert våben: hvilken hero har besejret flest monstre med det våben
void Database::getTopHeroPerWeapon() {
    const char *sql = R"(
        SELECT w.name, h.name, w.monsters_defeated
        FROM weapons w
        JOIN heroes h ON w.hero_id = h.id
        WHERE w.rowid = (
            SELECT rowid
            FROM weapons w2
            WHERE w2.name = w.name
            ORDER BY w2.monsters_defeated DESC
            LIMIT 1
        )
        ORDER BY w.name;
    )";
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "\nHero with most defeats for each weapon:\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            string weaponName = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
            string heroName = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
            int cnt = sqlite3_column_int(stmt,2);
            cout << "- " << weaponName << ": \t" << heroName << " (" << cnt << ")\n";
        }
        sqlite3_finalize(stmt);
    }
}

Weapon Database::getWeapon(const int weaponId) {
    const char *sql = R"(
        SELECT name, damage, strength_modifier, durability, hero_id, monsters_defeated
        FROM weapons
        WHERE id = ?;
    )";
    sqlite3_stmt *stmt;
    Weapon weapon;
    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, weaponId);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *name         = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int damage               = sqlite3_column_int(stmt, 1);
            int strengthModifier     = sqlite3_column_int(stmt, 2);
            int durability           = sqlite3_column_int(stmt, 3);
            int heroId               = sqlite3_column_int(stmt, 4);
            int monstersDefeated     = sqlite3_column_int(stmt, 5);
            weapon = Weapon(name, damage, strengthModifier, durability);
            weapon.setId(weaponId);
        } else {
            std::cerr << "No weapon found with id: " << weaponId << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing getWeapon: " << sqlite3_errmsg(database) << std::endl;
    }
    return weapon;
}


// ----- SETTER FUNCTIONS ----- //
void Database::incrementMonsterDefeated(int heroId, int weaponId) {
    sqlite3_stmt *stmt;
    // 1) Hero’s total kills
    const char *sql1 = R"(
        UPDATE heroes
        SET monsters_defeated = monsters_defeated + 1
        WHERE id = ?;
    )";
    sqlite3_prepare_v2(database, sql1, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, heroId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    // 2) Weapon’s own kills
    const char *sql2 = R"(
        UPDATE weapons
        SET monsters_defeated = monsters_defeated + 1
        WHERE id = ?;
    )";
    sqlite3_prepare_v2(database, sql2, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, weaponId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void Database::decrementWeaponDurability(int weaponId) {
    sqlite3_stmt *stmt;
    const char *sql = R"(
        UPDATE weapons
        SET durability = durability - 1
        WHERE id = ? AND durability > 0;
    )";
    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, weaponId);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << endl;
    }
}


void Database::saveHero(const Hero &hero) {
    const char *insertSQL = R"(
        INSERT INTO heroes (name, level, hp, strength, xp, gold, current_weapon_id)
        VALUES (?, ?, ?, ?, ?, ?, ?)
        ON CONFLICT(name) DO UPDATE SET
            level=excluded.level,
            hp=excluded.hp,
            strength=excluded.strength,
            xp=excluded.xp,
            gold=excluded.gold,
            current_weapon_id=excluded.current_weapon_id;
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, hero.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, hero.getLevel());
        sqlite3_bind_int(stmt, 3, hero.getHp());
        sqlite3_bind_int(stmt, 4, hero.getStrength());
        sqlite3_bind_int(stmt, 5, hero.getXp());
        sqlite3_bind_int(stmt, 6, hero.getGold());
        sqlite3_bind_int(stmt, 7, hero.getCurrentWeaponId()); // Save the current weapon ID
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error saving hero: " << sqlite3_errmsg(database) << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(database) << endl;
    }
}

int Database::saveWeapon(const Weapon &weapon, int heroId) {
    const char *insertSQL = R"(
        INSERT INTO weapons (name, damage, strength_modifier, durability, hero_id)
        VALUES (?, ?, ?, ?, ?);
    )";
    sqlite3_stmt *stmt;
    int weaponId;

    if (sqlite3_prepare_v2(database, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, weapon.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int (stmt, 2, weapon.getDamage());
        sqlite3_bind_int (stmt, 3, weapon.getStrengthModifier());
        sqlite3_bind_int (stmt, 4, weapon.getDurability());
        sqlite3_bind_int (stmt, 5, heroId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error saving weapon: " << sqlite3_errmsg(database) << std::endl;
        } else {
            weaponId = static_cast<int>(sqlite3_last_insert_rowid(database));
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(database) << std::endl;
    }
    return weaponId;
}

void Database::loadHeroes(vector<Hero> &heroes) {
    const char *selectSQL = R"(
        SELECT id, name, level, hp, strength, xp, gold, current_weapon_id
        FROM heroes
        WHERE defeated = FALSE;
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            int level = sqlite3_column_int(stmt, 2);
            int hp = sqlite3_column_int(stmt, 3);
            int strength = sqlite3_column_int(stmt, 4);
            int xp = sqlite3_column_int(stmt, 5);
            int gold = sqlite3_column_int(stmt, 6);
            int currentWeaponId = sqlite3_column_int(stmt, 7);

            Hero hero(name, level, hp, strength, xp, gold, currentWeaponId);
            hero.setId(id);
            if (currentWeaponId > 0) {
                Weapon weapon = getWeapon(currentWeaponId);
                hero.equipWeapon(weapon);
            }
            heroes.push_back(hero);
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error loading heroes: " << sqlite3_errmsg(database) << endl;
    }
}

void Database::heroDefeated(const Hero &hero) {
    const char *insertSQL = R"(
        UPDATE heroes 
        SET defeated = TRUE
        WHERE name = ?
    )";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(database, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, hero.getName().c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Error saving hero: " << sqlite3_errmsg(database) << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(database) << endl;
    }
}