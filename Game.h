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
        Game();
        ~Game();
        
        int start();
        void menu();
        void showStats(vector<Hero> &heroes);
        void adventure();
        void clearScreen();
        void createHero(vector<Hero> &heroes);
        int loadHero(vector<Hero> &heroes);
        int selectEnemy(vector<Enemy> &enemies);
        int selectCave(vector<Hero> &heroes);
        void gameOver(vector<Hero> &heroes);
        
        void saveHeroesToFile(vector<Hero> &heroes, const string &filename = "Heroes.txt");
        void loadHeroesFromFile(vector<Hero> &heroes, const string &filename = "Heroes.txt");

    private:
        vector<Hero> heroes;
        vector<Enemy> enemies;
        
        int currentHero = -1; 
        int currentEnemy = -1;
        int currentCave = -1;
        int userInput = -1;
        
        bool gameStart = true;
        bool battleWon;
        
        State STATE = MENU;
};
