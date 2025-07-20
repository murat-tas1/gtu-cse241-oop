// optimusprime.h
#ifndef OPTIMUSPRIME_H               // start include guard
#define OPTIMUSPRIME_H               // define include guard

#include "humanic.h"                 // include the Humanic base class
#include <iostream>                  // for potential input/output
using namespace std;                 // use standard namespace

// Optimusprime is a subclass of Humanic
class Optimusprime : public Humanic {
public:
    Optimusprime();                  // default constructor
    Optimusprime(int newStrength, int newHitpoints, const string& newName); // constructor with parameters

    virtual int getDamage() override;         // override to implement Optimusprime-specific damage
    virtual string getType() const override;  // override to return "optimusprime"
};

#endif // OPTIMUSPRIME_H             // end include guard
