#ifndef LEADER
#define LEADER

#include "Vehicle.h"


class Leader : public Vehicle {

public:
    Leader(
        GameWorld* world,
        Vector2D position,
        double    rotation,
        Vector2D velocity,
        double    mass,
        double    max_force,
        double    max_speed,
        double    max_turn_rate,
        double    scale);


    void Update(double time_elapsed);

};


#endif