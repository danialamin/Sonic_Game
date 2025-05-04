#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Player.h"
class Projectile {
private:
	float x, y, targetX, targetY;
	Sprite sprite;
	Texture texture;
	bool destroy = false;
public:
	Projectile(float x, float y, float targetX, float targetY) : x(x), y(y), targetX(targetX), targetY(targetY) {
		//texture.loadFromFile();//NEED PLACE HOLDER (AHMED NOTE)
		//sprite.setTexture(texture);
	}

	bool getDestroy() { return destroy; }

	void move(Player* p) {
		if (targetX > x)
			x += 1; //need to determine speed later on(AHMED NOTE)
		else
			x -= 1;

		if (targetY > y)
			y += 1;
		else
			y -= 1;

		if (y = 200) { destroy = true; }
	}

	virtual void attackHero(Player* p) {
		if (p->getX() == x && p->getY() == y) {
			if (!p->getJump()) {
				p->takeDamage();
			}
		}
	}
	virtual void draw(RenderWindow& window) {
		sprite.setPosition(x, y);
		window.draw(sprite);
	}
};
