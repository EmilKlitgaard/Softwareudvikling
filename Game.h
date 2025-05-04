#pragma once

#include <vector>
#include <string>

#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"
#include "Cave.h"
#include "Monster.h"
#include "Factory.h"

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
    EXIT
};

class Game {
    public:
        Game(vector<Hero> &heroes, vector<Enemy> &enemies);
        ~Game();
        
        int start();
        void menu();
        void showStats();
        void adventure();
        void clearScreen();
        void createHero();
        int loadHero();
        int selectEnemy();
        int selectCave();
        void gameOver();
        void startCave();
        
        void saveHeroesToFile(const string &filename = "Heroes.txt");
        void loadHeroesFromFile(const string &filename = "Heroes.txt");

    private:
        vector<Hero> &heroes;
        vector<Enemy> enemies;
        vector<Cave> caves;
        
        int currentHero = -1; 
        int currentEnemy = -1;
        int currentCave = -1;
        int userInput = -1;
        
        bool gameStart = true;
        bool battleWon;
        
        State STATE = MENU;
};
