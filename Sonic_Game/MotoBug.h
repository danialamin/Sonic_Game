#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"

class MotoBug :public Enemy {
public:
	MotoBug(float x, float y, float x_limit[2], float y_limit[2]) : Enemy(x, y, 2, "Data/motobug_right_35x29.png", "Data/motobug_left_35x29.png", x_limit, y_limit) {
		sprite.setScale(1.4, 1.5);
	}

	// moves within x_limits and if active player is within those limits then follow it
	void move(Player* p) { // gets active player as parameter
		if (p->getX()+36 > x_limit[0] && p->getX()+36 < x_limit[1]) { // if player is in the x limit of enemy then follow the player
			if (p->getX()+36 > x)
				x += 2;
			else
				x -= 2;
		}
		else { // if player is out of the x limit of enemy then move right until x_limit[1] and left until x_limit[0]
			if (direction == 1) {
				x += 2;
			}
			else if (direction == -1) {
				x -= 2;
			}

			// reverse direction if reaches the end of x_limit
			if (x - x_limit[0] < 2 && direction==-1) {
				direction = 1;
			}
			else if (x_limit[1]-x < 2 && direction==1) {
				direction = -1;
			}

		}
	}
	void checkCollisionWithPlayer(Player* p) override {
		if (health>0)
		if (p->getX() - x > 0) { // if player is on the right of enemy
			if (p->getX() - x < 46 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
				if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
					p->takeDamage(); // player's health decreases
					cout << "p->health--" << endl;
				}
				else if (p->getIsABall()) { // collision happened while player was a ball
					if (p->getIsActive() && !p->getIsInvincible()) { // if active then he should not have been invincible to cause damage to enenmy
						health--; // enenmy's health decreases
					}
					else if (!p->getIsActive()) {
						health--; // enenmy's health decreases
					}
				}
			}
		}
		else { // if player is on the left of enemy
			if (x - p->getX() < 46 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
				if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
					p->takeDamage(); // player's health decreases
					cout << "p->health--" << endl;
				}
				else if (p->getIsABall()) { // collision happened while player was a ball
					if (p->getIsActive() && !p->getIsInvincible()) { // if active then he should not have been invincible to cause damage to enenmy
						health--; // enenmy's health decreases
					}
					else if (!p->getIsActive()) { // is a ball and not active
						health--; // enenmy's health decreases
					}
				}
			}
		}
	}
};
