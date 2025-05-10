    #pragma once
    #include <iostream>
    #include "Global_variables.h"

    using namespace std;
    using namespace sf;

    class Projectile {
    private:
        float x, y;
        float width, height;
        float speedX, speedY;
        Sprite sprite;
        Texture texture;
        bool active; // collision with player and movement will only be when projectile is acitve
	    bool applyGravity; // if true then projectile will be affected by gravity, applicable in the case for crabmeat's projectiles
        int gravity;
        int terminalVelocity;

    public:
        // Constructor
        Projectile(float startX, float startY, float dirX, float dirY, float speed, string texturePath, bool applyGravity = 0) {
            x = startX;
            y = startY;
            this->applyGravity = applyGravity;
            this->gravity = 1;
            this->terminalVelocity = 20;

            // Normalize direction vector
            float length = sqrt(dirX * dirX + dirY * dirY);
            if (length != 0) {
                dirX /= length;
                dirY /= length;
            }

            // Set velocity
            speedX = dirX * speed;
            if (applyGravity) {
				speedY = dirY * speed - 20; // initial speedY is negative to go up
            }
            else {
                speedY = dirY * speed;
            }

            // Load texture
            texture.loadFromFile(texturePath);
            sprite.setTexture(texture);

            // Set dimensions based on texture size
            width = texture.getSize().x;
            height = texture.getSize().y;

            active = true;
        }

        // Update projectile position
        void update() {
            if (active) {
                x += speedX;

			    if (applyGravity) { // Apply gravity
				    speedY += gravity;
                    if (speedY >= terminalVelocity) {
                        speedY = terminalVelocity;
                    }
			    }

                y += speedY;
            }
        }

        // Draw projectile
        void draw(RenderWindow& window, Camera& camera) {
            if (active) {
                // Calculate screen position
                float screenX = camera.worldToScreenX(x);
                float screenY = camera.worldToScreenY(y);

                // Set sprite position to screen coordinates
                sprite.setPosition(screenX, screenY);
                window.draw(sprite);
            }
        }

        // Check if projectile is active
        bool isActive() {
            return active;
        }

        // Deactivate projectile
        void deactivate() {
            active = false;
        }

        // Get position and dimensions for collision detection
        float getX() { return x; }
        float getY() { return y; }
        float getWidth() { return width; }
        float getHeight() { return height; }

        // check collision of projectile with player
        void checkCollision(Player* p) {
            if (p->getX() - x > 0) { // if player is on the right of projectile
                if (p->getX() - x < 36 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
                    if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
                        p->takeDamage(); // player's health decreases
					    this->deactivate(); // deactivate projectile    
                        cout << "p->health--" << endl;
                    }
                }
            }
            else { // if player is on the left of projectile
                if (x - p->getX() < 36 && (p->getY() >= y ? (false) : (y - p->getY() < 95 ? true : false))) {
                    if (!p->getIsABall() && !p->getIsInvincible() && p->getIsActive()) { // collision happened while player was not a ball and not invincible
                        p->takeDamage(); // player's health decreases
                        this->deactivate(); // deactivate projectile    
                        cout << "p->health--" << endl;
                    }
                }
            }

            // deactivate projectile if it goes out of screen
            if (x < -100 || x > 14000 || y < -100 || y > 1500) {
                active = false;
            }
        }
    };