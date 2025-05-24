#pragma once

#include <vector>
#include <string>

#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"
#include "Cave.h"
#include "Monster.h"
#include "Factory.h"
#include "Weapon.h"
#include "Database.h"

using namespace std;

enum State { 
    MENU,
    CREATE_HERO,
    LOAD_HERO,
    SELECT_ENEMY,
    SELECT_CAVE,
    SHOW_STATS,
    ADVENTURE,
    START_BATTLE,
    POST_BATTLE,
    START_CAVE,
    ANALYSIS,
    EXIT
};

class Game {
    public:
        Game(vector<Hero> &heroes, vector<Enemy> &enemies, Database &database);
        ~Game();
        
        int start();
        void menu();
        void showStats();
        void adventure();
        void createHero();
        int loadHero();
        int selectEnemy();
        int selectCave();
        void gameOver();
        void startCave();
        void analysis();

        void clearScreen();
        void postBattle();

    private:
        vector<Hero> &heroes;
        vector<Enemy> &enemies;
        vector<Cave> caves;
        vector<Weapon> weapons;
        Database &database;
        
        int currentHero = -1; 
        int currentEnemy = -1;
        int currentCave = -1;
        int userInput = -1;
        
        bool gameStart = true;
        bool battleWon;
        
        State STATE = MENU;
};
