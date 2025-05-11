#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "PlayerFactory.h"
#include "Player.h"
#include "Projectile.h"

class Enemy {
protected:
	float x, y;
	int health;
	int direction;
	Sprite sprite;
	Texture textureRight;
	Texture textureLeft;
	float x_limit[2]; // the range over which enemy will move in a level
	float y_limit[2]; // the range over which enemy will move in a level
public:
	// constructor
	Enemy(float x, float y, int health, string textureRight_arg, string textureLeft_arg, float x_limit[2], float y_limit[2]) : x(x), y(y), health(health) {
		this->x_limit[0] = x_limit[0];
		this->x_limit[1] = x_limit[1];
		this->y_limit[0] = y_limit[0];
		this->y_limit[1] = y_limit[1];
		textureRight.loadFromFile(textureRight_arg);
		textureLeft.loadFromFile(textureLeft_arg);
		direction = 1;

		this->health = health;
	}

	// pure virtual functions
	virtual void move(Player* p) = 0;
	virtual void checkCollisionWithPlayer(Player* p) = 0;

	virtual void draw(RenderWindow& window, Camera& camera) {
		if (health <= 0) {
			return; // Don't draw if the enemy is dead
		}
		// Calculate screen position
		float screenX = camera.worldToScreenX(x);
		float screenY = camera.worldToScreenY(y);

		// Set sprite position to screen coordinates
		sprite.setPosition(screenX, screenY);
		/*if (direction == 1) {
			sprite.setTexture(textureRight);
		}
		else {
			sprite.setTexture(textureLeft);
		}*/
		sprite.setTexture(textureRight);
		window.draw(sprite);
	}

	virtual Projectile** getProjectilesArray() { // only crabmeat and beebot have projectiles. without this virtual function enemy* for crabmeat and beebot cannot access this function
		return nullptr;
	}

	// virtual destructor
	virtual ~Enemy() {
	}
};