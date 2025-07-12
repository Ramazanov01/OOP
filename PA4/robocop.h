#ifndef _ROBOCOP_H_
#define _ROBOCOP_H_

#include "humanic.h"

// Robocop class - represents a Robocop robot that inherits from Humanic
class robocop : public humanic {
private:
    // Member variables
    string name;       // Name of the Robocop
    int type;         // Type identifier for the robot
    int strength;     // Attack strength of the robot
    int hitpoints;    // Health points of the robot
    int flag;         // Status flag (used for tracking state or conditions)

public:
    // Default constructor - initializes with default Robocop values
    robocop() : humanic(), name(""), type(1), strength(30), hitpoints(40), flag(0) {}
    
    // Parameterized constructor - allows custom initialization
    robocop(int new_type, int new_strength, int new_hit, string name) 
        : humanic(new_type, new_strength, new_hit, name) {};
    
    // Destructor
    ~robocop() {};

    // Returns the robot type as a string (overrides base class virtual function)
    string get_type() const override { return "robocop"; };

    // Calculates and returns damage dealt by this robot
    // Uses the humanic base class damage calculation
    int get_damage() override {                   
        return humanic::get_damage();
    }
};

#endif