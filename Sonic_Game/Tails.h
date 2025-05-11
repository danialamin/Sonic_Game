#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Player.h"

class Level;

class Tails : public Player {
private:
	bool isFlying;
    Clock spaceOrUpKeyPressClock;
	float spaceOrUpKeyPressClockTime;
	Clock flyingClock;
	float flyingClockTime;
	float flyingMaxTime;
public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
    Tails(int activeOrPassive, int l2, int l3) :Player("Data/1right_still.png", "Data/1left_still.png", 10, "Data/1right_roll.png", "Data/1left_roll.png", activeOrPassive, l2, l3) { 
		jumpForce = -18.0f; 
		flyingMaxTime = 7;
	}

    void applyGravity(Level* level) override;

    void jump() override {

        if (onGround) { // jump when the player is on the ground
            velocityY = jumpForce;
            onGround = false;
            inAJump = true;
            isFlying = false;
			spaceOrUpKeyPressClock.restart();
        }
        else if (!onGround && isActive && flyingClockTime < flyingMaxTime && spaceOrUpKeyPressClockTime>0.2) { // if up/space key pressed while not on ground then start flying
            velocityY = -5;
            inAJump = false;
            isABall = false;
            isFlying = true;
            spaceOrUpKeyPressClock.restart();
        }
    }

	void activateSpecialAbility() override {
		// Activate the super power
		specialAbilityClock.restart();
		specialAbilityClockTime = 0;
		flyingMaxTime = 11;
	}

	void manageSpecialAbility() override {
		if (specialAbilityClockTime >= 15) { // specialAbilityClockTime has passed its limit
			flyingMaxTime = 7;
		}
		else {
			specialAbilityClockTime = specialAbilityClock.getElapsedTime().asSeconds();
		}
	}
};