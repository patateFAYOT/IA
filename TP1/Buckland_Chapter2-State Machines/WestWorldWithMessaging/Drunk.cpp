#include "Drunk.h"

bool Drunk::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}


void Drunk::Update()
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    m_pStateMachine->Update();
}

bool Drunk::isDrunk()
{
    if (m_Drunkness > max_drunkness) return true; 
    else return false;
}

bool Drunk::isSober()
{
    if (m_Drunkness == 0) return true; 
    else return false;
}

bool Drunk::WannaFight()
{
    if (m_Drunkness >= fight_drunkness) return true;
    else return false;
}