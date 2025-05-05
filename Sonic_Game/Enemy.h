#pragma once
#include "Global_variables.h"
#include "PlayerFactory.h"
#include "Player.h"
class Enemy {
protected:
	float x, y;
	int health;
	Sprite sprite;
	Texture texture;

public:
	Enemy(float x, float y, int health) : x(x), y(y), health(health) {}
	virtual void move(Player* p) = 0;
	virtual void attackHero(Player* p) {
		if (p->getX() == x && p->getY() == y) {
			if (p->getJump()) {
				//gets attacked
				health -= 2;//need to determine later on (AHMED NOTE)
				// make take damage function (AHMED NOTE)
				//will function called in parent class do dynamic polymorphism??? (REMINDER TO ASK SIR SHEHRYAR)

			}
			else {
				p->takeDamage();
			}

		}

	}
	virtual void draw(RenderWindow& window, Camera& camera) {
		// Calculate screen position
		float screenX = camera.worldToScreenX(x);
		float screenY = camera.worldToScreenY(y);

		// Set sprite position to screen coordinates
		sprite.setPosition(screenX, screenY);
		window.draw(sprite);
	}

	//IMPORTANT MUST IMPLEMENT DESTRUCTORS FOR ALL CLASSES (AHMED NOTE)


};