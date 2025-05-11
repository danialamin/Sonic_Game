#pragma once
#include <iostream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "BatBrain.h"
#include "EnemyFactory.h"

class BatBrainFactory : public EnemyFactory {
public:
	void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) override {
		enemy = new BatBrain(x, y, x_limit, y_limit);
	}
};