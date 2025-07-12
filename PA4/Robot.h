#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Abstract base class for all types of robots
class Robot
{
protected:
    int type;           // Robot's type identifier (e.g., 0 = OptimusPrime, 1 = Robocop, etc.)
    int strength;       // Damage potential (used in attack)
    int hitpoints;      // Current health
    string name;        // Robot's unique name
    int flag;           // Movement/combat flag (e.g., whether robot has moved/fought this turn)

public:
    // Default constructor - initializes flag to 0
    Robot() { flag = 0; };

    // Parametrized constructor - initializes all fields including flag to 0
    Robot(int new_type, int new_strength, int new_hit, string name)
        : type(new_type), strength(new_strength), hitpoints(new_hit), name(name) { flag = 0; };

    // Virtual destructor for proper cleanup of derived classes
    virtual ~Robot() {};

    // Pure virtual function - must be overridden in derived classes to return type name
    virtual string get_type() const = 0;

    // Getters and setters
    inline string get_name() const { return name; };
    inline void set_name(const string n) { name = n; };

    inline int get_strength() const { return strength; };
    inline void set_strength(int s) { strength = s; };

    inline int get_hitpoints() const { return hitpoints; };
    inline void set_hitpoints(int h) { hitpoints = h; };

    inline int get_flag() const { return flag; };
    inline void set_flag(int f) { flag = f; };

    // Virtual function to compute damage (can be overridden for special behavior)
    virtual int get_damage();
};

#endif
