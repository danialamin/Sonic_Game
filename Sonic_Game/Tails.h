#pragma once
#include "Global_variables.h"
#include "Level.h"

class Tails : public Player {
private:

public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Tails(int activeOrPassive) :Player("Data/1right_still.png", "Data/1left_still.png", 10, "Data/1right_roll.png", "Data/1left_roll.png", activeOrPassive) {}
};