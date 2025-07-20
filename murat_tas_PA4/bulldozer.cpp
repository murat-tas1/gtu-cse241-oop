// bulldozer.cpp
#include "bulldozer.h"            // include Bulldozer class definition
#include <cstdlib>                // for rand() function
using namespace std;              // use standard namespace

// Default constructor: calls Robot's default constructor
Bulldozer::Bulldozer()
    : Robot() {}

// Parameterized constructor: forwards values to Robot constructor
Bulldozer::Bulldozer(int newStrength, int newHitpoints, const string& newName)
    : Robot(newStrength, newHitpoints, newName) {}

// Override getDamage: uses only base Robot's damage logic
int Bulldozer::getDamage() {
    return Robot::getDamage();    // calls base class to generate and display damage
}

// Returns the type of this robot as "bulldozer"
string Bulldozer::getType() const {
    return "bulldozer";
}
