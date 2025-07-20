#include "world.h"            // include the World class definition
#include <iostream>           // for input/output
using namespace std;          // use the standard namespace

int main() {
    World world;              // create the world object (10x10 grid)
    world.init();             // initialize the world by placing robots
    world.simulate();         // run the robot battle simulation
    return 0;                 // end the program
}
