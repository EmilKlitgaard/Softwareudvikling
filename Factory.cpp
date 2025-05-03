#include "Factory.h"

Monster Factory::createMonster(int level) {
    vector<string> adjectives = {"Weak", "Fierce", "Strong"};
    vector<string> types = {"Goblin", "Orc", "Troll", "Unicorn", "Dragon"};

    string adjective = adjectives[rand() % adjectives.size()];
    string type = types[rand() % types.size()];
    string name = adjective + " " + type;
    
    int hp = 20 + rand() % (level * 10);
    int strength = 5 + rand() % (level * 2);
    int xp = 10 + rand() % (level * 5);
    
    if (adjective == "Weak") strength -= 2;
    else if (adjective == "Fierce") strength += 1;
    else if (adjective == "Strong") strength += 2;

    if (type == "Goblin") hp -= 15;
    else if (type == "Orc") hp -= 5;
    else if (type == "Troll") hp += 2;
    else if (type == "Unicorn") hp += 10;
    else if (type == "Dragon") hp += 50;

    return Monster(name, hp, strength, xp);
}

Cave Factory::createCave(const Hero& hero) {
    int level = hero.getLevel();
    int numMonsters = 1 + rand() % 5;
    int goldReward = 50 + level * 20;

    vector<Monster> monsters;
    for (int i = 0; i < numMonsters; ++i) {
        monsters.push_back(createMonster(level));
    }

    string caveName = "Cave of Level " + to_string(level);
    return Cave(caveName, goldReward, monsters);
}

