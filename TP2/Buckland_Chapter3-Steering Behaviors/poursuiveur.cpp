#include "poursuiveur.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"


Poursuiveur::Poursuiveur(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale, Vehicle* target, Vector2D offset) 
	: Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
	this->Steering()->OffsetPursuitOn(target, offset);
	this->SetMaxSpeed(71);
}
