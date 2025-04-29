#include <iostream>
#include <vector>
#include <limits>
#include <unistd.h>

#include "Game.h"
#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"

Game::Game() {}
Game::~Game() {}

void Game::clearScreen() {
    system("clear"); 
}

void Game::menu() {
    cout << "╔═════════════════════════════╗\n"
            "║      - - - MENU  - - -      ║\n"
            "╚═════════════════════════════╝" << endl;
    cout << "Choose one of the following options: " << endl;
    cout << "- Create new Hero (1)" << "\n" << "- Load Hero (2)" << "\n" << "- Exit game (3)" << endl;
    
    while (true) {
        if (cin >> userInput) {
            if (userInput == 1) {
                STATE = CREATE_HERO; 
            } else if (userInput == 2) {
                STATE = LOAD_HERO; 
            } else if (userInput == 3) {
                STATE = EXIT;
            } else {
                cout << "Invalid input. Please enter 1, 2, or 3." << endl;
                continue;
            }
            break;
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Game::createHero(vector<Hero> &heroes){
    cout << "╔═══════════════════════════════════╗\n"
            "║      - - - Create Hero - - -      ║\n"
            "╚═══════════════════════════════════╝" << endl;
    cout << "Enter your new Hero's name: ";
    
    string heroName;
    cin >> heroName;
    for (int i = 0; i < heroes.size(); i++) {
        while (heroes[i].getName() == heroName) {
            if (heroes[i].getName() == heroName) {
                cout << "A hero named '" << heroName << "' already exists." << endl;
                cout << "Enter a different hero name: ";
                cin >> heroName;
            }
        }
    }
    currentHero = heroes.size();
    Hero newHero(heroName, 1, 10, 2, 0);
    heroes.push_back(newHero);
    cout << "Hero '" << newHero.getName() << "' was successfully created!" << endl;
    sleep(3);
    STATE = ADVENTURE;
}

int Game::loadHero(vector<Hero>& heroes) {
    cout << "╔══════════════════════════════════╗\n"
            "║      - - - Load Hero  - - -      ║\n"
            "╚══════════════════════════════════╝" << endl;
    cout << "Choose which Hero you want to load: " << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << "- " << heroes[i].getName() << " (" << i << ")" << endl;
    }
    
    while (true) {
        if (cin >> currentHero) {
            if (currentHero >= 0 && currentHero < heroes.size()) {
                cout << "Hero: " << heroes[currentHero].getName() << " has been chosen. Hero stats:" << "\n" << "Level: "  << heroes[currentHero].getLevel() << "\n" << "Health: " << heroes[currentHero].getHp() << "\n" << "Strength: " << heroes[currentHero].getStrength() << "\n" << "Experience (xp): " << heroes[currentHero].getXp() << "\n" << endl;
                sleep(3);
                STATE = ADVENTURE;
                return currentHero;
            } else {
                cout << "Invalid Hero chosen, enter a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } 
}

int Game::selectEnemy(vector<Enemy> &enemies) {
    cout << "╔═════════════════════════════════════╗\n"
            "║      - - - Select Enemy  - - -      ║\n"
            "╚═════════════════════════════════════╝" << endl;
    
    cout << "Choose which Enemy you want to fight: " << endl;
    
    if (enemies.empty()) {
        enemies.emplace_back("Horse", 4, 1, 1500);
        enemies.emplace_back("Weak Goblin", 4, 2, 200);
        enemies.emplace_back("Strong Goblin", 8, 3, 400);
        enemies.emplace_back("Stronger Goblin", 10, 4, 500);
        enemies.emplace_back("King Goblin", 15, 5, 800);
        enemies.emplace_back("Monkey King", 30, 5, 1000);
        enemies.emplace_back("Unicorn", 5, 20, 1500);
        enemies.emplace_back("Dragon", 100, 10, 3000);
    }
    
    for (int i = 0; i < enemies.size(); i++) {
        cout << "- " << enemies[i].getName() << " (" << i << ")" << endl;
    }

    while (true) {
        if (cin >> currentEnemy) {
            if (currentEnemy >= 0 && currentEnemy < enemies.size()) {
                cout << "Enemy '" << enemies[currentEnemy].getName() << "' has been chosen. Enemy stats:" << "\n" << "- Health: " << enemies[currentEnemy].getHp() << "\n" << "- Strength: " << enemies[currentEnemy].getStrength() << "\n" << "- Experience (xp): " << enemies[currentEnemy].getXp() << "\n" << endl;
                sleep(3);
                STATE = START_BATTLE;
                return currentEnemy;
            } 
            else {
                cout << "Invalid enemy chosen, type a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Game::showStats() {
    if (heroes.empty()) {
        cout << "ERROR. Current hero: " << currentHero << endl;
        STATE = ADVENTURE;
        sleep(3);
        return;
    }
    
    cout << "Hero stats:" << "\n" << "Level: "  << heroes[currentHero].getLevel() << "\n" << "Health: " << heroes[currentHero].getHp() << "\n" << "Strength: " << heroes[currentHero].getStrength() << "\n" << "Experience (xp): " << heroes[currentHero].getXp() << "\n" << endl;
    STATE = ADVENTURE;
}

void Game::adventure() {
    if (gameStart) {
        cout << "╔═════════════════════════════════════╗\n"
                "║      - - - Game Started  - - -      ║\n"
                "╚═════════════════════════════════════╝" << endl;
        cout << "Welcome to the game!" << endl;
        gameStart = false;
    } else {
        cout << "\n" << "╔═══════════════════════════════════════╗\n"
                        "║      - - - Game Continued  - - -      ║\n"
                        "╚═══════════════════════════════════════╝" << endl;
    }
    
    cout << "Choose one of the following options:" << endl;
    cout << "- Return to menu (0)" << "\n" << "- Fight an enemy (1)" << "\n" << "- Show hero stats (2)" << endl;

    while(true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = MENU;
                return;
            } else if (userInput == 1) {
                STATE = SELECT_ENEMY;
                return;
            } else if (userInput == 2) {
                STATE = SHOW_STATS;
                return;
            } else {
                cout << "Input is out of range. Please enter a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int Game::start() {
    vector<Hero> heroes;
    vector<Enemy> enemies;

    while (true) {
        switch (STATE) {
            case MENU:
                clearScreen();
                menu();
                break;
            case CREATE_HERO:
                clearScreen();
                createHero(heroes);
                break;
            case LOAD_HERO:
                if (!heroes.empty()) { 
                    clearScreen();
                    loadHero(heroes);
                } else {
                    cout << "No heroes to load, create a new hero...\n" << endl;
                    sleep(1);
                    createHero(heroes);
                }
                break;
            case SELECT_ENEMY:
                selectEnemy(enemies);
                break;
            case SHOW_STATS:
                showStats();
                break;
            case ADVENTURE:
                clearScreen();
                adventure();
                break;
            case START_BATTLE: {
                Battle battle(heroes[currentHero], enemies[currentEnemy]); 
                battleWon = battle.startBattle();
                if (!battleWon) return 0;
                STATE = POST_BATTLE;
                break;
            }
            case POST_BATTLE:
                adventure();
                break;
            case EXIT:
                clearScreen();
                cout << "Exiting the game..." << endl;
                return 0;
        }
    }
}
