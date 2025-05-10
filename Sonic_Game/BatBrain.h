#pragma once
#include <iostream>
#include "Global_variables.h"
#include"Enemy.h"

class BatBrain : public Enemy {
public:
	BatBrain(float x, float y, float x_limit[2], float y_limit[2]) : Enemy(x, y, 3, "Data/batbrain_right_39x29.png", "Data/batbrain_left_39x29.png", x_limit, y_limit) {}
	void move(Player* p) {
		if (p->getX()+36 > x) {
			x += 2;
			direction = 1;
		}
		else {
			x -= 2;
			direction = -1;
		}
	}
	void checkCollisionWithPlayer(Player* p) override {
		if (health>0)
		if (direction == 1) {
			if (p->getX() - x < 46 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
				if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
					p->takeDamage(); // player's health decreases
					cout << "p->health--" << endl;
				}
				else if (p->getIsABall()) { // collision happened while player was a ball
					if (p->getIsActive() && !p->getIsInvincible()) { // if active then he should not have been invincible to cause damage to enenmy
						health--; // enenmy's health decreases
					}
					else if (!p->getIsActive()) { // if passive then he can cause damage just because he is a ball
						health--; // enenmy's health decreases
					}
				}
			}
		}
		else {
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