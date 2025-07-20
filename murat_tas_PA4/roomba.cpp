// roomba.cpp
#include "roomba.h"            // include Roomba class definition
#include <cstdlib>             // for rand() function
using namespace std;           // use standard namespace

// Default constructor: calls base Robot default constructor
Roomba::Roomba()
    : Robot() {}

// Parameterized constructor: passes values to base Robot constructor
Roomba::Roomba(int newStrength, int newHitpoints, const string& newName)
    : Robot(newStrength, newHitpoints, newName) {}

// Override getDamage: Roomba attacks twice per turn
int Roomba::getDamage() {
    int d1 = Robot::getDamage();   // First attack damage
    int d2 = Robot::getDamage();   // Second attack damage
    return d1 + d2;                // Return total combined damage
}

// Return the type of this robot as "roomba"
string Roomba::getType() const {
    return "roomba";
}
