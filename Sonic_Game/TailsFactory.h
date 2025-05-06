#pragma once
#include <iostream>
#include "Global_variables.h"
#include "PlayerFactory.h"
#include "Tails.h"

class TailsFactory : public PlayerFactory {
public:
	void createPlayer(int activeOrPassive) override {
		player = new Tails(activeOrPassive);
	}
};