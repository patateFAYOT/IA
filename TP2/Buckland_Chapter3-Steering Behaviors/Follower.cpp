#include "Follower.h"
#include "SteeringBehaviors.h"
#include "misc/CellSpacePartition.h"
#include "misc/cgdi.h"

Follower::Follower(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale,
	Vehicle* agent,
	const Vector2D  offset) : Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
	Steering()->OffsetPursuitOn(agent, offset);
}