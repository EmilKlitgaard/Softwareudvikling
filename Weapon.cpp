#include "Weapon.h"
#include "Database.h"

Weapon::Weapon() 
    : name("Fists"), damage(0), strengthModifier(0), durability(0) {}

Weapon::Weapon(string name, int damage, int strengthModifier, int durability)
    : name(name), damage(damage), strengthModifier(strengthModifier), durability(durability) {}

Weapon::~Weapon() {}

string Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
int Weapon::getStrengthModifier() const { return strengthModifier; }
int Weapon::getDurability() const { return durability; }
int Weapon::getId() const { return weaponId; }

void Weapon::setId(const int id) {
    weaponId = id;
}

void Weapon::useWeapon(Database &database) {
    if (durability > 0) {
        durability--;
        database.decrementWeaponDurability(weaponId);
    }
}

bool Weapon::isBroken() const {
    return durability <= 0;
}