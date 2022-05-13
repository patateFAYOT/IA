#include "Drunk.h"

bool Drunk::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Drunk::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Drunk::isDrunk() const
{
	if (m_iDrunkness >= DrunkLevel) { return true; }

	return false;
}