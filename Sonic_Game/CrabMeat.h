#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"
#include "Projectile.h"


class CrabMeat :public Enemy {
private:
    static const int MAX_PROJECTILES = 20; // after 20 the projectiles will be replaced
    Projectile* projectiles[MAX_PROJECTILES];
    int projectileCount;
public:
	CrabMeat(float x, float y, float x_limit[2], float y_limit[2]) : Enemy(x, y, 4, "Data/crabmeat_39x29.png", "Data/crabmeat_39x29.png", x_limit, y_limit) {
        direction = 1;
        sprite.setTexture(textureRight);
        sprite.setScale(1.4, 1.5);

        projectileCount = 0;
        // Initialize all projectiles to nullptr
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            projectiles[i] = nullptr;
        }
    }
	void move(Player* p) {
        if (direction == 1) {
            x += 2;

            // Update all active projectiles to move with the crab
            for (int i = 0; i < projectileCount; i++) {
                if (projectiles[i] != nullptr && projectiles[i]->isActive()) {
                    projectiles[i]->update();
                }
            }
        }
        else if (direction == -1) {
            x -= 2;

            // Update all active projectiles to move with the crab
            for (int i = 0; i < projectileCount; i++) {
                if (projectiles[i] != nullptr && projectiles[i]->isActive()) {
                    projectiles[i]->update();
                }
            }
        }

        // reverse direction if reaches the end of x_limit
        if (x - x_limit[0] < 2 && direction == -1) {
            direction = 1;
            if (health>0)
                fireProjectile(-1, 1);
        }
        else if (x_limit[1] - x < 2 && direction == 1) {
            direction = -1;
            if (health > 0)
                fireProjectile(1, 1);
        }
	}

    // Add projectile to array
    void fireProjectile(float dirX, float dirY) {
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i] == nullptr || !projectiles[i]->isActive()) { // Find an empty slot in the array
                if (projectiles[i] != nullptr) { // If slot is occupied but inactive, delete the old projectile
                    delete projectiles[i];
                }

                // Create new projectile
                projectiles[i] = new Projectile(x, y, dirX, dirY, 5.0f, "Data/projectile.png", 1);

                // Update count if needed
                if (i >= projectileCount) {
                    projectileCount = i + 1;
                }
                return;
            }
        }

        // If all slots are full, replace the oldest one
        if (projectileCount > 0) {
            delete projectiles[0];
            for (int i = 0; i < projectileCount - 1; i++) {
                projectiles[i] = projectiles[i + 1];
            }
            projectiles[projectileCount - 1] = new Projectile(x, y, dirX, dirY, 5.0f, "Data/projectile.png");
        }
    }

    // getters
    Projectile** getProjectilesArray() override {
        return projectiles;
    }

    void checkCollisionWithPlayer(Player* p) override {
        if (health>0)
        if (p->getX() - x > 0) { // player is to the right of the crab
            if (p->getX() - x < 90 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
                if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
                    p->takeDamage(); // player's health decreases
                    cout << "p->health--" << endl;
                }
                else if (p->getIsABall()) { // collision happened while player was a ball
                    if (p->getIsActive() && !p->getIsInvincible()) { // if active then he should not have been invincible to cause damage to enenmy
                        health--; // enenmy's health decreases
                        cout << "p->x " << p->getX() << endl;
                        cout << "x " << x << endl;
                    }
                    else if (!p->getIsActive()) { // if passive then he can cause damage just because he is a ball
                        health--; // enenmy's health decreases
                        cout << "p->x " << p->getX() << endl;
                        cout << "x " << x << endl;
                    }
                }
            }
        }
        else { // player is to the left of the crab
            if (x - p->getX() < 90 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
                if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
                    p->takeDamage(); // player's health decreases
                    cout << "p->health--" << endl;
                }
                else if (p->getIsABall()) { // collision happened while player was a ball
                    if (p->getIsActive() && !p->getIsInvincible()) { // if active then he should not have been invincible to cause damage to enenmy
                        health--; // enenmy's health decreases
                        cout << "p->x " << p->getX() << endl;
                        cout << "x " << x << endl;
                    }
                    else if (!p->getIsActive()) { // is a ball and not active
                        health--; // enenmy's health decreases
                        cout << "p->x " << p->getX() << endl;
                        cout << "x " << x << endl;
                    }
                }
            }
        }
    }

    void draw(RenderWindow& window, Camera& camera) override {
        // Draw the BeeBot
        if (health <= 0) {
            return; // Don't draw if the enemy is dead
        }

        // Calculate screen position
        float screenX = camera.worldToScreenX(x);
        float screenY = camera.worldToScreenY(y);

        sprite.setPosition(screenX, screenY);
        window.draw(sprite);

        // Draw all active projectiles
        for (int i = 0; i < projectileCount; i++) {
            if (projectiles[i] != nullptr && projectiles[i]->isActive()) {
                projectiles[i]->draw(window, camera);
            }
        }
    }

    ~CrabMeat() {
        // Clean up projectiles
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i] != nullptr) {
                delete projectiles[i];
                projectiles[i] = nullptr;
            }
        }
    }
};
