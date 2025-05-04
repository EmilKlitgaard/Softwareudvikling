#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <ctime>
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

void Game::saveHeroesToFile(vector<Hero> &heroes, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error saving heroes to file.\n";
        return;
    }
    for (const auto& hero : heroes) {
        outFile << hero.getName() << " " << hero.getLevel() << " " << hero.getHp() << " " << hero.getStrength() << " " << hero.getXp() << " " << hero.getGold() << "\n";
    }
    outFile.close();
}

void Game::loadHeroesFromFile(vector<Hero> &heroes, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No saved hero file found.\n";
        return;
    }
    string name;
    int level, hp, strength, xp, gold;
    while (inFile >> name >> level >> hp >> strength >> xp >> gold) {
        heroes.emplace_back(name, level, hp, strength, xp, gold);
    }
    inFile.close();
}


void Game::menu() {
    cout << "╔═════════════════════════════╗\n"
            "║      - - - MENU  - - -      ║\n"
            "╚═════════════════════════════╝" << endl;
    cout << "Choose one of the following options: " << endl;
    cout << "- Create new Hero (0)" << "\n" << "- Load Hero (1)" << "\n" << "- Exit game (2)" << endl;
    
    while (true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = CREATE_HERO; 
            } else if (userInput == 1) {
                STATE = LOAD_HERO; 
            } else if (userInput == 2) {
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
    Hero newHero(heroName, 1, 10, 2, 0, 0);
    heroes.push_back(newHero);
    currentHero = heroes.size() - 1;
    saveHeroesToFile(heroes);
    cout << "Hero '" << newHero.getName() << "' was successfully created!" << endl;
    STATE = ADVENTURE;
    sleep(3);
}

int Game::loadHero(vector<Hero> &heroes) {
    cout << "╔══════════════════════════════════╗\n"
            "║      - - - Load Hero  - - -      ║\n"
            "╚══════════════════════════════════╝" << endl;

    cout << "Choose which hero you want to load: " << endl;
    for (int i = 0; i < heroes.size(); i++) {
        cout << "- " << heroes[i].getName() << " (" << i << ")" << endl;
    }
    
    while (true) {
        if (cin >> currentHero) {
            if (currentHero >= 0 && currentHero < heroes.size()) {
                cout << "Hero '" << heroes[currentHero].getName() << "' has been chosen. Hero stats:" << "\n" << "Level: "  << heroes[currentHero].getLevel() << "\n" << "Health: " << heroes[currentHero].getHp() << "\n" << "Strength: " << heroes[currentHero].getStrength() << "\n" << "Experience (xp): " << heroes[currentHero].getXp() << "\n" << "Gold: " << heroes[currentHero].getGold() << "\n" << endl;
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
        enemies.emplace_back("Horse", 4, 1, 150);
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
                cout << "Enemy '" << enemies[currentEnemy].getName() << "' has been chosen. Enemy stats:" << "\n" << "- Health: " << enemies[currentEnemy].getHp() << "\n" << "- Strength: " << enemies[currentEnemy].getStrength() << "\n" << "- Experience (xp): " << enemies[currentEnemy].getXp() << endl;
                sleep(3);
                STATE = START_BATTLE;
                return currentEnemy;
            } else {
                cout << "Invalid enemy chosen, type a valid number." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int Game::selectCave(vector<Hero> &heroes) {
    cout << "╔════════════════════════════════════╗\n"
            "║      - - - Select Cave  - - -      ║\n"
            "╚════════════════════════════════════╝" << endl;

    cout << "Choose which cave you want to explore:" << endl;

    caves.clear();
    for (int i = 0; i < 5; ++i) {
        caves.push_back( Factory::createCave(heroes[currentHero]) );
        auto &cave = caves.back();
        cout << i+1 << ". " << cave.getName() << "\t( Difficulty: " << cave.getLevel() << ", Gold: " << cave.getGold() << " )\n";
    }

    while (true) {
        int choice;
        if (cin >> choice) {
            if (choice == 0) {
                STATE = ADVENTURE;
                return -1;
            }
            choice -= 1; // to zero‐based
            if (choice >= 0 && choice < (int)caves.size()) {
                currentCave = choice;
                cout << "\nYou picked '" << caves[choice].getName() << "'. It has " << caves[choice].getMonsters().size() << " monsters." << endl;
                cout << "Do you want to enter the cave? (Y/N): ";

                char yn;
                while (cin >> yn) {
                    if (yn == 'y' || yn == 'Y') {
                        STATE = START_CAVE;
                        return currentCave;
                    } else if (yn == 'n' || yn == 'N') {
                        STATE = ADVENTURE;
                        return -1;
                    }
                    cout << "Please enter Y or N: ";
                }
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Game::startCave(vector<Hero> &heroes) {
    clearScreen();
    auto &cave = caves[currentCave];
    cout << "╔═════════════════════════════════════╗\n"
            "║      - - - Entering Cave - - -      ║\n"
            "╚═════════════════════════════════════╝" << endl;

    cave.display();
    sleep(3);

    const auto &monsters = cave.getMonsters();

    for (size_t i = 0; i < monsters.size(); ++i) {
        cout << "\n— Battle " << (i + 1) << " of " << monsters.size() << " —\n";
        Battle battle(heroes[currentHero], monsters[i]); 
        battleWon = battle.startBattle();

        if (!battleWon) {
            gameOver(heroes);
            STATE = MENU;
            return;
        }

        saveHeroesToFile(heroes);
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nCongratulations! You have cleared the cave and earned " << cave.getGold() << " gold!\n";
    heroes[currentHero].addGold(cave.getGold()); 
    sleep(3);
    STATE = ADVENTURE;
}

void Game::showStats(vector<Hero> &heroes) {    
    cout << "Hero stats:" << "\n" << "Level: "  << heroes[currentHero].getLevel() << "\n" << "Health: " << heroes[currentHero].getHp() << "\n" << "Strength: " << heroes[currentHero].getStrength() << "\n" << "Experience (xp): " << heroes[currentHero].getXp() << "\n" << "Gold: " << heroes[currentHero].getGold() << "\n" << endl;
    STATE = ADVENTURE;
    sleep(5);
}

void Game::adventure() {
    if (gameStart) {
        cout << "╔══════════════════════════════════════════╗\n"
                "║      - - - Adventure Started  - - -      ║\n"
                "╚══════════════════════════════════════════╝" << endl;
        cout << "Welcome to the game!" << endl;
        gameStart = false;
    } else {
        cout << "╔════════════════════════════════════════════╗\n"
                "║      - - - Adventure Continued  - - -      ║\n"
                "╚════════════════════════════════════════════╝" << endl;
    }
    
    cout << "Choose one of the following options:" << endl;
    cout << "- Return to menu (0)" << "\n" << "- Fight an enemy (1)" << "\n" << "- Explore caves (2)" << "\n" << "- Show hero stats (3)" << endl;

    while(true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = MENU;
                return;
            } else if (userInput == 1) {
                STATE = SELECT_ENEMY;
                return;
            } else if (userInput == 2) {
                STATE = SELECT_CAVE;
                return;
            } else if (userInput == 3) {
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

void Game::gameOver(vector<Hero> &heroes) {
    cout << "╔══════════════════════════════════╗\n"
            "║      * * * GAME OVER  * * *      ║\n"
            "╚══════════════════════════════════╝" << endl;
    sleep(1);
    heroes.erase(heroes.begin() + currentHero);
    currentHero = -1;
    cout << "Returning to main menu in ";
    for (int i = 5; i > 0; i--) {
        cout << i;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(250));
        for (int j = 0; j < 3; j++) {
            cout << ".";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    cout << endl;
    saveHeroesToFile(heroes);
}

int Game::start() {
    srand(time(0));

    vector<Hero> heroes;
    vector<Enemy> enemies;
    loadHeroesFromFile(heroes);

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
                showStats(heroes);
                break;
            case ADVENTURE:
                clearScreen();
                adventure();
                break;
            case START_BATTLE: {
                clearScreen();
                Battle battle(heroes[currentHero], enemies[currentEnemy]); 
                battleWon = battle.startBattle();
                saveHeroesToFile(heroes);
                if (!battleWon) {
                    gameOver(heroes);
                    STATE = MENU;
                    break;
                }
                STATE = POST_BATTLE;
                break;
            }
            case SELECT_CAVE:
                selectCave(heroes);
                break;
            case START_CAVE:
                startCave(heroes);
                break;
            case POST_BATTLE:
                clearScreen();
                adventure();
                break;
            case EXIT:
                clearScreen();
                cout << "Exiting the game..." << endl;
                return 0;
        }
    }
}
