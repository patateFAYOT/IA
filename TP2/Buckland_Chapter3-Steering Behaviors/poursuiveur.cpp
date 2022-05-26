#include "poursuiveur.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"


Poursuiveur::Poursuiveur(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale, Vehicle* target, Vehicle* neigbour, Vector2D offset)
	: Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
	this->offset = offset;
	this->neighbour = neigbour;
	this->Leader = target;
	this->Steering()->OffsetPursuitOn(target, offset);
	this->SetMaxSpeed(150);
}

void Poursuiveur::Update(double time_elapsed)
{
	Vehicle::Update(time_elapsed);

	if (!this->World()->GetCrossHair())
	{
		this->Steering()->OffsetPursuitOff();
		this->Steering()->OffsetPursuitOn(Leader, offset);
	}
	else
	{
		this->Steering()->OffsetPursuitOff();
		this->Steering()->OffsetPursuitOn(neighbour, Vector2D(1,1));

	}

}