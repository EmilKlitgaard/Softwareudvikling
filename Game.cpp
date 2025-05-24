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
#include "Database.h"

Game::Game(vector<Hero> &heroes, vector<Enemy> &enemies, Database &database) : heroes(heroes), enemies(enemies), database(database) {}
Game::~Game() {}

void Game::clearScreen() {
    system("clear"); 
}

void Game::postBattle() {
    database.incrementMonsterDefeated(heroes[currentHero].getId(), heroes[currentHero].getCurrentWeaponId());
    database.saveHero(heroes[currentHero]);
}

void Game::menu() {
    cout << "╔═════════════════════════════╗\n"
            "║      - - - MENU  - - -      ║\n"
            "╚═════════════════════════════╝" << endl;
    cout << "Choose one of the following options: " << endl;
    cout << "- Create new Hero (0)" << "\n" << "- Load Hero (1)" << "\n" << "- Game analysis (2)" << "\n" << "- Exit game (3)" << endl;
    
    while (true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                STATE = CREATE_HERO; 
            } else if (userInput == 1) {
                STATE = LOAD_HERO; 
            } else if (userInput == 2) {
                STATE = ANALYSIS; 
            } else if (userInput == 3) {
                STATE = EXIT;
            } else {
                cout << "Invalid input. Please enter 0, 1, 2 or 3." << endl;
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

void Game::createHero(){
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
    Hero newHero(heroName, 1, 10, 2, 0, 0, 0);
    heroes.push_back(newHero);
    currentHero = heroes.size() - 1;
    database.saveHero(heroes[currentHero]);
    cout << "Hero '" << newHero.getName() << "' was successfully created!" << endl;
    STATE = ADVENTURE;
    sleep(3);
}

int Game::loadHero() {
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
                cout << "\nHero '" << heroes[currentHero].getName() << "' has been chosen!";
                showStats();
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

int Game::selectEnemy() {
    clearScreen();
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
                cout << "\nEnemy '" << enemies[currentEnemy].getName() << "' has been chosen. Enemy stats:" << "\n" << "- Health: " << enemies[currentEnemy].getHp() << "\n" << "- Strength: " << enemies[currentEnemy].getStrength() << "\n" << "- Experience (xp): " << enemies[currentEnemy].getXp() << endl;
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

int Game::selectCave() {
    clearScreen();
    cout << "╔════════════════════════════════════╗\n"
            "║      - - - Select Cave  - - -      ║\n"
            "╚════════════════════════════════════╝\n" << endl;

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

void Game::startCave() {
    clearScreen();
    auto &cave = caves[currentCave];
    cout << "╔═════════════════════════════════════╗\n"
            "║      - - - Entering Cave - - -      ║\n"
            "╚═════════════════════════════════════╝\n" << endl;

    cave.display();
    sleep(3);

    const auto &monsters = cave.getMonsters();

    for (size_t i = 0; i < monsters.size(); ++i) {
        Battle battle(heroes[currentHero], monsters[i], database); 
        string battleText = "— Battle " + std::to_string(i + 1) + " of " + std::to_string(monsters.size()) + " —\n";
        battleWon = battle.startBattle(battleText);

        if (!battleWon) {
            gameOver();
            STATE = MENU;
            return;
        }

        postBattle();

        cout << "Press Enter to continue...";
    }

    cout << "\nCongratulations! You have cleared the cave and earned " << cave.getGold() << " gold!\n";
    heroes[currentHero].addGold(cave.getGold()); 

    // 50% chance to find a random weapon
    if (rand() % 2) {
        vector<Weapon> weapons = {
            Weapon("Knife", 5, 0, 20),
            Weapon("Stick", 0, 1, 10),
            Weapon("Metal pipe", 0, 2, 20),
            Weapon("Sword", 20, 1, 30),
            Weapon("Morningstar", 10, 3, 40)
        };
        Weapon foundWeapon = weapons[rand() % weapons.size()];
        weapons.push_back(foundWeapon);
        int weaponId = database.saveWeapon(foundWeapon, heroes[currentHero].getId());
        foundWeapon.setId(weaponId);
        cout << "You have found a weapon: " << foundWeapon.getName() << " (Damage: " << foundWeapon.getDamage() << ", Strength Modifier: " << foundWeapon.getStrengthModifier() << ", Durability: " << foundWeapon.getDurability() << ")\n";
        if (heroes[currentHero].haveWeapon()) {
            cout << "You already have a '" << heroes[currentHero].getWeapon().getName() << "' equipped. Do you want to equip the new weapon? (Y/N): " << endl;
            char yn;
            while (cin >> yn) {
                if (yn == 'y' || yn == 'Y') {
                    heroes[currentHero].equipWeapon(foundWeapon);
                    cout << "You have equipped the new weapon: " << foundWeapon.getName() << endl;
                    break;
                } else if (yn == 'n' || yn == 'N') {
                    cout << "You keep your current weapon: " << heroes[currentHero].getWeapon().getName() << endl;
                    break;
                } else { 
                    cout << "Please enter Y or N: ";
                }
            }
        } else {
            heroes[currentHero].equipWeapon(foundWeapon);
            cout << "You have equipped the new weapon: " << foundWeapon.getName() << endl;
        }
        database.saveHero(heroes[currentHero]);
    }

    sleep(3);
    STATE = ADVENTURE;
}

void Game::showStats() {    
    cout << "\nHero stats:" << "\nLevel: "  << heroes[currentHero].getLevel() << "\nHealth: " << heroes[currentHero].getHp() << "\nStrength: " << heroes[currentHero].getStrength() << "\nExperience (xp): " << heroes[currentHero].getXp() << "\nGold: " << heroes[currentHero].getGold();
    if (heroes[currentHero].getWeapon().getName() != "Fists") {
        cout << "\nWeapon: " << heroes[currentHero].getWeapon().getName() << " (Durability: " << heroes[currentHero].getWeapon().getDurability() << ")" << endl;
    } else {
        cout << endl;
    }
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

void Game::gameOver() {
    cout << "\n" << "╔══════════════════════════════════╗\n"
                    "║      * * * GAME OVER  * * *      ║\n"
                    "╚══════════════════════════════════╝" << endl;
    sleep(1);
    database.heroDefeated(heroes[currentHero]);
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
}

void Game::analysis() {
    clearScreen();
    cout << "╔═════════════════════════════════════╗\n"
            "║      - - - GAME ANALYSIS - - -      ║\n"
            "╚═════════════════════════════════════╝" << endl;

    cout << "Choose one of the following options: " << endl;
    cout << "- Show heroes (0)" << "\n" << "- Show monsters defeated by hero (1)" << "\n" << "- Show monsters defeated by weapon (2)" << "\n" << "- Show weapons (3)" << "\n" << "- Return to main menu (4)" << endl;
    
    while (true) {
        if (cin >> userInput) {
            if (userInput == 0) {
                database.getHeroesOrderedByName();
                sleep(5);
            } else if (userInput == 1) {
                database.getTotalMonstersDefeatedByHero();
                sleep(5);
            } else if (userInput == 2) {
                database.getMonstersDefeatedByWeapon(heroes);
                sleep(5);
            } else if (userInput == 3) {
                database.getTopHeroPerWeapon();
                sleep(5);
            } else if (userInput == 4) {
                STATE = MENU;
            } else {
                cout << "Invalid input. Please enter 0, 1, 2, 3 or 4." << endl;
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

int Game::start() {
    srand(time(0));

    database.loadHeroes(heroes);

    while (true) {
        switch (STATE) {
            case MENU:
                clearScreen();
                menu();
                break;
            case CREATE_HERO:
                clearScreen();
                createHero();
                break;
            case LOAD_HERO:
                if (!heroes.empty()) { 
                    clearScreen();
                    loadHero();
                } else {
                    cout << "No heroes to load, create a new hero...\n" << endl;
                    sleep(1);
                    createHero();
                }
                break;
            case SELECT_ENEMY:
                selectEnemy();
                break;
            case SHOW_STATS:
                showStats();
                break;
            case ADVENTURE:
                clearScreen();
                adventure();
                break;
            case START_BATTLE: {
                clearScreen();
                Battle battle(heroes[currentHero], enemies[currentEnemy], database); 
                battleWon = battle.startBattle("");
                if (!battleWon) {
                    gameOver();
                    STATE = MENU;
                    break;
                }
                postBattle();
                STATE = POST_BATTLE;
                break;
            }
            case SELECT_CAVE:
                selectCave();
                break;
            case START_CAVE:
                startCave();
                break;
            case POST_BATTLE:
                clearScreen();
                adventure();
                break;
            case ANALYSIS:
                analysis();
                break;
            case EXIT:
                clearScreen();
                cout << "Exiting the game..." << endl;
                return 0;
        }
    }
}
