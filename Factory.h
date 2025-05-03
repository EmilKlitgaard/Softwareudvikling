#pragma once

#include <string>
#include <vector>

#include "Monster.h"
#include "Cave.h"
#include "Hero.h"

using namespace std;

class Factory {
    public:
        static Monster createMonster(int level);
        static Cave createCave(const Hero &hero);
};

