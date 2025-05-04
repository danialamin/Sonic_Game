#pragma once
#include <iostream>
#include "Global_variables.h"
#include "EnemyFactory.h"
#include "BeeBot.h"

class BeeBotFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y) override {
		enemy = new BeeBot(x, y);
	}
};