// optimusprime.cpp
#include "optimusprime.h"       // include Optimusprime class definition
#include <cstdlib>              // for rand() function
using namespace std;            // use standard namespace

// Default constructor: calls Humanic's default constructor
Optimusprime::Optimusprime()
    : Humanic() {}

// Parameterized constructor: passes values to Humanic constructor
Optimusprime::Optimusprime(int newStrength, int newHitpoints, const string& newName)
    : Humanic(newStrength, newHitpoints, newName) {}

// Override getDamage to add Optimusprime's special double-damage ability
int Optimusprime::getDamage() {
    int damage = Humanic::getDamage();       // base damage from Humanic
    if ((rand() % 100) < 20) {               // 20% chance to double the damage
        cout << getType()
             << " special attack doubles the damage!"
             << endl;
        damage *= 2;                         // double the damage
    }
    return damage;                           // return total damage
}

// Return the type of this robot as "optimusprime"
string Optimusprime::getType() const {
    return "optimusprime";
}
