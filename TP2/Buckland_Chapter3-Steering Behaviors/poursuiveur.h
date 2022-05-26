#ifndef POURSUIVEUR
#define POURSUIVEUR

#include "Vehicle.h"


class Poursuiveur : public Vehicle {

private:
    Vector2D offset;
    Vehicle* Leader;
    Vehicle* neighbour;
public: 
    Poursuiveur(
        GameWorld* world,
        Vector2D position,
        double    rotation,
        Vector2D velocity,
        double    mass,
        double    max_force,
        double    max_speed,
        double    max_turn_rate,
        double    scale,
        Vehicle* target,
        Vehicle* neigbour,
        Vector2D offset);

    void Update(double time_elapsed);
};


#endif