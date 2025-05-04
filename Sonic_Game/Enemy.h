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
	virtual void draw(RenderWindow& window) {
		sprite.setPosition(x, y);
		window.draw(sprite);
	}

	//IMPORTANT MUST IMPLEMENT DESTRUCTORS FOR ALL CLASSES (AHMED NOTE)


};








//need to put this in seperate file (AHMED NOTE)
class BatBrain : public Enemy {
public:
	BatBrain(float x, float y) : Enemy(x, y, 3) { // need to add parameters for later work(AHMED NOTE)
		texture.loadFromFile("Data/brick1.png");//temporary filler(AHMED NOTE)
		sprite.setTexture(texture);
	}
	void move(Player* p) {
		if (p->getX() > x)
			x += 1; //need to determine speed later on(AHMED NOTE)
		else
			x -= 1;

		if (p->getY() > y)
			y += 1;
		else
			y -= 1;
	}


};

class BeeBot : public Enemy {

private:
	Projectile** projectile = new Projectile * [10];
	Clock projectileClock;
	Clock xClock;
	Clock yClock;
	bool yUp = true, xRight = true;

public:
	BeeBot(float x, float y) : Enemy(x, y, 5) { // need to add parameters for later work(AHMED NOTE)

		texture.loadFromFile("Data/brick1.png");//temporary filler(AHMED NOTE)
		sprite.setTexture(texture);
	}
	void move(Player* p) {

		if (yUp)
			y += 1;
		else
			y -= 1;
		if (yClock.getElapsedTime().asSeconds() > 1.5) { yUp = !yUp; yClock.restart(); }

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


};







class EnemyFactory {
public:
	Enemy* createEnemy(string& type, float x = 0.0f, float y = 0.0f) {
		if (type == "BatBrain") {
			return new BatBrain(); // pass coordinates later on (AHMED NOTE)
		}
		else if (type == "BeeBot") {
			return new BeeBot();
		}
		else if (type == "MotoBug") {
			return new MotoBug();
		}
		else if (type == "CrabMeat") {
			return new CrabMeat();
		}
		else if (type == "EggStinger") {
			return new EggStinger();
		}
		else {
			return nullptr;
		}
	}
};


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