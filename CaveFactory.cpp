#include <cstdlib>
#include <ctime>

#include "CaveFactory.h"

using namespace std;

Cave CaveFactory::createCave(int heroLevel) {
    vector<Monster> monsters;
    int numMonsters = 2 + rand() % 4;

    for (int i = 0; i < numMonsters; ++i) {
        monsters.push_back(MonsterFactory::createMonster(heroLevel));
    }

    string name = "Cave of Doom " + to_string(rand() % 100);
    int goldReward = 50 + heroLevel * 10;

    return Cave(name, goldReward, monsters);
}
