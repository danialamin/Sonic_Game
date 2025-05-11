#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Player.h"
#include "Level.h"

class Sonic : public Player {
private:

public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Sonic(int activeOrPassive, int l2, int l3) :Player("Data/0right_still.png", "Data/0left_still.png", 18, "Data/0roll_right.png", "Data/0roll_left.png", activeOrPassive, l2, l3){}

	void activateSpecialAbility() override {
		// Activate the super power
		specialAbilityClock.restart();
		specialAbilityClockTime = 0;
		minSpeedX = 6.5;
		if (l3) {
			maxSpeedX = 18;
		} else {
			maxSpeedX = 22;
		}
	}

	void manageSpecialAbility() override {
		if (specialAbilityClockTime >= 15) { // specialAbilityClockTime has passed its limit
			minSpeedX = 2.5;
			if (l3) {
				maxSpeedX = 13;
			}
			else {
				maxSpeedX = 17;
			}
		}
		else {
			specialAbilityClockTime = specialAbilityClock.getElapsedTime().asSeconds();
		}
	}
};