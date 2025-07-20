
#include "robot.h"            // include the Robot class definition
#include <cstdlib>            // for rand() function
using namespace std;          // use standard namespace

// Default constructor: sets default values
Robot::Robot()
: strength(0), hitpoints(0), name("unknown") {}

// Parameterized constructor: sets custom strength, hitpoints, and name
Robot::Robot(int newStrength, int newHitpoints, const string& newName)
    : strength(newStrength), hitpoints(newHitpoints), name(newName) {}

// Destructor: currently does nothing, but defined for virtual cleanup
Robot::~Robot() {}

// Calculate and return damage; also print attack message
int Robot::getDamage() {
    int damage = (rand() % strength) + 1;  // random damage between 1 and strength
    cout << getType() << " attacks for " << damage << " points!" << endl;
    return damage;                         // return computed damage
}

// Getter for strength
int Robot::getStrength() const { return strength; }

// Getter for hitpoints
int Robot::getHitpoints() const { return hitpoints; }

// Getter for name
string Robot::getName() const { return name; }

// Setter for strength
void Robot::setStrength(int s) { strength = s; }

// Setter for hitpoints
void Robot::setHitpoints(int hp) { hitpoints = hp; }

// Setter for name
void Robot::setName(const string& n) { name = n; }
