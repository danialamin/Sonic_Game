#pragma once
#include "Global_variables.h"
#include "Player.h"
#include "Level.h"

class Sonic : public Player {
private:

public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Sonic(int activeOrPassive) :Player("Data/0right_still.png", "Data/0left_still.png", 18, "Data/0roll_right.png", "Data/0roll_left.png", activeOrPassive){}
};