#ifndef DRUNK_H
#define DRUNK_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
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

// the maximum level of drunkness
const int max_drunkness = 5;



class Drunk : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Drunk>* m_pStateMachine;

    location_type         m_Location;

    int                   m_Drunkness;
   

public:

    Drunk(int id) :m_Location(Roger_shack),
        m_Drunkness(0),
        BaseGameEntity(id)

    {
        //set up state machine
        m_pStateMachine = new StateMachine<Drunk>(this);

        m_pStateMachine->SetCurrentState(HangoverRecovery::Instance());

        /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
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

    bool          isSober() {}
    bool          isDrunk() {}
    void          GetDrunk() { m_Drunkness++; }
    void          Sleeping() { m_Drunkness--; }
};



#endif
