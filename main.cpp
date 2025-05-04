#include <iostream>
#include <vector>
#include <unistd.h>

#include "Game.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;

int main(){
    vector<Hero> heroes;
    vector<Enemy> enemies;
    Game game(heroes, enemies);
    return game.start();
}   
