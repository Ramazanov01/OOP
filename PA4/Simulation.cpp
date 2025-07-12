#include "Simulation.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Seed the random number generator with the current time
// Set all grid cells to nullptr (empty)
Simulation::Simulation() : robot_count(0) {
    srand(time(NULL)); // So we get different random values each time we run
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = nullptr; // Clear the grid, make sure it's all empty
        }
    }
}

// Destructor for the Simulation class
// Clean up all dynamically allocated robots in the grid
Simulation::~Simulation() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                delete grid[i][j]; // Boom! Memory freed, no leaks allowed here.
            }
        }
    }
}

// Create and place different robot types randomly on the grid
void Simulation::initializeRobots() {
    // Create a list of all grid positions
    vector<pair<int, int>> positions;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            positions.emplace_back(i, j);
        }
    }
    random_shuffle(positions.begin(), positions.end());

    // Create 5 of each robot type
    for (int i = 0; i < 5; i++) {
        // OptimusPrime
        grid[positions.back().first][positions.back().second] = new optimusprime(0, 100, 100, "optimusprime_" + to_string(i));
        positions.pop_back();
        robot_count++;

        // Robocop
        grid[positions.back().first][positions.back().second] = new robocop(1, 30, 40, "robocop_" + to_string(i));
        positions.pop_back();
        robot_count++;

        // Roomba
        grid[positions.back().first][positions.back().second] = new roomba(2, 3, 10, "roomba_" + to_string(i));
        positions.pop_back();
        robot_count++;

        // Bulldozer
        grid[positions.back().first][positions.back().second] = new bulldozer(3, 50, 200, "bulldozer_" + to_string(i));
        positions.pop_back();
        robot_count++;

        // Kamikaze
        grid[positions.back().first][positions.back().second] = new kamikaze(4, 10, 10, "kamikaze_" + to_string(i));
        positions.pop_back();
        robot_count++;
    }
}

// Resets the flags of all robots in the grid to 0
// Used to ensure that each robot moves only once per simulation step
void Simulation::resetFlags() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->set_flag(0); // Resetting the "has moved" flag
            }
        }
    }
}

// Attempts to move a robot from position (x, y) in a random direction
void Simulation::moveRobot(int x, int y) {
    // If there's no robot here or it already moved this turn, do nothing
    if (grid[x][y] == nullptr || grid[x][y]->get_flag() == 1) return;

    int direction = rand() % 4; // Pick a random direction: 0=up, 1=right, 2=down, 3=left
    int newX = x, newY = y;

    // Update new coordinates based on chosen direction (within bounds)
    switch (direction) {
        case 0: if (x > 0) newX--; break;         // Move up
        case 1: if (y < GRID_SIZE - 1) newY++; break; // Move right
        case 2: if (x < GRID_SIZE - 1) newX++; break; // Move down
        case 3: if (y > 0) newY--; break;         // Move left
    }

    // If the move goes nowhere, just exit (hit a wall basically)
    if (newX == x && newY == y) return;

    // If the new cell is empty, move robot there
    if (grid[newX][newY] == nullptr) {
        grid[newX][newY] = grid[x][y];
        grid[x][y] = nullptr;
        grid[newX][newY]->set_flag(1); // Mark robot as moved
    } else {
        // If the new cell is occupied, initiate a fight between robots
        fight(grid[x][y], grid[newX][newY], newX, newY, x, y);
    }
}


