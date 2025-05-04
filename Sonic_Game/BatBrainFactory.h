#pragma once
#include <iostream>
#include "Global_variables.h"
#include "BatBrain.h"
#include "EnemyFactory.h"

class BatBrainFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y) override {
		enemy = new BatBrain(x, y);
	}
};