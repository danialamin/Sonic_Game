#pragma once
#include <iostream>
#include "Global_variables.h"
#include "EnemyFactory.h"
#include "MotoBug.h"

class MotoBugFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) override {
		enemy = new MotoBug(x, y, x_limit,y_limit);
	}
};