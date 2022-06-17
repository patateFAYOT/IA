#ifndef LEARNING_BOT_H
#define LEARNING_BOT_H
#pragma warning (disable:4786)

#include "Raven_Bot.h"
#include "CNeuralNet.h"

class Learning_Bot : public Raven_Bot
{
private:
	CNeuralNet m_CNNModel;

public:
	Learning_Bot(Raven_Game* world, Vector2D pos);
	void Update();
};

#endif