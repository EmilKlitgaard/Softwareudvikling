#include "Factory.h"

Monster Factory::createMonster(int level) {
    vector<string> adjectives = {"Weak", "Fierce", "Strong"};
    vector<string> types = {"Goblin", "Orc", "Troll", "Unicorn", "Dragon"};

    string adjective = adjectives[rand() % adjectives.size()];
    string type = types[rand() % types.size()];
    string name = adjective + " " + type;
    
    int hp = 5 + rand() % (level * 10);
    int strength = 1 + rand() % (level * 2);
    int xp = 100 + rand() % (level * 150);
    
    if (adjective == "Weak") strength -= 2;
    else if (adjective == "Fierce") strength += 1;
    else if (adjective == "Strong") strength += 2;

    if (type == "Goblin") hp -= 10;
    else if (type == "Orc") hp -= 5;
    else if (type == "Troll") hp += 2;
    else if (type == "Unicorn") hp += 10;
    else if (type == "Dragon") hp += 20;

    strength = max(strength, 1);
    hp = max(hp, 1);
    xp = max(xp, 1);

    return Monster(name, hp, strength, xp);
}

Cave Factory::createCave(const Hero &hero) {
    int caveLevel = 1 + rand() % (hero.getLevel() * 2);
    int numMonsters = 1 + rand() % 5;
    int gold = 50 + caveLevel * 20;

    vector<Monster> monsters;
    for (int i = 0; i < numMonsters; ++i) {
        monsters.push_back(createMonster(caveLevel));
    }

    vector<string> descriptors = {"Shadow", "Fiery", "Frozen", "Ancient", "Whispering", "Cursed", "Echoing", "Murky"};
    vector<string> features = {"Abyss", "Sanctum", "Cavern", "Maze", "Pit"};

    string caveName = descriptors[rand() % descriptors.size()] + " " + features[rand() % features.size()];

    return Cave(caveName, caveLevel, gold, monsters);
}

