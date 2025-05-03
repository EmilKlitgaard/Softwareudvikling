#include <vector>
#include <cstdlib>
#include <ctime>

#include "MonsterFactory.h"

using namespace std;

Monster MonsterFactory::createMonster(int heroLevel) {
    vector<string> types = {"Goblin", "Orc", "Troll", "Dragon"};
    vector<string> adjectives = {"Weak", "Strong", "Fierce"};

    string type = types[rand() % types.size()];
    string adj = adjectives[rand() % adjectives.size()];
    string name = adj + " " + type;

    int baseHp = 20 + heroLevel * 5;
    int strength = 5 + heroLevel;
    int xp = 10 + heroLevel * 2;

    if (adj == "Strong") strength += 5;
    if (adj == "Weak") strength -= 2;

    if (type == "Dragon") baseHp += 50;
    else if (type == "Goblin") baseHp -= 5;

    return Monster(name, baseHp, strength, xp);
}
