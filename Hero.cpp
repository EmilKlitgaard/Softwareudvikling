#include <iostream>

#include "Hero.h"

Hero::Hero() 
    : name("Default"), level(1), hp(10), strength(2), xp(0), gold(0), currentWeaponId(0) {}
    
Hero::Hero(const string newName, const int newLevel, const int newHp, const int newStrength, const int newXp, const int newGold, const int newCurrentWeaponId)
    : name(newName), level(newLevel), hp(newHp), strength(newStrength), xp(newXp), gold(newGold), currentWeaponId(newCurrentWeaponId) {}

Hero::~Hero() {}

string Hero::getName() const { return name; }
int Hero::getHp() const { return hp; }
int Hero::getStrength() const { return strength; }
int Hero::getXp() const { return xp; }
int Hero::getLevel() const { return level; }
int Hero::getGold() const { return gold; }
Weapon &Hero::getWeapon() { return weapon; }

int Hero::getId() const { return heroId; }
int Hero::getCurrentWeaponId() const { return currentWeaponId; }

void Hero:: setId(int id) {
    heroId = id;
}

void Hero::setCurrentWeaponId(int weaponId) {
    currentWeaponId = weaponId;
}

void Hero::addXp(int addXp) {
    xp += addXp;
}

void Hero::addGold(int addGold) {
    gold += addGold;
}

int Hero::levelUp() {
    xp -= level * 1000;
    level++;
    strength += 1;
    hp += 2;
    cout << name << " leveled up to lv" << level << "!" << endl;
    return level;
}

void Hero::equipWeapon(Weapon &newWeapon) {
    setCurrentWeaponId(newWeapon.getId());
    weapon = newWeapon;
}

void Hero::unequipWeapon() {
    setCurrentWeaponId(0);
    weapon = Weapon();
}

bool Hero::haveWeapon() {
    return weapon.getName() != "Fists";
}