#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Player.h"

class Level;

class Knuckles : public Player {
private:
public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Knuckles(int activeOrPassive, int l2, int l3) :Player("Data/2right_still.png", "Data/2left_still.png", 12, "Data/2right_roll.png", "Data/2left_roll.png", activeOrPassive, l2, l3) {}

    void Punch(Level* level);

	void checkCollisions(Level* level);

	void activateSpecialAbility() override {
		// Activate the super power
		specialAbilityClock.restart();
		specialAbilityClockTime = 0;
		isInvincibleFromSpecialAbility = true;
	}

	void manageSpecialAbility() override {
		if (specialAbilityClockTime >= 15) { // specialAbilityClockTime has passed its limit
			isInvincibleFromSpecialAbility = false;
		}
		else {
			specialAbilityClockTime = specialAbilityClock.getElapsedTime().asSeconds();
		}
	}
};