#pragma once
#include <iostream>
#include "Global_variables.h"
#include "EnemyFactory.h"
#include "MotoBug.h"

class MotoBugFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y) override {
		enemy = new MotoBug(x, y);
	}
};