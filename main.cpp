#include <iostream>
#include <vector>
#include <unistd.h>

#include "Game.h"
#include "Hero.h"
#include "Enemy.h"
#include "Database.h"

using namespace std;

int main(){
    vector<Hero> heroes;
    vector<Enemy> enemies;
    Database database("SQL_Database");
    Game game(heroes, enemies, database);
    return game.start();
}   
