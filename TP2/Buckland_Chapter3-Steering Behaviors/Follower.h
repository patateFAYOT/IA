#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Vehicle.h"

class Follower : public Vehicle
{
public:
	Follower(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale,
		Vehicle* agent,
		const Vector2D  offset);
};

#endif