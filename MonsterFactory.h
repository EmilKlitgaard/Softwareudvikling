#pragma once

#include <vector>

#include "Monster.h"

using namespace std;

class MonsterFactory {
    public:
        static Monster createMonster(int heroLevel);
        static vector<Monster> createMonsterGroup(int heroLevel, int count);
};
