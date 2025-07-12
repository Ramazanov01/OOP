#ifndef _ROOMBA_H_
#define _ROOMBA_H_

#include "Robot.h"

// Roomba class - represents a specialized cleaning robot that inherits from base Robot
// Unique behavior: Always deals double damage in attacks
class roomba : public Robot {
private:
    // Member variables
    string name;       // Identifier name for the Roomba
    int type;         // Type identifier (2 for Roomba)
    int strength;     // Base attack strength (default 3)
    int hitpoints;    // Health points (default 10)
    int flag;         // Status flag for tracking robot state

public:
    // Default constructor - initializes with Roomba-specific default values
    roomba() : Robot(), name(""), type(2), strength(3), hitpoints(10), flag(0) {}
    
    // Parameterized constructor - allows custom initialization while maintaining Robot properties
    roomba(int new_type, int new_strength, int new_hit, string name)
        : Robot(new_type, new_strength, new_hit, name) {};
    
    // Destructor
    ~roomba() {};

    // Returns the robot type as string (overrides base class virtual function)
    string get_type() const override { return "roomba"; };

    // Specialized damage calculation:
    // Roomba always deals double the normal robot damage
    // This represents its aggressive cleaning/attack behavior
    int get_damage() override {
        return Robot::get_damage() * 2;
    }
};

#endif