// Handles combat between two robots: attacker and defender
// Takes into account special robot types like kamikaze, optimusprime, robocop, and roomba
void Simulation::fight(Robot* attacker, Robot* defender, int newX, int newY, int oldX, int oldY) {
    attacker->set_flag(1);
    defender->set_flag(1); // Mark both robots as having acted in this turn

    // Special case: Attacker is a kamikaze robot - explodes on impact
    if (attacker->get_type() == "kamikaze") {
        int damage = attacker->get_hitpoints(); // Full HP used as damage
        int defender_hp_before = defender->get_hitpoints();
        defender->set_hitpoints(defender_hp_before - damage);

        cout << attacker->get_name() << "(" << attacker->get_hitpoints() << ") hits " 
             << defender->get_name() << "(" << defender_hp_before << ") with " << damage << endl;
        cout << "The new hitpoints of " << defender->get_name() << " is " << defender->get_hitpoints() << endl;
        cout << attacker->get_name() << " has died (kamikaze)." << endl;

        delete attacker;
        grid[oldX][oldY] = nullptr;
        robot_count--;

        // If defender died from the explosion
        if (defender->get_hitpoints() <= 0) {
            cout << defender->get_name() << " has died." << endl;
            delete defender;
            grid[newX][newY] = nullptr;
            robot_count--;
        } 
        // If defender is humanic, give it some healing love
        else if (defender->get_type() == "optimusprime" || defender->get_type() == "robocop") {
            int max_hp = (defender->get_type() == "optimusprime") ? 100 : 40;
            if (defender->get_hitpoints() < max_hp) {
                defender->set_hitpoints(defender->get_hitpoints() + 1);
            }
        }
        return;
    }

    // Special case: Defender is kamikaze - same boom logic as above
    if (defender->get_type() == "kamikaze") {
        int damage = defender->get_hitpoints();
        int attacker_hp_before = attacker->get_hitpoints();
        attacker->set_hitpoints(attacker_hp_before - damage);

        cout << defender->get_name() << "(" << defender->get_hitpoints() << ") hits " 
             << attacker->get_name() << "(" << attacker_hp_before << ") with " << damage << endl;
        cout << "The new hitpoints of " << attacker->get_name() << " is " << attacker->get_hitpoints() << endl;
        cout << defender->get_name() << " has died (kamikaze)." << endl;

        delete defender;
        grid[newX][newY] = nullptr;
        robot_count--;

        if (attacker->get_hitpoints() <= 0) {
            cout << attacker->get_name() << " has died." << endl;
            delete attacker;
            grid[oldX][oldY] = nullptr;
            robot_count--;
        } else {
            // Attacker survives and takes defender's place
            grid[newX][newY] = attacker;
            grid[oldX][oldY] = nullptr;

            // Humanic healing again
            if (attacker->get_type() == "optimusprime" || attacker->get_type() == "robocop") {
                int max_hp = (attacker->get_type() == "optimusprime") ? 100 : 40;
                if (attacker->get_hitpoints() < max_hp) {
                    attacker->set_hitpoints(attacker->get_hitpoints() + 1);
                }
            }
        }
        return;
    }

    // Normal combat mode – Turn-based slugfest until one drops
    while (true) {
        // Attacker hits first
        int damage = attacker->get_damage();
        int defender_hp_before = defender->get_hitpoints();
        defender->set_hitpoints(defender_hp_before - damage);
        cout << attacker->get_name() << "(" << attacker->get_hitpoints() << ") hits " 
             << defender->get_name() << "(" << defender_hp_before << ") with " << damage << endl;
        cout << "The new hitpoints of " << defender->get_name() << " is " << defender->get_hitpoints() << endl;

        if (defender->get_hitpoints() <= 0) {
            cout << defender->get_name() << " has died." << endl;
            delete defender;
            grid[newX][newY] = attacker;
            grid[oldX][oldY] = nullptr;
            robot_count--;

            // Heal the attacker if they're one of the humanic robots
            if (attacker->get_type() == "optimusprime" || attacker->get_type() == "robocop") {
                int max_hp = (attacker->get_type() == "optimusprime") ? 100 : 40;
                if (attacker->get_hitpoints() < max_hp) {
                    attacker->set_hitpoints(attacker->get_hitpoints() + 1);
                }
            }
            return;
        }

        // Special: Roomba gets a bonus attack (surprise vacuum boop!) 🧹
        if (defender->get_type() == "roomba") {
            damage = defender->get_damage();
            int attacker_hp_before = attacker->get_hitpoints();
            attacker->set_hitpoints(attacker_hp_before - damage);
            cout << defender->get_name() << "(" << defender->get_hitpoints() << ") hits " 
                 << attacker->get_name() << "(" << attacker_hp_before << ") with " << damage << endl;
            cout << "The new hitpoints of " << attacker->get_name() << " is " << attacker->get_hitpoints() << endl;

            if (attacker->get_hitpoints() <= 0) {
                cout << attacker->get_name() << " has died." << endl;
                delete attacker;
                grid[oldX][oldY] = nullptr;
                robot_count--;

                // Defender gets a heal if they’re humanic
                if (defender->get_type() == "optimusprime" || defender->get_type() == "robocop") {
                    int max_hp = (defender->get_type() == "optimusprime") ? 100 : 40;
                    if (defender->get_hitpoints() < max_hp) {
                        defender->set_hitpoints(defender->get_hitpoints() + 1);
                    }
                }
                return;
            }
        }

        // Now it's the defender’s turn for revenge!
        damage = defender->get_damage();
        int attacker_hp_before = attacker->get_hitpoints();
        attacker->set_hitpoints(attacker_hp_before - damage);
        cout << defender->get_name() << "(" << defender->get_hitpoints() << ") hits " 
             << attacker->get_name() << "(" << attacker_hp_before << ") with " << damage << endl;
        cout << "The new hitpoints of " << attacker->get_name() << " is " << attacker->get_hitpoints() << endl;

        if (attacker->get_hitpoints() <= 0) {
            cout << attacker->get_name() << " has died." << endl;
            delete attacker;
            grid[oldX][oldY] = nullptr;
            robot_count--;

            // Heal defender if they're humanic
            if (defender->get_type() == "optimusprime" || defender->get_type() == "robocop") {
                int max_hp = (defender->get_type() == "optimusprime") ? 100 : 40;
                if (defender->get_hitpoints() < max_hp) {
                    defender->set_hitpoints(defender->get_hitpoints() + 1);
                }
            }
            return;
        }
    }
}

