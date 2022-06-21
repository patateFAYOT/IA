#include "Weapon_HandGrenade.h"
#include "../Raven_Bot.h"
#include "misc/Cgdi.h"
#include "../Raven_Game.h"
#include "../Raven_Map.h"
#include "../lua/Raven_Scriptor.h"
#include "fuzzy/FuzzyOperators.h"


//--------------------------- ctor --------------------------------------------
//-----------------------------------------------------------------------------
HandGrenade::HandGrenade(Raven_Bot*   owner):

                      Raven_Weapon(type_hand_grenade,
                                   script->GetInt("HandGrenade_DefaultRounds"),
                                   script->GetInt("HandGrenade_MaxRoundsCarried"),
                                   script->GetDouble("HandGrenade_FiringFreq"),
                                   script->GetDouble("HandGrenade_IdealRange"),
                                   script->GetDouble("Grenade_MaxSpeed"),
                                   owner)
{
    //setup the vertex buffer
  const int NumWeaponVerts = 8;
  const Vector2D weapon[NumWeaponVerts] = {Vector2D(0, -3),
                                           Vector2D(6, -3),
                                           Vector2D(6, -1),
                                           Vector2D(15, -1),
                                           Vector2D(15, 1),
                                           Vector2D(6, 1),
                                           Vector2D(6, 3),
                                           Vector2D(0, 3)
                                           };
  for (int vtx=0; vtx<NumWeaponVerts; ++vtx)
  {
    m_vecWeaponVB.push_back(weapon[vtx]);
  }

  //setup the fuzzy module
  InitializeFuzzyModule();

}


//------------------------------ ShootAt --------------------------------------
//-----------------------------------------------------------------------------
inline void HandGrenade::ShootAt(Vector2D pos)
{ 
  if (NumRoundsRemaining() > 0 && isReadyForNextShot())
  {
    //launch a Grenade!
    m_pOwner->GetWorld()->AddGrenade(m_pOwner, pos);

    m_iNumRoundsLeft--;

    UpdateTimeWeaponIsNextAvailable();

    //add a trigger to the game so that the other bots can hear this shot
    //(provided they are within range)
    m_pOwner->GetWorld()->GetMap()->AddSoundTrigger(m_pOwner, script->GetDouble("HandGrenade_SoundRange"));
  }
}

//---------------------------- Desirability -----------------------------------
//
//-----------------------------------------------------------------------------
double HandGrenade::GetDesirability(double DistToTarget)
{
  if (m_iNumRoundsLeft == 0)
  {
    m_dLastDesirabilityScore = 0;
  }
  else
  {
    //fuzzify distance and amount of ammo
    m_FuzzyModule.Fuzzify("DistToTarget", DistToTarget);
    m_FuzzyModule.Fuzzify("AmmoStatus", (double)m_iNumRoundsLeft);

    m_dLastDesirabilityScore = m_FuzzyModule.DeFuzzify("Desirability", FuzzyModule::max_av);
  }

  return m_dLastDesirabilityScore;
}

//-------------------------  InitializeFuzzyModule ----------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void HandGrenade::InitializeFuzzyModule()
{
  FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");

  FzSet& Target_Close = DistToTarget.AddTriangularSet("Target_Close",0,50,200);
  FzSet& Target_Medium = DistToTarget.AddTriangularSet("Target_Medium",50,200,300);
  FzSet& Target_Far = DistToTarget.AddRightShoulderSet("Target_Far",200,300,1000);

  FuzzyVariable& Desirability = m_FuzzyModule.CreateFLV("Desirability"); 
  FzSet& VeryDesirable = Desirability.AddRightShoulderSet("VeryDesirable", 50, 75, 100);
  FzSet& Desirable = Desirability.AddTriangularSet("Desirable", 25, 50, 75);
  FzSet& Undesirable = Desirability.AddLeftShoulderSet("Undesirable", 0, 25, 50);

  FuzzyVariable& AmmoStatus = m_FuzzyModule.CreateFLV("AmmoStatus");
  FzSet& Ammo_Loads = AmmoStatus.AddRightShoulderSet("Ammo_Loads", 0, 4, 5);
  FzSet& Ammo_Okay = AmmoStatus.AddTriangularSet("Ammo_Okay", 0, 2, 4);
  FzSet& Ammo_Low = AmmoStatus.AddTriangularSet("Ammo_Low", 0, 0, 2);

  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Loads), Undesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Okay), Undesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Close, Ammo_Low), Undesirable);

  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Loads), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Okay), VeryDesirable);
  m_FuzzyModule.AddRule(FzAND(Target_Medium, Ammo_Low), Desirable);

  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Loads), Desirable);
  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Okay), Desirable);
  m_FuzzyModule.AddRule(FzAND(Target_Far, Ammo_Low), Undesirable);

}


//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void HandGrenade::Render()
{
    m_vecWeaponVBTrans = WorldTransform(m_vecWeaponVB,
                                   m_pOwner->Pos(),
                                   m_pOwner->Facing(),
                                   m_pOwner->Facing().Perp(),
                                   m_pOwner->Scale());

  gdi->BluePen();

  gdi->ClosedShape(m_vecWeaponVBTrans);
}