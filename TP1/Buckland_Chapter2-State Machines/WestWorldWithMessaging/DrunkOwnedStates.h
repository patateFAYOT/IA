#ifndef DRUNK_OWNED_STATES_H
#define DRUNK_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drnk class.
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunk;
struct Telegram;

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class DrunkAndQuarrel : public State<Drunk>
{
private:

	DrunkAndQuarrel() {}

	//copy ctor and assignment should be private
	DrunkAndQuarrel(const DrunkAndQuarrel&);
	DrunkAndQuarrel& operator=(const DrunkAndQuarrel&);

public:

	//this is a singleton
	static DrunkAndQuarrel* Instance();

	virtual void Enter(Drunk* drunk);

	virtual void Execute(Drunk* drunk);

	virtual void Exit(Drunk* drunk);

	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class Drinking : public State<Drunk>
{
private:

	Drinking() {}

	//copy ctor and assignment should be private
	Drinking(const Drinking&);
	Drinking& operator=(const Drinking&);

public:

	//this is a singleton
	static Drinking* Instance();

	virtual void Enter(Drunk* drunk);

	virtual void Execute(Drunk* drunk);

	virtual void Exit(Drunk* drunk);

	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

#endif