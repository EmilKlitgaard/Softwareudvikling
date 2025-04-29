#include <iostream>
#include <vector>
#include <limits>
#include <unistd.h>

#include "Hero.h"

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
    cout << "Create new Hero (1)" << "\t" << "Load Hero (2)" << "\t" << "Exit game (3)" << endl;
    
    int userInput;
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
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
        }
    }
}

void Game::createHero(vector<Hero>& heroes){
    cout << "╔═══════════════════════════════════╗\n"
            "║      - - - Create Hero - - -      ║\n"
            "╚═══════════════════════════════════╝" << endl;
    cout << "Enter your new Hero's name: ";
    
    string currentHero;
    cin >> currentHero;
    for (int i = 0; i < heroes.size(); i++) {
        while (heroes[i].getName() == currentHero) {
            if (heroes[i].getName() == currentHero) {
                cout << "A hero named '" << currentHero << "' already exists." << endl;
                cout << "Enter a different hero name: ";
                cin >> currentHero;
            }
        }
    }
    Hero newHero(currentHero, 1, 10, 2, 0);
    heroes.push_back(newHero);
    cout << "New hero successfully created: " << newHero.getName() << endl;
    STATE = MENU;
}

int Game::loadHero(vector<Hero>& heroes) {
    cout << "╔══════════════════════════════════╗\n"
            "║      - - - Load Hero  - - -      ║\n"
            "╚══════════════════════════════════╝" << endl;
    cout << "Choose which Hero you want to load: " << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << "(" << i << "), name: " << heroes[i].getName() << "\n" << endl;
    }
    
    int currentHero;
    while (true) {
        if (cin >> currentHero) {
            if (currentHero >= 0 && currentHero < heroes.size()) {
                cout << "Hero: " << heroes[currentHero].getName() << " has been chosen. Hero stats:" << "\n" << "Level: "  << heroes[currentHero].getLevel() << "\n" << "Health: " << heroes[currentHero].getHp() << "\n" << "Strength: " << heroes[currentHero].getStrength() << "\n" << "Experience (xp): " << heroes[currentHero].getXp() << endl;
                sleep(3);
                STATE = START_ADVENTURE;
                return currentHero;
            } else {
                cout << "Invalid Hero chosen, enter a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
        }
    } 
}

int Game::enemyLoad(vector<Enemy>& enemies) {
    cout << "╔═══════════════════════════════════╗\n"
            "║      - - - Load Enemy  - - -      ║\n"
            "╚═══════════════════════════════════╝" << endl;
    
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
        cout <<"Enemy number: " << i << ", name: " << enemies[i].getName() << endl;
    }

    int currentEnemy;
    while (true) {
        if (cin >> currentEnemy) {
            if (currentEnemy >= 0 && currentEnemy < enemies.size()) {
                cout << "Enemy '" << enemies[currentEnemy].getName() << "' has been chosen. Enemy stats:" << "\n" << "Health: " << enemies[currentEnemy].getHp() << "\n" << "Strength: " << enemies[currentEnemy].getStrength() << "\n" << "Experience (xp): " << enemies[currentEnemy].getXp() << endl;
                sleep(1);
                STATE = START_BATTLE;
                return currentEnemy;
            } 
            else {
                cout << "Invalid enemy chosen, type a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
        }
    }
}

int Game::startAdventure() {
    cout << "Welcome to the game!" << endl;
    cout << "Choose one of the following options:" << endl;
    cout << "Return to menu (0)" << "\t" << "Fight an enemy (1)" << endl;
    
    int userInput;
    while (true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = MENU;
                return 0;
            }
            else if (userInput == 1) {
                STATE = LOAD_ENEMY;
                return 0;
            } else {
                cout << "Input is out of range. Please enter a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
        }
    }
}

int Game::Adventure() {
    cout << "Do you want to continue your adventure?" << endl;
    cout << "NO, return to menu (0)" << "\t" << "YES, fight an enemy (1)" << endl;

    while(true) {
        int userInput;
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = MENU;
                return 0;
            }
            else if (userInput == 1) {
                STATE = LOAD_ENEMY;
                return 0;
            } else {
                cout << "Input is out of range. Please enter a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
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
                    cout << "No heroes to load, create a new hero..." << endl;
                    sleep(3);
                    createHero(heroes);
                }
                break;
            case LOAD_ENEMY:
                loadEnemy(enemies);
                break;
            case START_ADVENTURE:
                startAdventure();
                break;
            case START_BATTLE:
                Battle battle(heroes[currentHero], enemies[currentEnemy]);
                battle.startBattle();
                STATE = POST_BATTLE;
                break;
            case POST_BATTLE:
                Adventure();
                break;
            case EXIT:
                clearScreen();
                cout << "Exiting the game" << endl;
                return 0;
        }
    }
}   
