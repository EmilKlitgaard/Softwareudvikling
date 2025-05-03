#include <cstdlib>
#include <ctime>

#include "Factory.h"

Monster Factory::createMonster(int level) {
    vector<string> adjectives = {"Weak", "Fierce", "Strong"};
    vector<string> types = {"Goblin", "Orc", "Troll", "Dragon"};

    string name = adjectives[rand() % adjectives.size()] + " " + types[rand() % types.size()];
    int hp = 20 + rand() % (level * 10);
    int strength = 5 + rand() % (level * 2);
    int xp = 10 + rand() % (level * 5);

    return Monster(name, hp, strength, xp);
}

Dungeon Factory::createCave(const Hero& hero) {
    srand(time(0));

    int level = hero.getLevel();
    int numMonsters = 1 + rand() % 5;
    int goldReward = 50 + level * 20;

    vector<Monster> monsters;
    for (int i = 0; i < numMonsters; ++i) {
        monsters.push_back(createMonsterForLevel(level));
    }

    string dungeonName = "Cave of Level " + to_string(level);
    return Dungeon(dungeonName, goldReward, monsters);
}

