#ifndef HANDGRENADE_H
#define HANDGRENADE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Grenade
//
//  Author: 
//
//  Desc:   class to implement a grenade
//-----------------------------------------------------------------------------
#include "Raven_Weapon.h"



class  Raven_Bot;

class HandGrenade : public Raven_Weapon
{
private:

  void     InitializeFuzzyModule();

public:

  HandGrenade(Raven_Bot* owner);


  void Render();

  void ShootAt(Vector2D pos);

  double GetDesirability(double DistToTarget);
};



#endif