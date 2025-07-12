#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include "Robot.h"

// Kamikaze class - represents a suicide attack robot that inherits from base Robot
// Special behavior: Always deals fixed high damage (10) regardless of strength,
// representing its suicidal attack nature. Has low base stats to balance this.
class kamikaze : public Robot {
private:
    // Member variables
    string name;       // Identifier name (though get_name() always returns "kamikaze")
    int type;         // Type identifier (4 for kamikaze)
    int strength;     // Low base strength (default 10) - not used for damage
    int hitpoints;    // Low health points (default 10) - fragile nature
    int flag;         // Status flag for tracking robot state

public:
    // Default constructor - initializes with characteristic low stats
    kamikaze() : Robot(), name(""), type(4), strength(10), hitpoints(10), flag(0) {}
    
    // Parameterized constructor - allows custom initialization
    kamikaze(int new_type, int new_strength, int new_hit, string name)
        : Robot(new_type, new_strength, new_hit, name) {}
    
    // Destructor
    ~kamikaze() {}

    // Returns the robot type as string
    string get_type() const override { return "kamikaze"; }

    // Special damage calculation:
    // Always returns fixed damage (10) regardless of strength  
    // This represents the robot's suicidal attack nature
    // Note: Completely overrides base Robot damage calculation
    int get_damage() override {
        return 10;  // Fixed high damage output
    }
};

#endif