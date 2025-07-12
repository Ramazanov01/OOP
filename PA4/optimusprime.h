#ifndef _OPTIMUSPRIME_H_
#define _OPTIMUSPRIME_H_

#include "humanic.h"

// OptimusPrime class - represents a powerful leader robot inheriting from Humanic
// Has a special ability: 20% chance to deal double damage
class optimusprime : public humanic {
private:
    // Member variables
    string name;       // Name of the Optimus Prime robot
    int type;         // Type identifier (0 for Optimus Prime)
    int strength;     // High base attack strength (default 100)
    int hitpoints;    // High base health points (default 100)
    int flag;         // Status flag for tracking robot state

public:
    // Default constructor - initializes with strong default values
    optimusprime() : humanic(), name(""), type(0), strength(100), hitpoints(100), flag(0) {}
    
    // Parameterized constructor - allows custom initialization while maintaining Humanic properties
    optimusprime(int new_type, int new_strength, int new_hit, string name) 
        : humanic(new_type, new_strength, new_hit, name) {};
    
    // Destructor
    ~optimusprime() {};

    // Returns the robot type as string (overrides base class virtual function)
    string get_type() const override { return "optimusprime"; };

    // Calculates damage with special ability:
    // - 20% chance to deal double damage (strong attack)
    // - Otherwise deals normal Humanic damage
    int get_damage() override {
        int possibility = rand() % 100 + 1; // Random number between 1-100
        
        // 20% chance for critical hit (numbers 1-20)
        if (possibility <= 20) {
            return humanic::get_damage() * 2; // Double damage
        }
        return humanic::get_damage(); // Normal damage
    }
};

#endif