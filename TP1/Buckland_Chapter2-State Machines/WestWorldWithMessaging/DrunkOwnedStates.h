#ifndef DRUNK_OWNED_STATES_H
#define DRUNK_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class.
//          Note that a global state has not been implemented.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunk;
struct Telegram;



class HangoverRecovery : public State<Drunk>
{
private:

	HangoverRecovery(){}

	//copy ctor and assignment should be private
	HangoverRecovery(const HangoverRecovery&);
	HangoverRecovery& operator=(const HangoverRecovery&);

public:

	//this is a singleton
	static HangoverRecovery* Instance();

	virtual void Enter(Drunk* drunker);

	virtual void Execute(Drunk* drunker);

	virtual void Exit(Drunk* drunker);

	virtual bool OnMessage(Drunk* drunker, const Telegram& msg);

};


class GoingToSaloon : public State<Drunk>
{
private:

	GoingToSaloon() {}

	//copy ctor and assignment should be private
	GoingToSaloon(const GoingToSaloon&);
	GoingToSaloon& operator=(const GoingToSaloon&);

public:

	//this is a singleton
	static GoingToSaloon* Instance();

	virtual void Enter(Drunk* drunker);

	virtual void Execute(Drunk* drunker);

	virtual void Exit(Drunk* drunker);

	virtual bool OnMessage(Drunk* drunker, const Telegram& msg);

};


#endif