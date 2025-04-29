#pragma once

#include <vector>
#include <string>

#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"

using namespace std;

enum State { 
    MENU,
    CREATE_HERO,
    LOAD_HERO,
    SELECT_ENEMY,
    SHOW_STATS,
    ADVENTURE,
    START_BATTLE,
    POST_BATTLE,
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
        
    private:
        vector<Hero> heroes;
        vector<Enemy> enemies;
        
        int currentHero = -1; 
        int currentEnemy = -1;
        int userInput = -1;
        
        bool gameStart = true;
        bool battleWon;
        
        State STATE = MENU;
};
