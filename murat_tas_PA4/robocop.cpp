// robocop.cpp
#include "robocop.h"               // include Robocop class definition
using namespace std;               // use the standard namespace

// Default constructor: calls the default Humanic constructor
Robocop::Robocop()
    : Humanic() {}

// Parameterized constructor: forwards values to Humanic constructor
Robocop::Robocop(int newStrength, int newHitpoints, const string& newName)
    : Humanic(newStrength, newHitpoints, newName) {}

// Inherit and use Humanic's getDamage() behavior
int Robocop::getDamage() {
    return Humanic::getDamage();
}

// Return the type of this robot as "robocop"
string Robocop::getType() const {
    return "robocop";
}
