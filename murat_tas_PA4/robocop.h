// robocop.h
#ifndef ROBOCOP_H               // start include guard
#define ROBOCOP_H               // define include guard

#include "humanic.h"            // include the Humanic base class
#include <iostream>             // for potential I/O operations
using namespace std;            // use the standard namespace

// Robocop is a subclass of Humanic
class Robocop : public Humanic {
public:
    Robocop();                  // default constructor
    Robocop(int newStrength, int newHitpoints, const string& newName); // parameterized constructor

    virtual int getDamage() override;         // override to provide Robocop-specific damage behavior
    virtual string getType() const override;  // override to return "robocop"
};

#endif // ROBOCOP_H             // end include guard
