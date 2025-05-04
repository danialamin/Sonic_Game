#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"

class EggStinger : public Enemy {
private:
	int hitsLeft;
	Clock xClock, hitClock;
	bool xRight = true;
	bool isHiting = false;

public:
	EggStinger(float x, float y) : Enemy(x, y, 0), hitsLeft(15) { // need to add parameters for later work(AHMED NOTE)
		texture.loadFromFile("Data/brick1.png");//temporary filler(AHMED NOTE)
		sprite.setTexture(texture);
	}

	void move(Player* p) {

		if (hitClock.getElapsedTime().asSeconds() >= 10)
		{
			hitPlayer(p);
		}
		else {
			if (xRight)
				x += 1;
			else
				x -= 1;
			if (xClock.getElapsedTime().asSeconds() > 4) { xRight = !xRight; xClock.restart(); }
			//NEED TO COMPLETE LOGIC (AHMED NOTE)
		}
	}

	void hitPlayer(Player* p) {

	}

	void destroyBlock() {}

	virtual void attackHero(Player* p) {
		if (p->getX() == x && p->getY() == y) {
			if (p->getJump()) {
				//gets attacked
				hitsLeft--;
				// make take damage function (AHMED NOTE)
				//will function called in parent class do dynamic polymorphism??? (REMINDER TO ASK SIR SHEHRYAR)

			}
			else {
				p->takeDamage();
			}

		}

	}
	//MUST MAKE FACTORY (AHMED NOTE)

};