// Main simulation loop: runs until only one robot remains standing.
// Initializes robots, runs turns, and declares the champion!
void Simulation::runSimulation() {
    initializeRobots(); // Bring in the robo-gladiators!
    // displayGrid();   // Optional: Uncomment to show the grid before battle begins

    while (robot_count > 1) {  // Continue until we have a robo-champion
        resetFlags(); // Reset "already moved" flags so everyone gets a turn

        // Iterate over every grid cell to move active robots
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                // If there's a robot here and it hasn't moved this turn
                if (grid[i][j] != nullptr && grid[i][j]->get_flag() == 0) {
                    moveRobot(i, j); // Let it do its thing (move/fight)
                }
            }
        }
        // displayGrid(); // Optional: Uncomment to watch the carnage unfold turn by turn
    }

    // Once only one robot is left standing, find and announce the winner
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                cout << "\n\nThe winner is " << grid[i][j]->get_name()
                     << " (" << grid[i][j]->get_hitpoints() << " HP)" << endl;
                return;
            }
        }
    }
}


// Utility function: displays the grid to the console.
// Uses different letters to represent different robot types.
// Great for visual debugging or creating ASCII art warfare 
void Simulation::displayGrid() const {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == nullptr) {
                cout << ".";  // Empty space
            } else {
                string type = grid[i][j]->get_type();
                if (type == "optimusprime") cout << "O"; // O for Overpowered
                else if (type == "robocop") cout << "R"; // R for Reliable robo-cop
                else if (type == "roomba") cout << "m";  // m for mini vacuum 🧹
                else if (type == "bulldozer") cout << "B"; // B for Brutal
                else if (type == "kamikaze") cout << "K"; // K for Kaboom 💥
            }
        }
        cout << endl;
    }
    cout << endl;
}
