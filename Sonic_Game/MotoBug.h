#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"

class MotoBug :public Enemy {
public:
	MotoBug(float x, float y) : Enemy(x, y, 2) { // need to add parameters for later work(AHMED NOTE)
		texture.loadFromFile("Data/brick1.png");//temporary filler(AHMED NOTE)
		sprite.setTexture(texture);
	}

	void move(Player* p) {
		if (p->getX() > x)
			x += 1; //need to determine speed later on(AHMED NOTE)
		else
			x -= 1;


	}

};
