#ifndef GOAL_FLEE_H
#define GOAL_FLEE_H
#pragma warning (disable:4786)

#include "Goals/Goal.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"


class Goal_Flee : public Goal<Raven_Bot>
{
private:
	Vector2D m_vFleePos;

	//the approximate time the bot should take to travel the target location
	double     m_dTimeToReachPos;

	//this records the time this goal was activated
	double     m_dStartTime;

	//returns true if a bot gets stuck
	bool      isStuck()const;

public:

	Goal_Flee(Raven_Bot* pBot, Vector2D target);

	void Activate();

	int Process();

	void Terminate();
};





#endif
