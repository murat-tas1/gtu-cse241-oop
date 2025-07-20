// world.h
#ifndef WORLD_H                   // start include guard
#define WORLD_H                   // define include guard

#include <iostream>               // for input/output
#include <cstdlib>                // for rand(), srand()
#include <ctime>                  // for time()
#include <string>                 // for std::string

#include "robot.h"                // base class
#include "humanic.h"              // derived class
#include "optimusprime.h"         // derived class
#include "robocop.h"              // derived class
#include "roomba.h"               // derived class
#include "bulldozer.h"            // derived class
#include "kamikaze.h"             // derived class

using namespace std;              // use standard namespace

// constants for grid dimensions and initial robot count
static const int GRID_SIZE        = 10;   // size of the grid (10x10)
static const int INITIAL_PER_TYPE = 5;    // number of robots per type to place

// World class manages the simulation grid and robot logic
class World {
public:
    World();                      // constructor
    ~World();                     // destructor

    void init();                  // place INITIAL_PER_TYPE of each robot at random locations
    void simulate();              // run the simulation until one (or zero) robots remain

private:
    Robot* grid[GRID_SIZE][GRID_SIZE];    // 2D grid of robot pointers
    bool   moved[GRID_SIZE][GRID_SIZE];   // track which robots moved this turn

    int dr[4];                    // row direction offsets: up/down/left/right
    int dc[4];                    // column direction offsets

    void resetMoved();           // reset moved[][] flags at the beginning of each turn
    void countAlive(int &survivors, Robot* &last); // count how many robots are alive
    void moveAndFight();         // execute robot movement and combat for this turn
    void fight(Robot*& att, Robot*& def, int ar, int ac, int br, int bc); // 1-on-1 fight between two robots
    void applyHealing();         // Humanic robots heal +1 HP per round
    void cleanup();              // delete remaining robots and clear memory
};

#endif // WORLD_H                 // end include guard
