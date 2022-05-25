#ifndef LEADER_H
#define LEADER_H

#include "Vehicle.h"

class Leader : public Vehicle
{
private:
	bool m_controlled = false;
public:
	Leader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale, 
		Color m_color);

	bool isControlled() { return m_controlled; }
	void toggleControlled();
};

#endif