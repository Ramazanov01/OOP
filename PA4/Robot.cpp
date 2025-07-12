#include "Robot.h"

int Robot::get_damage() // implementation of get_damage here
{
    int damage;
    damage = (rand() % strength) + 1;
    return (damage);
}
