#include "MoveToPositionGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"
#include "../Raven_SensoryMemory.h"
#include "Goal_AttackTarget.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double MoveToPositionGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
    double Desirability = 0.0;

    //only do the calculation if there is a target present
    if (pBot->GetTargeting() && pBot->Pos() != pBot->GetDestination())
    {
        Desirability = 1.0;
    }

    return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void MoveToPositionGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
    std::list<Raven_Bot*> sensedBots = pBot->GetSensoryMem()->GetListOfRecentlySensedOpponents();

    bool found = false;

    for(Raven_Bot * bot : sensedBots) {
        if (bot->ID() == pBot->GetGivenTarget()->ID()) {
            found = true;

            pBot->GetBrain()->AddSubgoal(new Goal_AttackTarget(pBot));
            return;
        }
    }

    pBot->GetBrain()->AddGoal_Explore();
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void MoveToPositionGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
    gdi->TextAtPos(Position, "MV: " + ttos(CalculateDesirability(pBot), 2));
    return;

    std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
    gdi->TextAtPos(Position + Vector2D(0, 12), s);
}