#include <iostream>

#include "Cave.h"

using namespace std;

Cave::Cave(string name, int level, int gold, vector<Monster> monsters)
    : name(name), level(level), gold(gold), monsters(monsters) {}


void Cave::display() const {
    cout << "Cave: " << name << " | Gold: " << gold << "\n";
    cout << "Monsters:\n";
    for (const Monster& monster : monsters) {
        monster.display();
    }
}

const vector<Monster> &Cave::getMonsters() const { 
    return monsters; 
}

string Cave::getName() const { 
    return name; 
}

int Cave::getLevel() {
    return level;
}

int Cave::getGold() const { 
    return gold; 
}
