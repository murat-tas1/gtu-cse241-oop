// humanic.cpp
#include "humanic.h"         // include the Humanic class definition
#include <cstdlib>           // for rand() function
using namespace std;         // use standard namespace

// Default constructor: calls base Robot constructor
Humanic::Humanic()
    : Robot() {}

// Parameterized constructor: passes values to base Robot constructor
Humanic::Humanic(int newStrength, int newHitpoints, const string& newName)
    : Robot(newStrength, newHitpoints, newName) {}

// Override getDamage: adds chance for extra Humanic damage
int Humanic::getDamage() {
    int damage = Robot::getDamage();           // base damage from Robot class
    if ((rand() % 100) < 15) {                 // 15% chance for extra damage
        cout << getType()
             << " tactical nuke inflicts 40 additional damage points!"
             << endl;
        damage += 40;                          // add 40 extra damage
    }
    return damage;                             // return total damage
}

// Return the type of this robot as "humanic"
string Humanic::getType() const {
    return "humanic";
}