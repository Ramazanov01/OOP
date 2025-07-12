#ifndef _BULLDOZER_H_
#define _BULLDOZER_H_

#include "Robot.h"

// Bulldozer class - represents a heavy, durable robot that inherits from base Robot
// Characteristics: High strength and hitpoints, but no special attack abilities
class bulldozer : public Robot {
private:
    // Member variables
    string name;       // Identifier name for the bulldozer
    int type;         // Type identifier (3 for bulldozer)
    int strength;     // High base attack strength (default 50)
    int hitpoints;    // Very high health points (default 200)
    int flag;         // Status flag for tracking robot state

public:
    // Default constructor - initializes with bulldozer's characteristic high stats
    bulldozer() : Robot(), name(""), type(3), strength(50), hitpoints(200), flag(0) {}
    
    // Parameterized constructor - allows custom initialization
    bulldozer(int new_type, int new_strength, int new_hit, string name)
        : Robot(new_type, new_strength, new_hit, name) {}
    
    // Destructor
    ~bulldozer() {}

    // Returns the robot type as string
    string get_type() const override { return "bulldozer"; }

    // Damage calculation:
    // Bulldozer uses the base Robot damage without any special abilities
    // Its advantage comes from high base stats rather than special attacks
    int get_damage() override {
        return Robot::get_damage();
    }
};

#endif