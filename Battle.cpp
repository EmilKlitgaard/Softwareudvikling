#include <iostream>
#include <limits>
#include <unistd.h>

#include "Battle.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;

Battle::Battle(Hero &newHero, Enemy &newEnemy)
    : hero(newHero), enemy(newEnemy) {}

Battle::~Battle() {}

void Battle::awaitEnter() {
    cin.get();
}

bool Battle::startBattle() {
    cout << "╔══════════════════════════════════════╗\n"
            "║      - - - Battle Begins  - - -      ║\n"
            "╚══════════════════════════════════════╝" << endl;
    cout << hero.getName() << " vs. " << enemy.getName() << endl;

    int heroHp = hero.getHp();
    int enemyHp = enemy.getHp();
    
    cin.ignore();

    while (heroHp > 0 && enemyHp > 0) {
        cout << "\n" << "It's your turn! Press ENTER to attack." << endl;
        awaitEnter();
        enemyHp -= hero.getStrength();
        cout << hero.getName() << " attacks " << enemy.getName() << " for " << hero.getStrength() << " damage. " << enemy.getName() << " HP: " << enemyHp << endl;

        if (enemyHp <= 0) {
            cout << enemy.getName() << " is defeated!" << endl;
            cout << hero.getName() << " has won!" << endl;
            hero.addXp(enemy.getXp());
            while (hero.getXp() >= hero.getLevel() * 1000) {
                hero.levelUp();
            }
            sleep(5);
            return true;
        }

        sleep(1);

        heroHp -= enemy.getStrength();
        cout << enemy.getName() << " attacks " << hero.getName() << " for " << enemy.getStrength() << " damage. " << hero.getName() << " HP: " << heroHp << endl;

        if (heroHp <= 0) {
            cout << hero.getName() << " is defeated!" << "\n" << endl;
            sleep(1);
            return false;
        }
        sleep(1);
    }
    return false;
}
