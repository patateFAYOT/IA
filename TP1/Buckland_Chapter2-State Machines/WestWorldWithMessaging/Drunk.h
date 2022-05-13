#ifndef DRUNK_H
#define DRUNK_H
//------------------------------------------------------------------------
//
//  Name:   DRUNK.h
//
//  Desc:   A class defining a drunk.
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State;
struct Telegram;

//above this value a drunk is drunk
const int DrunkLevel = 5;


class Drunk : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Drunk>* m_pStateMachine;

    location_type         m_Location = saloon;

    //the higher the value, the thirstier the miner
    int                   m_iDrunkness;

public:

    Drunk(int id):m_iDrunkness(0),BaseGameEntity(id)
    {
        //set up state machine
        m_pStateMachine = new StateMachine<Drunk>(this);

        m_pStateMachine->SetCurrentState(Drinking::Instance());
    }

    ~Drunk() { delete m_pStateMachine; }

    //this must be implemented
    void Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);


    StateMachine<Drunk>* GetFSM()const { return m_pStateMachine; }



    //-------------------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    bool          isDrunk()const;
    void          Drink() { m_iDrunkness += 2; }

};



#endif