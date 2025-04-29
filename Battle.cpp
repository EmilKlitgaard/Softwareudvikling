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

void Battle::gameOver() {
    cout << hero.getName() << " is defeated!" << endl;
    cout << "╔══════════════════════════════════╗\n"
            "║      * * * GAME OVER  * * *      ║\n"
            "╚══════════════════════════════════╝" << endl;
    sleep(1);
    cout << "Exiting the game in 5..."
    sleep(1);
    cout << "4..."
    sleep(1);
    cout << "3..."
    sleep(1);
    cout << "2..."
    sleep(1);
    cout << "1..."
    sleep(1);
}

void Battle::startBattle() {
    cout << "Battle begins: " << hero.getName() << " vs. " << enemy.getName() << endl;

    int heroHp = hero.getHp();
    int enemyHp = enemy.getHp();

    while (heroHp > 0 && enemyHp > 0) {
        cout << "It's your turn! Press ENTER to attack." << endl;
        cin;
        enemyHp -= hero.getStrength();
        cout << hero.getName() << " attacks " << enemy.getName() << " for " << hero.getStrength() << " damage. " << enemy.getName() << " HP: " << enemyHp << endl;

        if (enemyHp <= 0) {
            cout << enemy.getName() << " is defeated!" << endl;
            cout << hero.getName() << " has won!" << endl;

            hero.addXp(enemy.getXp());

            while (hero.getXp() >= hero.getLevel() * 1000) {
                hero.levelUp();
                sleep(1);
            }
            break;
        }

        sleep(1);

        cout << "It's" << enemy.getName() << "'s turn!" << endl;
        heroHp -= enemy.getStrength();
        cout << enemy.getName() << " attacks " << hero.getName() << " for " << enemy.getStrength() << " damage. " << hero.getName() << " HP: " << heroHp << endl;

        if (heroHp <= 0) {
            gameOver();
            break;
        }
        sleep(1);
    }
}
