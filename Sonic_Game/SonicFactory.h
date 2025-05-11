#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "PlayerFactory.h"
#include "Sonic.h"

class SonicFactory : public PlayerFactory {
public:
	void createPlayer(int activeOrPassive, int l2, int l3) override {
		player = new Sonic(activeOrPassive, l2, l3);
	}
};