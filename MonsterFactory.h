#pragma once
#include "Monster.h"
#include <vector>

using namespace std;

class MonsterFactory {
    public:
        static Monster createMonster(int heroLevel);
        static vector<Monster> createMonsterGroup(int heroLevel, int count);
};
