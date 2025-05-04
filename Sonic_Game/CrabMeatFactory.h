#pragma once
#include <iostream>
#include "Global_variables.h"
#include "CrabMeat.h"
#include "EnemyFactory.h"


class CrabMeatFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y) override {
		enemy = new CrabMeat(x, y);
	}
};