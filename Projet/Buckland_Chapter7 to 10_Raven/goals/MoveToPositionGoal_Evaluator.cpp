#include "MoveToPositionGoal_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


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
    if (pBot->GetTeam() == 1 && pBot->GetTargetBot()->ID() != pBot->GetGivenTarget()->ID())
    {
        Desirability = 1.0;
    }

    return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
/*void MoveToPositionGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
    pBot->GetBrain()->AddGoal_MoveToPosition();
}*/

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void MoveToPositionGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
    gdi->TextAtPos(Position, "MV: " + ttos(CalculateDesirability(pBot), 2));
    return;

    std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
    gdi->TextAtPos(Position + Vector2D(0, 12), s);
}