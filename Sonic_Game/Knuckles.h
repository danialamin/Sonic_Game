#pragma once
#include "Global_variables.h"
#include "Level.h"
#include "Player.h"
class Level;
class Knuckles : public Player {
private:

public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Knuckles(int activeOrPassive) :Player("Data/2right_still.png", "Data/2left_still.png", 12, "Data/2right_roll.png", "Data/2left_roll.png", activeOrPassive) {}
    virtual void Punch(Level* level);
	void checkCollisions(Level* level);
	
    
	
};