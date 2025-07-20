// world.cpp
#include "world.h"                             // include World class definition
// Constructor: initialize direction arrays, seed RNG, and clear the grid
World::World()
{
    dr[0] = -1; dr[1] = 1; dr[2] = 0; dr[3] = 0; // direction rows: up/down/left/right
    dc[0] = 0;  dc[1] = 0; dc[2] = -1; dc[3] = 1; // direction columns
    srand(time(0));                              // seed random number generator

    // Set all grid cells to nullptr (empty)
    for (int r = 0; r < GRID_SIZE; ++r)
        for (int c = 0; c < GRID_SIZE; ++c)
            grid[r][c] = nullptr;
}

// Destructor: clean up all remaining robots
World::~World() {
    cleanup();
}

// Place INITIAL_PER_TYPE robots of each type at random empty positions
void World::init() {
    int countOpt=0, countRobo=0, countRoom=0, countBull=0, countKami=0;

    // Place Optimusprime robots
    while (countOpt < INITIAL_PER_TYPE) {
        int r = rand() % GRID_SIZE, c = rand() % GRID_SIZE;
        if (!grid[r][c]) {
            grid[r][c] = new Optimusprime(100, 100, "optimusprime_" + to_string(countOpt));
            ++countOpt;
        }
    }

    // Place Robocop robots
    while (countRobo < INITIAL_PER_TYPE) {
        int r = rand() % GRID_SIZE, c = rand() % GRID_SIZE;
        if (!grid[r][c]) {
            grid[r][c] = new Robocop(30, 40, "robocop_" + to_string(countRobo));
            ++countRobo;
        }
    }

    // Place Roomba robots
    while (countRoom < INITIAL_PER_TYPE) {
        int r = rand() % GRID_SIZE, c = rand() % GRID_SIZE;
        if (!grid[r][c]) {
            grid[r][c] = new Roomba(3, 10, "roomba_" + to_string(countRoom));
            ++countRoom;
        }
    }

    // Place Bulldozer robots
    while (countBull < INITIAL_PER_TYPE) {
        int r = rand() % GRID_SIZE, c = rand() % GRID_SIZE;
        if (!grid[r][c]) {
            grid[r][c] = new Bulldozer(50, 200, "bulldozer_" + to_string(countBull));
            ++countBull;
        }
    }

    // Place Kamikaze robots
    while (countKami < INITIAL_PER_TYPE) {
        int r = rand() % GRID_SIZE, c = rand() % GRID_SIZE;
        if (!grid[r][c]) {
            grid[r][c] = new Kamikaze(10, 10, "kamikaze_" + to_string(countKami));
            ++countKami;
        }
    }
}

// Main simulation loop: continue until 1 or no robot remains
void World::simulate() {
    while (true) {
        resetMoved();                        // clear all moved flags

        int survivors;
        Robot* last;
        countAlive(survivors, last);         // count how many are still alive

        if (survivors <= 1) {                // check end condition
            if (last)
                cout << last->getName() << " is the winner!" << endl;
            else
                cout << "No robots remain." << endl;
            break;
        }

        moveAndFight();                      // run movement and battles
        applyHealing();                     // humanic robots heal +1 HP

    }
}

// Set all moved[][] flags to false at the beginning of each turn
void World::resetMoved() {
    for (int r = 0; r < GRID_SIZE; ++r)
        for (int c = 0; c < GRID_SIZE; ++c)
            moved[r][c] = false;
}

// Count how many robots are still alive and remember the last one
void World::countAlive(int &survivors, Robot* &last) {
    survivors = 0;
    last = nullptr;
    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            if (grid[r][c]) {
                ++survivors;
                last = grid[r][c];
            }
        }
    }
}

// Loop through all robots and let them move or fight
void World::moveAndFight() {
    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            Robot* bot = grid[r][c];
            if (bot && !moved[r][c]) {
                int dir = rand() % 4;              // choose random direction
                int nr  = r + dr[dir];             // new row
                int nc  = c + dc[dir];             // new column

                // skip if new position is outside the grid
                if (nr < 0 || nr >= GRID_SIZE || nc < 0 || nc >= GRID_SIZE)
                    continue;

                if (!grid[nr][nc]) {
                    // move robot to new position
                    grid[nr][nc] = bot;
                    grid[r][c]   = nullptr;
                    moved[nr][nc] = true;
                } else {
                    // fight with the robot in the target cell
                    fight(grid[r][c], grid[nr][nc], r, c, nr, nc);
                }
            }
        }
    }
}
// Run a 1-on-1 fight until one robot dies
void World::fight(Robot*& att, Robot*& def, int ar, int ac, int br, int bc) {
    while (att && def) {
        // attacker strikes
        int damageA = att->getDamage();
        int hpBeforeDef = def->getHitpoints();
        def->setHitpoints(hpBeforeDef - damageA);
        cout << att->getName() << "(" << att->getHitpoints() << ") hits "
             << def->getName() << "(" << hpBeforeDef << ") with " << damageA << endl;
        cout << "The new hitpoints of " << def->getName()
             << " is " << def->getHitpoints() << endl;

        if (def->getHitpoints() <= 0) {
            cout << def->getName() << " is dead" << endl;
            delete def;
            grid[br][bc]   = nullptr;
            moved[br][bc]  = true;
            return;
        }

        // defender strikes back
        int damageD = def->getDamage();
        int hpBeforeAtt = att->getHitpoints();
        att->setHitpoints(hpBeforeAtt - damageD);
        cout << def->getName() << "(" << def->getHitpoints() << ") hits "
             << att->getName() << "(" << hpBeforeAtt << ") with " << damageD << endl;
        cout << "The new hitpoints of " << att->getName()
             << " is " << att->getHitpoints() << endl;

        if (att->getHitpoints() <= 0) {
            cout << att->getName() << " is dead" << endl;
            delete att;
            grid[ar][ac]   = nullptr;
            moved[ar][ac]  = true;
            return;
        }
    }
}


// Give +1 HP to all Humanic-derived robots
void World::applyHealing() {
    for (int r = 0; r < GRID_SIZE; ++r)
        for (int c = 0; c < GRID_SIZE; ++c)
            if (grid[r][c]) {
                string t = grid[r][c]->getType();
                if (t == "optimusprime" || t == "robocop") {
                    int hp = grid[r][c]->getHitpoints();
                    grid[r][c]->setHitpoints(hp + 1);
                }
            }
}

// Free memory and clear grid
void World::cleanup() {
    for (int r = 0; r < GRID_SIZE; ++r)
        for (int c = 0; c < GRID_SIZE; ++c) {
            delete grid[r][c];          // delete any robot at this cell
            grid[r][c] = nullptr;       // reset pointer to null
        }
}
