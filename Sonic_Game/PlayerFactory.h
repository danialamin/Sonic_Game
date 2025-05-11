#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Player.h"

class PlayerFactory { // abstract class
protected:
	Player* player;

public:
	// pure virtual function
	virtual void createPlayer(int activeOrPassive, int l2, int l3) = 0;

	// getters
	Player* getPlayer() {
		return player;
	}

	// destructor is virtual so that child constructor is called first
	virtual ~PlayerFactory() {
		delete player;
	}

};