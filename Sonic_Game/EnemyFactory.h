#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Enemy.h"

class EnemyFactory { // abstract class
protected:
	Enemy* enemy;

public:
	// pure virtual function
	virtual void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) = 0;

	// getters
	Enemy* getEnemy() {
		return enemy;
	}

	// destructor is virtual so that child constructor is called first
	virtual ~EnemyFactory() {
		delete enemy;
	}

};
