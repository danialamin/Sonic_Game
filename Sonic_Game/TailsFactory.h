#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "PlayerFactory.h"
#include "Tails.h"

class TailsFactory : public PlayerFactory {
public:
	void createPlayer(int activeOrPassive, int l2, int l3) override {
		player = new Tails(activeOrPassive, l2, l3);
	}
};