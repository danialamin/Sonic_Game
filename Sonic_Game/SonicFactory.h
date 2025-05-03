#pragma once
#include <iostream>
#include "Global_variables.h"
#include "PlayerFactory.h"
#include "Sonic.h"

class SonicFactory : public PlayerFactory {
public:
	void createPlayer() override {
		player = new Sonic();
	}
};