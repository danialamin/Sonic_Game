#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"

class EnemyFactory { // abstract class
protected:
	Enemy* enemy;

public:
	// pure virtual function
	virtual void createEnemy() = 0;

	// getters
	Enemy* getEnemy() {
		return enemy;
	}

	// destructor is virtual so that child constructor is called first
	virtual ~EnemyFactory() {
		delete enemy;
	}

};
