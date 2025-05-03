#pragma once
#include "Global_variables.h"
#include "Level.h"

class Sonic : public Player {
private:

public:
	// constructor
	Sonic() :Player("Data/0right_still.png", "Data/0left_still.png", 18) {}
};