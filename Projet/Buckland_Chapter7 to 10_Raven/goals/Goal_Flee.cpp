#include "Goal_Flee.h"
#include "..\Raven_Bot.h"
#include "..\Raven_SteeringBehaviors.h"
#include "time/CrudeTimer.h"
#include "debug/DebugConsole.h"


Goal_Flee::Goal_Flee(Raven_Bot* pBot, Vector2D target) : Goal<Raven_Bot>(pBot, goal_flee), m_vFleePos(target) {}

//---------------------------- Initialize -------------------------------------
//-----------------------------------------------------------------------------  
void Goal_Flee::Activate()
{
    debug_con << "The bot has begun to flee " << m_pOwner->ID() << "";
	m_iStatus = active;

    //record the time the bot starts this goal
    m_dStartTime = Clock->GetCurrentTime();

    //This value is used to determine if the bot becomes stuck 
    m_dTimeToReachPos = m_pOwner->CalculateTimeToReachPosition(m_vFleePos);

    //factor in a margin of error for any reactive behavior
    const double MarginOfError = 1.0;

    m_dTimeToReachPos += MarginOfError;

	m_pOwner->GetSteering()->FleeOn(m_vFleePos);
    m_pOwner->GetSteering()->WallAvoidanceOn();
}

//------------------------------ Process --------------------------------------
//-----------------------------------------------------------------------------
int Goal_Flee::Process()
{
    //if status is inactive, call Activate()
    ActivateIfInactive();

    //test to see if the bot has become stuck
    if (isStuck())
    {
        m_iStatus = failed;
    }

    //test to see if the bot has fled its target. If so terminate the goal
    else
    {
        if (!m_pOwner->GetTargetSys()->isTargetWithinFOV())
        {
            m_iStatus = completed;
        }
    }

    return m_iStatus;
}

//--------------------------- isBotStuck --------------------------------------
//
//  returns true if the bot has taken longer than expected to reach the 
//  currently active waypoint
//-----------------------------------------------------------------------------
bool Goal_Flee::isStuck()const
{
    double TimeTaken = Clock->GetCurrentTime() - m_dStartTime;

    if (TimeTaken > m_dTimeToReachPos)
    {
        debug_con << "BOT " << m_pOwner->ID() << " IS STUCK!!" << "";

        return true;
    }

    return false;
}

//---------------------------- Terminate --------------------------------------
//-----------------------------------------------------------------------------
void Goal_Flee::Terminate()
{
    debug_con << "The bot has fled " << m_pOwner << "";
	m_pOwner->GetSteering()->FleeOff();
}

