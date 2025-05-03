#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Player.h"

class PlayerFactory { // abstract class
protected:
	Player* player;

public:
	// pure virtual function
	virtual void createPlayer() = 0;

	// getters
	Player* getPlayer() {
		return player;
	}

	// destructor is virtual so that child constructor is called first
	virtual ~PlayerFactory() {
		delete player;
	}

};