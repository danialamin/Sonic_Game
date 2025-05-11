#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "EnemyFactory.h"
#include "BeeBot.h"

class BeeBotFactory : public EnemyFactory {
public:
	virtual void createEnemy(float x, float y, float x_limit[2], float y_limit[2]) override {
		enemy = new BeeBot(x, y, x_limit, y_limit);
	}
};