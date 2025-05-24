#include <iostream>
#include <limits>
#include <unistd.h>

#include "Battle.h"
#include "Hero.h"
#include "Opponent.h"
#
using namespace std;

Battle::Battle(Hero &newHero, const Opponent &newOpponent, Database &newDatabase)
    : hero(newHero), opponent(newOpponent), database(newDatabase) {}

Battle::~Battle() {}

void Battle::awaitEnter() {
    cin.get();
}

void drawHealthBar(int currentHp, int maxHp, int width) {
    int filled = (currentHp * width) / maxHp;
    int empty = width - filled;

    cout << "╔";
    for (int i = 0; i < width; i++) cout << "═";
    cout << "╗\n║";

    for (int i = 0; i < filled; i++) cout << "#";
    for (int i = 0; i < empty; i++) cout << " ";
    
    cout << "║\n╚";
    for (int i = 0; i < width; i++) cout << "═";
    cout << "╝";
}

void printBattleStatus(const string &heroName, int heroHp, int heroMaxHp, const string &opponentName, int opponentHp, int opponentMaxHp, string battleText, int barWidth = 40) {
    system("clear");

    cout << "╔══════════════════════════════════════╗\n"
         << "║      - - - Battle Begins  - - -      ║\n"
         << "╚══════════════════════════════════════╝\n\n";

    cout << battleText;
    cout << heroName << " vs. " << opponentName << "\n\n";

    cout << heroName << "'s Health:\n";
    drawHealthBar(heroHp, heroMaxHp, barWidth);
    cout << " " << heroHp << "/" << heroMaxHp << "\n\n";

    cout << opponentName << "'s Health:\n";
    drawHealthBar(opponentHp, opponentMaxHp, barWidth);
    cout << " " << opponentHp << "/" << opponentMaxHp << "\n\n";
}

bool Battle::startBattle(string battleText) {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int heroHp = hero.getHp();
    int opponentHp = opponent.getHp();
    int heroMaxHp = heroHp;
    int opponentMaxHp = opponentHp;

    Weapon &weapon = hero.getWeapon();

    printBattleStatus(hero.getName(), heroHp, heroMaxHp, opponent.getName(), opponentHp, opponentMaxHp, battleText);

    while (heroHp > 0 && opponentHp > 0) {
        cout << "It's your turn! Press ENTER to attack." << endl;
        cin.get();

        // Opponent attacks hero
        int heroDamage = hero.haveWeapon() ? 
            hero.getStrength() + weapon.getDamage() + (hero.getStrength() * weapon.getStrengthModifier())
            : hero.getStrength();

        opponentHp -= heroDamage;
        if (opponentHp < 0) opponentHp = 0;

        printBattleStatus(hero.getName(), heroHp, heroMaxHp, opponent.getName(), opponentHp, opponentMaxHp, battleText);

        cout << hero.getName() << " attacks for " << heroDamage << " damage." << endl;

        if (hero.haveWeapon()) {
            weapon.useWeapon(database);
            if (weapon.isBroken()) {
                cout << hero.getName() << "'s weapon has broken!" << endl;
                hero.unequipWeapon();
            }
        }

        if (opponentHp <= 0) {
            cout << "\n" << opponent.getName() << " is defeated!" << endl;
            cout << hero.getName() << " has won!\n" << endl;
            hero.addXp(opponent.getXp());
            while (hero.getXp() >= hero.getLevel() * 1000) {
                hero.levelUp();
            }
            sleep(5);
            return true;
        }
        sleep(1);

        // Opponent attacks hero
        heroHp -= opponent.getStrength();
        if (heroHp < 0) heroHp = 0;

        printBattleStatus(hero.getName(), heroHp, heroMaxHp, opponent.getName(), opponentHp, opponentMaxHp, battleText);

        cout << opponent.getName() << " attacks for " << opponent.getStrength() << " damage.\n" << endl;

        if (heroHp <= 0) {
            cout << hero.getName() << " is defeated!" << endl;
            cout << opponent.getName() << " has won!" << endl;
            sleep(2);
            return false;
        }
        sleep(1);
    }
    return false;
}