#include "Weapon.h"

Weapon::Weapon() 
    : name("Fists"), damage(1), strengthModifier(0), durability(10) {}

Weapon::Weapon(string name, int damage, int strengthModifier, int durability)
    : name(name), damage(damage), strengthModifier(strengthModifier), durability(durability) {}

Weapon::~Weapon() {}

string Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
int Weapon::getStrengthModifier() const { return strengthModifier; }
int Weapon::getDurability() const { return durability; }

void Weapon::useWeapon() {
    if (durability > 0) {
        durability--;
    }
}

bool Weapon::isBroken() const {
    return durability <= 0;
}