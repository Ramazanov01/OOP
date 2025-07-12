#ifndef _HUMANIC_H_
#define _HUMANIC_H_

#include "Robot.h"

// Humanic class - represents humanoid-type robots that inherit from base Robot
// Special ability: 15% chance to deal bonus damage (+40) on attacks
class humanic : public Robot {
private:
    // Member variables
    string name;       // Identifier name for the humanic robot
    int type;         // Type identifier 
    int strength;     // Base attack strength
    int hitpoints;    // Health points
    int flag;         // Status flag for tracking robot state

public:
    // Default constructor - initializes with base Robot properties plus flag
    humanic() : Robot() { flag = 0; };
    
    // Parameterized constructor - allows custom initialization
    humanic(int new_type, int new_strength, int new_hit, string name)
        : Robot(new_type, new_strength, new_hit, name) {};
    
    // Destructor
    ~humanic() {};

    // Returns default humanic type as "robocop" 
    // Note: This should likely be "humanic" for base class
    string get_type() const override { return "robocop"; };

    // Specialized damage calculation:
    // - 15% chance to deal bonus damage (+40)
    // - Otherwise deals normal robot damage
    int get_damage() override {           
        int possibility = rand() % 100;  // Range 0-99 (15% chance)
        
        if (possibility < 15) {  // 15% probability
            return Robot::get_damage() + 40;  // Bonus damage
        }
        return Robot::get_damage();  // Normal damage
    }
};

#endif