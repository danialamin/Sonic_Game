#pragma once
#include <iostream>
#include "Global_variables.h"
#include "EnemyFactory.h"
#include "BeeBot.h"

class BeeBotFactory : public EnemyFactory {
public:
	virtual void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) override {
		enemy = new BeeBot(x, y, x_limit, y_limit);
	}
};