// robot.h
#ifndef ROBOT_H            // start include guard
#define ROBOT_H            // define include guard

#include <string>          // for std::string
#include <iostream>        // for std::cout, std::endl
using namespace std;       // bring std namespace into global scope

class Robot {
protected:
    int strength;          // attack power of the robot
    int hitpoints;         // current health of the robot
    string name;           // name identifier of the robot

public:
    Robot();               // default constructor
    Robot(int newStrength, int newHitpoints, const string& newName); // initialize members
    virtual ~Robot();      // virtual destructor to allow derived cleanup

    virtual string getType() const = 0; // pure virtual: return robot type
    virtual int getDamage();            // compute attack damage

    int getStrength() const;            // retrieve strength value
    int getHitpoints() const;           // retrieve hitpoints value
    string getName() const;             // retrieve name

    void setStrength(int s);            // update strength
    void setHitpoints(int hp);          // update hitpoints
    void setName(const string& n);      // update name
};

#endif  // ROBOT_H         // end include guard
