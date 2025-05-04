#include <iostream>
#include <limits>
#include <unistd.h>

#include "Battle.h"
#include "Hero.h"
#include "Opponent.h"

using namespace std;

Battle::Battle(Hero &newHero, const Opponent &newOpponent)
    : hero(newHero), opponent(newOpponent) {}

Battle::~Battle() {}

void Battle::awaitEnter() {
    cin.get();
}

bool Battle::startBattle() {
    cout << "╔══════════════════════════════════════╗\n"
            "║      - - - Battle Begins  - - -      ║\n"
            "╚══════════════════════════════════════╝" << endl;

    cout << hero.getName() << " vs. " << opponent.getName() << endl;        

    int heroHp = hero.getHp();
    int opponentHp = opponent.getHp();

    cin.ignore();

    while (heroHp > 0 && opponentHp > 0) {
        cout << "\nIt's your turn! Press ENTER to attack." << endl;
        awaitEnter();
        opponentHp -= hero.getStrength();
        cout << hero.getName() << " attacks " << opponent.getName() << " for " << hero.getStrength() << " damage.\t" << opponent.getName() << " HP: " << opponentHp << endl;

        if (opponentHp <= 0) {
            cout << opponent.getName() << " is defeated!" << endl;
            cout << hero.getName() << " has won!" << endl;
            hero.addXp(opponent.getXp());
            while (hero.getXp() >= hero.getLevel() * 1000) {
                hero.levelUp();
            }
            sleep(5);
            return true;
        }

        sleep(1);

        heroHp -= opponent.getStrength();
        cout << opponent.getName() << " attacks " << hero.getName() << " for " << opponent.getStrength() << " damage.\t" << hero.getName() << " HP: " << heroHp << endl;

        if (heroHp <= 0) {
            cout << hero.getName() << " is defeated!" << endl;
            cout << opponent.getName() << " has won!" << endl;
            sleep(5);
            return false;
        }
    }
    return false;
}
