#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"
#include "Projectile.h"


class CrabMeat :public Enemy {
private:
	Projectile** projectile = new Projectile * [10];
	Clock projectileClock;
	Clock xClock;
	bool xRight = true;
public:
	CrabMeat(float x, float y) : Enemy(x, y, 4) { // need to add parameters for later work(AHMED NOTE)
		texture.loadFromFile("Data/brick1.png");//temporary filler(AHMED NOTE)
		sprite.setTexture(texture);
	}
	void move(Player* p) {


		if (xRight)
			x += 1;
		else
			x -= 1;
		if (xClock.getElapsedTime().asSeconds() > 4) { xRight = !xRight; xClock.restart(); }

	}
	void shootProjectile(Player* p) {
		if (projectileClock.getElapsedTime().asSeconds() >= 5) {
			int findProjectile = 0;
			while (projectile[findProjectile++] != NULL) {}
			projectile[findProjectile] = new Projectile(x, y, p->getX(), p->getY());
			projectileClock.restart();
		}
	}

	void destroyProjectile() {
		for (int i = 0; i < 10; i++)
		{
			if (projectile[i]->getDestroy()) {
				delete projectile[i];
				projectile[i] = NULL;
			}

		}
	}
};
