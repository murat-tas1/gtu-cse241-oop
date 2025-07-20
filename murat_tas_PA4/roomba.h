// roomba.h
#ifndef ROOMBA_H                // start include guard
#define ROOMBA_H                // define include guard

#include "robot.h"              // include the base Robot class
#include <iostream>             // for possible input/output
using namespace std;            // use standard namespace

// Roomba is a subclass of Robot
class Roomba : public Robot {
public:
    Roomba();                   // default constructor
    Roomba(int newStrength, int newHitpoints, const string& newName); // parameterized constructor

    // Very fast: attacks twice in one turn
    virtual int getDamage() override;         // override damage calculation
    virtual string getType() const override;  // override to return "roomba"
};

#endif // ROOMBA_H              // end include guard
