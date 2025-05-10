#pragma once
#include <iostream>
#include "Global_variables.h"
#include "CrabMeat.h"
#include "EnemyFactory.h"


class CrabMeatFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) override {
		enemy = new CrabMeat(x, y, x_limit, y_limit);
	}
};