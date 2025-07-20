// kamikaze.cpp
#include "kamikaze.h"            // include Kamikaze class definition
using namespace std;             // use standard namespace

// Default constructor: calls base Robot default constructor
Kamikaze::Kamikaze()
    : Robot() {}

// Parameterized constructor: passes values to base Robot constructor
Kamikaze::Kamikaze(int newStrength, int newHitpoints, const string& newName)
    : Robot(newStrength, newHitpoints, newName) {}

// Kamikaze attack: deals damage equal to its current hitpoints, then dies
int Kamikaze::getDamage() {
    int damage = hitpoints;      // damage equals current hitpoints
    cout << getType()
         << " inflicts a kamikaze attack for "
         << damage << " points and self-destructs!"
         << endl;
    hitpoints = 0;               // self-destruct: set own HP to 0
    return damage;               // return damage dealt
}

// Return the type of this robot as "kamikaze"
string Kamikaze::getType() const {
    return "kamikaze";
}
