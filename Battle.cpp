#include <iostream>
#include <limits>
#include <unistd.h>

#include "Battle.h"
#include "Hero.h"
#include "Enemy.h"
#include "Monster.h"

using namespace std;

Battle::Battle(Hero &newHero, Enemy &newEnemy)
    : hero(newHero), enemy(&newEnemy) {}

Battle::Battle(Hero &newHero, const Monster &newMonster)
    : hero(newHero), monster(&newMonster) {}

Battle::~Battle() {}

void Battle::awaitEnter() {
    cin.get();
}

bool Battle::startBattle() {
    cout << "╔══════════════════════════════════════╗\n"
            "║      - - - Battle Begins  - - -      ║\n"
            "╚══════════════════════════════════════╝" << endl;

    string opponentName = enemy ? enemy->getName() : monster->getName();
    int opponentHp = enemy ? enemy->getHp() : monster->getHp();
    int opponentStrength = enemy ? enemy->getStrength() : monster->getStrength();
    int opponentXp = enemy ? enemy->getXp() : monster->getXp();

    cout << hero.getName() << " vs. " << opponentName << endl;

    int heroHp = hero.getHp();

    cin.ignore();

    while (heroHp > 0 && opponentHp > 0) {
        cout << "\nIt's your turn! Press ENTER to attack." << endl;
        awaitEnter();
        opponentHp -= hero.getStrength();
        cout << hero.getName() << " attacks " << opponentName << " for " << hero.getStrength() << " damage. " << opponentName << " HP: " << opponentHp << endl;

        if (opponentHp <= 0) {
            cout << opponentName << " is defeated!" << endl;
            cout << hero.getName() << " has won!" << endl;
            hero.addXp(opponentXp);
            while (hero.getXp() >= hero.getLevel() * 1000) {
                hero.levelUp();
            }
            sleep(5);
            return true;
        }

        sleep(1);

        cout << opponentName << " attacks " << hero.getName() << " for " << opponentStrength << " damage." << endl;
        heroHp -= opponentStrength;
        cout << hero.getName() << " HP: " << heroHp << endl;

        if (heroHp <= 0) {
            cout << hero.getName() << " is defeated!" << endl;
            cout << opponentName << " has won!" << endl;
            sleep(5);
            return false;
        }
    }
    return false;
}
