#pragma once
#include "Global_variables.h"
#include "Player.h"

class Level;

class Tails : public Player {
private:
	bool isFlying;
    Clock spaceOrUpKeyPressClock;
	float spaceOrUpKeyPressClockTime;
	Clock flyingClock;
	float flyingClockTime;
public:
	// constructor
	// activeOrPassive = 1 for active, 2 for passive1, 3 for passive2
	Tails(int activeOrPassive) :Player("Data/1right_still.png", "Data/1left_still.png", 10, "Data/1right_roll.png", "Data/1left_roll.png", activeOrPassive) {}

    void applyGravity(Level* level) override;

    void jump() override {

        if (onGround) { // jump when the player is on the ground
            velocityY = jumpForce;
            onGround = false;
            inAJump = true;
            isFlying = false;
			spaceOrUpKeyPressClock.restart();
        }
        else if (!onGround && isActive && flyingClockTime < 7 && spaceOrUpKeyPressClockTime>0.2) { // if up/space key pressed while not on ground then start flying
            velocityY = -5;
            inAJump = false;
            isABall = false;
            isFlying = true;
            spaceOrUpKeyPressClock.restart();
        }
    }
};