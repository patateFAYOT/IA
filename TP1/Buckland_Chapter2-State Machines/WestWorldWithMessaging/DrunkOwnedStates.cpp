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


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
HangoverRecovery* HangoverRecovery::Instance()
{
    static HangoverRecovery instance;

    return &instance;
}


void HangoverRecovery::Enter(Drunk* pDrunker)
{
    //if the miner is not already located at the goldmine, he must
    //change location to the gold mine
    if (pDrunker->Location() != Roger_shack)
    {
        cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Feelin' sleepy";

        pDrunker->ChangeLocation(Roger_shack);
    }
}


void HangoverRecovery::Execute(Drunk* pDrunker)
{
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "Snortin' ";

    if (!pDrunker->isSober())
    {
        pDrunker->Sleeping();
    }
    else
    {
        pDrunker->GetFSM()->ChangeState(GoingToSaloon::Instance());
    }

}


void HangoverRecovery::Exit(Drunk* pDrunker)
{
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
        << "Slept well, goin' to the saloon";
}


GoingToSaloon* GoingToSaloon::Instance()
{
    static GoingToSaloon instance;

    return &instance;
}



void GoingToSaloon::Execute(Drunk* pDrunker)
{

    if (!pDrunker->WannaFight())
    {
        pDrunker->GetDrunk();
        cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": " << "That's some good whiskey ";
    }
    else
    {
        pDrunker->GetFSM()->ChangeState(DrinkAndFight::Instance());
    }

}

void GoingToSaloon::Exit(Drunk* pDrunker)
{
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
        << "gonna clap some chicks";
}


DrinkAndFight* DrinkAndFight::Instance()
{
    static DrinkAndFight instance;

    return &instance;
}

void DrinkAndFight::Enter(Drunk* pDrunker)
{
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
        << "Damn bob, i hate him";
}

void DrinkAndFight::Execute(Drunk* pDrunker)
{

    if (!pDrunker->isDrunk())
    {
        pDrunker->GetDrunk();
        
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDrunker->ID(),        //ID of sender
            ent_Miner_Bob,            //ID of recipient
            Msg_fight,   //the message
            NO_ADDITIONAL_INFO);

        cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
            << "HEY BOB COME HERE YOU COWARD";

    }
    else
    {
        pDrunker->GetFSM()->ChangeState(HangoverRecovery::Instance());
    }

}

void GoingToSaloon::Exit(Drunk* pDrunker)
{
    cout << "\n" << GetNameOfEntity(pDrunker->ID()) << ": "
        << "I'm tired, goin' home";
}