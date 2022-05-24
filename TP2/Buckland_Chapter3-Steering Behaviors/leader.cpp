#include "leader.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"

Leader::Leader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale)
	: Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
	this->SetScale(Vector2D(15, 15));
	this->Steering()->WanderOn();
	this->SetMaxSpeed(70);

}

void Leader::Update(double time_elapsed) {

	Vehicle::Update(time_elapsed);
	if (!this->World()->GetCrossHair())
	{
		this->Steering()->WanderOff();
		this->Steering()->ArriveOn();
	}
	else
	{ 
		this->Steering()->ArriveOff();
		this->Steering()->WanderOn();
		
	}

}