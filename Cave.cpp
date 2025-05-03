#include <iostream>

#include "Cave.h"

using namespace std;

Cave::Cave(string name, int goldReward, vector<Monster> monsters)
    : name(name), goldReward(goldReward), monsters(monsters) {}

void Cave::display() const {
    cout << "Cave: " << name << " | Gold: " << goldReward << "\n";
    cout << "Monsters:\n";
    for (const Monster& m : monsters) {
        m.display();
    }
}

const vector<Monster>& Cave::getMonsters() const { return monsters; }
int Cave::getGoldReward() const { return goldReward; }
string Cave::getName() const { return name; }
