#pragma once

#include <vector>
#include <string>

#include "Hero.h"

using namespace std;

enum State { 
    MENU,
    CREATE_HERO,
    LOAD_HERO,
    LOAD_ENEMY,
    START_ADVENTURE,
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
        void clearScreen();
        void createHero(vector<Hero> &heroes);
        int loadHero(vector<Hero> &heroes);
        int enemyLoad(vector<Enemy> &enemies); 
        int startAdventure();
        int Adventure();
        
    private:
        vector<Hero> heroes;
        vector<Enemy> enemies;
        
        int currentHero = -1; 
        int currentEnemy = -1;
        int userInput = -1;
        
        State STATE = MENU;
};
