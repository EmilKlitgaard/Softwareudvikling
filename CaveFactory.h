#pragma once

#include "Cave.h"
#include "MonsterFactory.h"

using namespace std;

class CaveFactory {
    public:
        static Cave createCave(int heroLevel);
};
