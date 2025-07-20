// humanic.h
#ifndef HUMANIC_H              // start include guard
#define HUMANIC_H              // define include guard

#include "robot.h"             // include base Robot class
#include <iostream>            // for potential input/output
using namespace std;           // use standard namespace

// Humanic is a derived class from Robot
class Humanic : public Robot {
public:
    Humanic();                 // default constructor
    Humanic(int newStrength, int newHitpoints, const string& newName); // constructor with parameters

    virtual int getDamage() override;         // override damage calculation with Humanic logic
    virtual string getType() const override;  // return the type as "humanic"

};

#endif // HUMANIC_H            // end include guard
