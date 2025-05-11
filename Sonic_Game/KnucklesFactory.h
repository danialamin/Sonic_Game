#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "PlayerFactory.h"
#include "Knuckles.h"

class KnucklesFactory : public PlayerFactory {
public:
	void createPlayer(int activeOrPassive, int l2, int l3) override {
		player = new Knuckles(activeOrPassive, l2, l3);
	}
};