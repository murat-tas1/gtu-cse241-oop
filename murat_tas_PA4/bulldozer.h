#ifndef BULLDOZER_H               // start include guard
#define BULLDOZER_H               // define include guard

#include "robot.h"                // include base Robot class
#include <string>                 // for using std::string
using namespace std;              // use standard namespace

// Bulldozer is a subclass of Robot
class Bulldozer : public Robot {
public:
    Bulldozer();                 // default constructor
    Bulldozer(int newStrength, int newHitpoints, const string& newName); // constructor with parameters

    virtual int getDamage() override;         // override to define Bulldozer's damage behavior
    virtual string getType() const override;  // override to return "bulldozer"
};

#endif // BULLDOZER_H             // end include guard
