#pragma once
#include <iostream>
#include "Global_variables.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

using namespace std;
using namespace sf;

class BeeBot : public Enemy {
private:
    bool yDirection;

    static const int MAX_PROJECTILES = 20; // after 20 the projectiles will be replaced
    Projectile* projectiles[MAX_PROJECTILES];
    int projectileCount;

public:
    BeeBot(float x, float y, float x_limit[2], float y_limit[2]) : Enemy(x, y, 5, "Data/beebot_right_39x29.png", "Data/beebot_left_39x29.png", x_limit, y_limit) {
        projectileCount = 0;
        // Initialize all projectiles to nullptr
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            projectiles[i] = nullptr;
        }
		sprite.setScale(1.3, 1.5); 
    }

    ~BeeBot() {
        // Clean up projectiles
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i] != nullptr) {
                delete projectiles[i];
                projectiles[i] = nullptr;
            }
        }
    }

    // getters
    Projectile** getProjectilesArray() override {
        return projectiles;
    }

    // Add projectile to array
    void fireProjectile(float dirX, float dirY) {
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i] == nullptr || !projectiles[i]->isActive()) { // Find an empty slot in the array
                if (projectiles[i] != nullptr) { // If slot is occupied but inactive, delete the old projectile
                    delete projectiles[i];
                }

                // Create new projectile
                projectiles[i] = new Projectile(x, y, dirX, dirY, 5.0f, "Data/projectile.png");

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

    void move(Player* p) {
        // Define movement speed
        float moveSpeed = 2.0f;

        // Define waypoints for the zig-zag pattern
        const int numWaypoints = 8;
        float waypointsX[numWaypoints] = {
            x_limit[0], x_limit[1], x_limit[0], x_limit[1],
            x_limit[0], x_limit[1], x_limit[0], x_limit[0]
        };

        float waypointsY[numWaypoints] = {
            y_limit[0], y_limit[0] + 80, y_limit[0] + 160, y_limit[1],
            y_limit[0] + 160, y_limit[0] + 80, y_limit[0], y_limit[0]
        };

        // Static variables to keep track of current waypoint and direction between function calls
        static int currentWaypoint = 0;
        static bool initialized = false;

        // Initialize position on first call
        if (!initialized) {
            x = waypointsX[0];
            y = waypointsY[0];
            yDirection = true; // Start moving down
            initialized = true;
        }

        // Calculate direction to the current waypoint
        float currentX = x;
        float currentY = y;
        float targetX = waypointsX[currentWaypoint];
        float targetY = waypointsY[currentWaypoint];
        float directionX = targetX - currentX;
        float directionY = targetY - currentY;

        // Calculate distance to the waypoint
        float distance = sqrt(directionX * directionX + directionY * directionY);

        // If we've reached the waypoint (or very close to it)
        if (distance < moveSpeed) {
            // Fire projectile based on current position
            if (currentWaypoint == 0) {  // (x_limit[0], y_limit[0])
                // Fire down-left
                if (health>0)
                    fireProjectile(-1, 1);
                this->direction = -1; // Update sprite direction
            }
            else if (currentWaypoint == 1) {  // (x_limit[1], y_limit[0]+80)
                // Fire down-right
                if (health > 0)
                    fireProjectile(1, 1);
                this->direction = 1; // Update sprite direction
            }
            else if (currentWaypoint == 2) {  // (x_limit[0], y_limit[0]+160)
                // Fire down-left
                if (health > 0)
                    fireProjectile(-1, 1);
                this->direction = -1; // Update sprite direction
            }
            else if (currentWaypoint == 3) {  // (x_limit[1], y_limit[1])
                // Fire down-right
                if (health > 0)
                    fireProjectile(1, 1);
                this->direction = 1; // Update sprite direction
            }

            // Move to next waypoint
            currentWaypoint = (currentWaypoint + 1) % (numWaypoints - 1);

            // If we've completed a full cycle, reset to start the pattern again
            if (currentWaypoint == 0) {
                yDirection = true; // Start moving down again
            }

            // Update direction based on which part of the cycle we're in
            if (currentWaypoint == 4) {
                yDirection = false; // Start moving up
            }
        }
        else {
            // Normalize the direction vector
            directionX /= distance;
            directionY /= distance;

            // Move towards the current waypoint
            x += directionX * moveSpeed;
            y += directionY * moveSpeed;
        }

        // Update all active projectiles to move with the bee
        for (int i = 0; i < projectileCount; i++) {
            if (projectiles[i] != nullptr && projectiles[i]->isActive()) {
                projectiles[i]->update();
            }
        }
    }

    void checkCollisionWithPlayer(Player* p) override {
        if (health>0) // if enemy is not dead
        if (p->getX() - x > 0) { // player is to the right of the bee
            if (p->getX() - x < 46 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
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
        else {
            if (x - p->getX() < 46 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
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

        // Set sprite position to screen coordinates
        sprite.setPosition(screenX, screenY);
        if (direction == 1) {
            sprite.setTexture(textureRight);
        }
        else {
            sprite.setTexture(textureLeft);
        }
        window.draw(sprite);

        // Draw all active projectiles
        for (int i = 0; i < projectileCount; i++) {
            if (projectiles[i] != nullptr && projectiles[i]->isActive()) {
                projectiles[i]->draw(window, camera);
            }
        }
    }
};