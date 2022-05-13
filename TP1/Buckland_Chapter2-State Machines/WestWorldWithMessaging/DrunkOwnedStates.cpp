#include "DrunkOwnedStates.h"
#include "fsm/State.h"
#include "Drunk.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------DrunkAndQuarrel

DrunkAndQuarrel* DrunkAndQuarrel::Instance()
{
    static DrunkAndQuarrel instance;

    return &instance;
}

void DrunkAndQuarrel::Enter(Drunk* pDrunk)
{
    cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Feelin' a bit tippsy...";
}

void DrunkAndQuarrel::Execute(Drunk* pDrunk)
{
    if (!pDrunk->isDrunk())
    {
        cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Feelin' thirsty all of a sudden";
        pDrunk->GetFSM()->ChangeState(Drinking::Instance());
    }
    else
    {
        //start quarrel with Bob
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunk->ID(),        //ID of sender
            ent_Miner_Bob,       //ID of recipient
            Msg_WannaFight,      //the message
            NO_ADDITIONAL_INFO);

        cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "You're wife's a freakin' ice queen!";
    }
}

void DrunkAndQuarrel::Exit(Drunk* pDrunk)
{
}

bool DrunkAndQuarrel::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
    

    return false; //send message to global message handler
}

//------------------------------------------------------------------------Drinking

Drinking* Drinking::Instance()
{
    static Drinking instance;

    return &instance;
}

void Drinking::Enter(Drunk* pDrunk)
{
    cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Another bottle for me!";
}

void Drinking::Execute(Drunk* pDrunk)
{

    if (pDrunk->isDrunk())
    {
        pDrunk->GetFSM()->ChangeState(DrunkAndQuarrel::Instance());
    }
    else {
        pDrunk->Drink();
        cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "That's som' good stuff";
    }
}

void Drinking::Exit(Drunk* pDrunk)
{
    cout << "\n" << GetNameOfEntity(pDrunk->ID()) << ": " << "Not feelin' so good...";
}


bool Drinking::OnMessage(Drunk* pDrunk, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}