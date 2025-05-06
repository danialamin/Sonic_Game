#pragma once
#include <iostream>
#include "Global_variables.h"
#include "PlayerFactory.h"
#include "Knuckles.h"

class KnucklesFactory : public PlayerFactory {
public:
	void createPlayer(int activeOrPassive) override {
		player = new Knuckles(activeOrPassive);
	}
};