#ifndef SIMULATION_H
#define SIMULATION_H

#include "Robot.h"
#include "humanic.h"
#include <utility>
#include "optimusprime.h"
#include "robocop.h"
#include "roomba.h"
#include <vector>
#include "bulldozer.h"
#include "kamikaze.h"
#include <algorithm>
#include <ctime>

// Class representing the robot battle simulation
class Simulation {
private:
    static const int GRID_SIZE = 10;  // Size of the simulation grid (10x10)
    int robot_count;                 // Count of robots in the simulation
    Robot* grid[GRID_SIZE][GRID_SIZE]; // 2D array representing the grid with Robot pointers

    // Resets flags or states of all robots before each simulation step
    void resetFlags();

    // Moves a robot located at position (x, y) on the grid
    void moveRobot(int x, int y);

    // Handles combat between two robots when they meet
    // attacker: The robot initiating the attack
    // defender: The robot being attacked
    // newX, newY: The intended new position of the attacker
    // oldX, oldY: The original position of the attacker
    void fight(Robot* attacker, Robot* defender, int newX, int newY, int oldX, int oldY);

public:
    Simulation();   // Constructor
    ~Simulation();  // Destructor

    // Initializes the simulation by creating and placing robots on the grid
    void initializeRobots();

    // Runs the main simulation loop where robots move and fight
    void runSimulation();  // Changed from simulation_loop to runSimulation

    // Displays the current state of the grid (for visualization)
    void displayGrid() const;
};

#endif