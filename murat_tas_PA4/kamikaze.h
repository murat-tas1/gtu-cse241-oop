// kamikaze.h
#ifndef KAMIKAZE_H               // start include guard
#define KAMIKAZE_H               // define include guard

#include "robot.h"               // include base Robot class
#include <iostream>              // for possible input/output
using namespace std;             // use standard namespace

// Kamikaze is a subclass of Robot
class Kamikaze : public Robot {
public:
    Kamikaze();                 // default constructor
    Kamikaze(int newStrength, int newHitpoints, const string& newName); // parameterized constructor

    // Damage equals its current hitpoints, then it dies
    virtual int getDamage() override;         // override damage to implement self-destruct logic
    virtual string getType() const override;  // override to return "kamikaze"
};

#endif // KAMIKAZE_H             // end include guard
