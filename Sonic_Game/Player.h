#pragma once
#include "Global_variables.h"
#include "Camera.h"

class Level; // forward declaration to avoid circulation error

class Player { // abstract class
protected:
    float player_x, player_y; // world positions
    float velocityY;
    float velocityX;         // Added for horizontal movement
    float minSpeedX;         // Starting speed
    float maxSpeedX;         // Maximum running speed
    float accelerationX;     // Acceleration rate
    bool isInvincible; //if the player is invincible
    Clock runClock;      // Clock to track acceleration time
    Clock invincibleClock; //clock for howlong a player is invincible
	float invincibleClockTime; // how long the player has been invincible
    float accelerationTime;// For how long the player has been accelerating
    Clock decelerationClock; // Clock to track deceleration time
    float decelerationTime;  // For how long the player has been decelerating
	float decelerationTimeLimit; // Maximum time for deceleration
    float startDecelerationSpeed; // Speed at which deceleration began
    bool isDecelerating;     // Track if player is decelerating
    int decelerationDirection; // Direction during deceleration (1 or -1)
    bool wasRightKeyHeld;         // Track if the right key was held previously
    bool wasLeftKeyHeld;         // Track if the left key was held previously
    bool isHorizontalKeyPressed;   // TRACK IF RIGHT OR LEFT KEY IS PRESSED
    bool collisionWithWallHorizontally; // checks if there's a wall in front of the player
	bool collisionWithWallAbove; // checks if there's a wall above the player
    int direction; // direction is 1 if player facing right and -1 for left
    bool onGround;
    float gravity;
    float terminal_Velocity;
    int health; 
    Sprite sprite;
    Texture textureRight;
    Texture textureLeft;
    int hit_box_factor_x, hit_box_factor_y;
    int Pwidth, Pheight;
    float offset_y;
    bool inAJump; // checks if player is in air or groun
    float jumpForce; // the starting up velocity when up key is presses
    bool isActive; // true if player is active, false if passive
    bool isPassive1; // true if player is in the middle of the three players
    bool isPassive2; // true if player is behind two players
	int* activePlayerCoordinates; // [0] = x, [1] = y, [2] = direction, [3] = maxSpeedX
	bool isABall; // tracks if player is in ball form or not
    Texture ballTextureRight;
    Texture ballTextureLeft;
    bool isColliding;
public:
    Player(string textureRightPath, string textureLeftPath, int maxSpeedX_arg, string ballTextureRight_arg, string ballTextureLeft_arg, int activeOrPassive) { // attributes whose values are different per child, will be passed as parameter
		activePlayerCoordinates = new int[4]; // [0] = x, [1] = y, [2] = direction, [3] = maxSpeedX

        maxSpeedX = maxSpeedX_arg;
        velocityX = 0;
        accelerationX = 0;
        minSpeedX = 2.5f;
        accelerationTime = 0.0f;
        decelerationTime = 0.0f;
        startDecelerationSpeed = 0.0f;
        isDecelerating = false;
        direction = 1;
        decelerationDirection = 1;
        collisionWithWallHorizontally = false;
        isHorizontalKeyPressed = false;

        if (activeOrPassive==1) {
            player_x = 100;
            player_y = 0;
        }
        else if (activeOrPassive==2) {
            player_x = 60;
            player_y = 0;
		}
		else if (activeOrPassive == 3) {
			player_x = 20;
			player_y = 0;
		}
        velocityY = 0;
        onGround = false;
        gravity = 1;
        terminal_Velocity = 20;

        float scale_x = 2.5, scale_y = 2.5;
        int raw_img_x = 24, raw_img_y = 35;
        Pwidth = raw_img_x * scale_x;
        Pheight = raw_img_y * scale_y;
        hit_box_factor_x = 8 * scale_x;
        hit_box_factor_y = 5 * scale_y;
        float offset_y = player_y;
        
        textureRight.loadFromFile(textureRightPath);
        textureLeft.loadFromFile(textureLeftPath);
        sprite.setScale(scale_x, scale_y);

        isABall = false;
		ballTextureRight.loadFromFile(ballTextureRight_arg);
		ballTextureLeft.loadFromFile(ballTextureLeft_arg);
        
        inAJump = false;
        jumpForce = -17.0f; // negative is up
		isInvincible = false; 
        invincibleClockTime = 0;

        health = 3;
    }

    // getters
    float getX() {
        return player_x;
    }

    float getY() {
        return player_y;
    }

    bool getJump() {
        return inAJump;
    }
    bool getHorizontalColl() { return collisionWithWallHorizontally; }

    bool getIsABall() {
        return isABall;
    }

	int getHealth() {
		return health;
	}

    void takeDamage() { //when player takes damage from enemies
        if (!isInvincible) {
            health--;
			isInvincible = true; // make player invincible for 1 seconds
            invincibleClock.restart();
          
        }
    }

	int activePlayerHealthSharing() { // this function is called in the main loop and gives the health of the active player to the passive players
        return health;
	}

    bool getIsActive() {
        return isActive;
    }

    bool getIsPassive1() {
        return isPassive1;
    }

    bool getIsPassive2() {
		return isPassive2;
    }

	int getDirection() {
		return direction;
	}

	float getMaxSpeedX() {
		return maxSpeedX;
	}

	float getCurrentSpeedX() {
		return velocityX;
	}

	bool getIsInvincible() {
		return isInvincible;
	}

    // setters
    void setIsActive(bool arg) {
        isActive = arg;
    }

	void setIsPassive1(bool arg) {
		isPassive1 = arg;
    }

	void setIsPassive2(bool arg) {
		isPassive2 = arg;
	}

    
    void collectibleCollision(Level* level);


	void setActivePlayerCoordinates(int x_arg, int y_arg, int direction_arg, int maxSpeedX_arg) {
		activePlayerCoordinates[0] = x_arg;
		activePlayerCoordinates[1] = y_arg;
		activePlayerCoordinates[2] = direction_arg;
        activePlayerCoordinates[3] = maxSpeedX_arg;
	}

	void setHealth(int arg) {
		health = arg;
	}

	void isInvincibleUpdate() { // this function updates the value of isInvincible based on the invicibleClockTime
        invincibleClockTime = invincibleClock.getElapsedTime().asSeconds();
        if (invincibleClockTime < 1) {
            isInvincible = true;
        }
        else {
            isInvincible = false;
        }

		cout << "healhth: " << health << endl;
    }

    // manageRun function applies acceleration, makes the player run if right/left keys are pressed
    void manageRun(bool isHorizontalKeyPressed, int direction) {
        if (collisionWithWallHorizontally) { // if player is colliding with wall then stop moving
            velocityX = 0;
            isHorizontalKeyPressed = false;
            isDecelerating = false;
            accelerationTime = 0.0f;
            runClock.restart();
            return; // EXIT THE FUNCTION
        }

        if (isHorizontalKeyPressed) {
            isDecelerating = false; // Reset deceleration state when starting to move

            if (!wasRightKeyHeld && direction == 1) { // if player was previously moving left and now want to move right so start acceleration from zero
                accelerationTime = 0.0f;
                runClock.restart();
                wasRightKeyHeld = true;
                wasLeftKeyHeld = false;
            }
            else if (!wasLeftKeyHeld && direction == -1) { // if player was previously moving right and now want to move left so start acceleration from zero
                accelerationTime = 0.0f;
                runClock.restart();
                wasLeftKeyHeld = true;
                wasRightKeyHeld = false;
            }

            accelerationTime = runClock.getElapsedTime().asSeconds();

            // Calculate the current speed based on acceleration time
            double currentSpeed = accelerationTime * accelerationTime; // currentSpeed is a quadratic curve: y=x^2

            // Set the velocity
            if (isActive) { // if active player then maximum speed it can go is its own maxSpeedX attribute
                if (currentSpeed >= maxSpeedX) {
                    velocityX = maxSpeedX * direction;
                }
                else {
                    velocityX = currentSpeed * direction + (minSpeedX * direction);
                }
            }
            else { // if passive player then maximum speed it can go is the active player's maxSpeedX attribute
                if (currentSpeed >= activePlayerCoordinates[3]) {
                    velocityX = activePlayerCoordinates[3] * direction;
                }
                else {
                    velocityX = currentSpeed * direction + (minSpeedX * direction);
                }
            }

            // Apply velocity to position
            if (isPassive1 && direction == 1 && player_x < activePlayerCoordinates[0] - 70) {
                player_x += velocityX;
            }
            else if (isPassive1 && direction == -1 && player_x > activePlayerCoordinates[0] + 70) {
                player_x += velocityX;
            }
            else if (isPassive2 && direction == 1 && player_x < activePlayerCoordinates[0] - 140) {
                player_x += velocityX;
            }
            else if (isPassive2 && direction == -1 && player_x > activePlayerCoordinates[0] + 140) {
                player_x += velocityX;
            }
            else if (isActive) { // if active player then move normally
                player_x += velocityX;
            }
        }
        else { // right or left key not pressed
            if (!isDecelerating && velocityX != 0) { // This is run only ONCE when the player stops moving
                isDecelerating = true;
                decelerationClock.restart();
                decelerationTime = 0.0f;

                // Store the starting speed for deceleration
                if (velocityX > 0) {
                    startDecelerationSpeed = velocityX;
                    decelerationDirection = 1;
                }
                else {
                    startDecelerationSpeed = -velocityX;
                    decelerationDirection = -1;
                }

                decelerationTimeLimit = velocityX / 4; // decelerationTimeLimit is dependent on the speed at which the player started to decelerate
                if (decelerationTimeLimit < 0) decelerationTimeLimit *= -1; // make it positive
            }

            // Apply deceleration if needed
            if (isDecelerating) {
                decelerationTime = decelerationClock.getElapsedTime().asSeconds();

                if (decelerationTime >= decelerationTimeLimit) { // If we've finished decelerating
                    velocityX = 0.0f;
                    isDecelerating = false;
                }
                else { // if we are still decelerating
                    float decelerationFactor = 1.0f - (decelerationTime / decelerationTimeLimit); // deceleration factor: 1.0 at start, 0.0 at end

                    float currentSpeedDuringDeceleration = startDecelerationSpeed * decelerationFactor; // calculating current speed during deceleration using decelerationFactor

                    // Apply direction
                    velocityX = currentSpeedDuringDeceleration * decelerationDirection;
                }

				// only move passive players if they are behind active player
                if (isPassive1 && direction == 1 && player_x < activePlayerCoordinates[0] - 70) {
                    player_x += velocityX;
                }
                else if (isPassive1 && direction == -1 && player_x > activePlayerCoordinates[0] + 70) {
                    player_x += velocityX;
                }
                else if (isPassive2 && direction == 1 && player_x < activePlayerCoordinates[0] - 140) {
                    player_x += velocityX;
                }
                else if (isPassive2 && direction == -1 && player_x > activePlayerCoordinates[0] + 140) {
                    player_x += velocityX;
                }
                else if (isActive) { // if active player then move normally
                    player_x += velocityX;
                }
            }
        }

        // Reset acceleration parameters if not moving
        if (!isHorizontalKeyPressed && !isDecelerating) {
            accelerationTime = 0.0f;
            velocityX = 0.0f;
            wasRightKeyHeld = false;
            wasLeftKeyHeld = false;
            runClock.restart();

			// move passive players behind the active player
            if (isPassive1 && player_x<activePlayerCoordinates[0]-70 && direction==1) {
                player_x += 5;
			}
			else if (isPassive1 && player_x > activePlayerCoordinates[0] + 70 && direction == -1) {
				player_x -= 5;
			}
			else if (isPassive2 && player_x < activePlayerCoordinates[0] - 140 && direction == 1) {
				player_x += 5;
			}
			else if (isPassive2 && player_x > activePlayerCoordinates[0] + 140 && direction == -1) {
				player_x -= 5;
			}
        }
    }
    
    

    virtual void checkCollisions(Level * level);

    virtual void handleInput() {
        // call jump() if up Space/Up presses
        if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) {
            jump();

        }

        //

        bool keyRightPressed = Keyboard::isKeyPressed(Keyboard::Right);
        bool keyLeftPressed = Keyboard::isKeyPressed(Keyboard::Left);
        bool keyDownPressed = Keyboard::isKeyPressed(Keyboard::Down);
        // Handle ball form transition
        if (keyDownPressed && velocityX != 0) {
            isABall = true;
        }
        // Reset ball form when velocity becomes zero and was previously in ball form
        else if (isABall && velocityX == 0) {
            isABall = false;
        }

        // Check if movement keys are pressed - but only allow movement if not in ball form and not ahead of active player
        if (keyRightPressed && (!isABall || isABall && inAJump)) {
            isHorizontalKeyPressed = true;
            direction = 1;
        }
        else if (keyLeftPressed && (!isABall || isABall && inAJump)) {
            isHorizontalKeyPressed = true;
            direction = -1;
        }
        else {
            isHorizontalKeyPressed = false;
        }

        // Check for instant stop when pressing opposite direction during deceleration
        if (isDecelerating) {
            if ((decelerationDirection == 1 && keyLeftPressed) || (decelerationDirection == -1 && keyRightPressed)) {
                // Instant stop
                velocityX = 0;
                isDecelerating = false;
            }
        }

        manageRun(isHorizontalKeyPressed, direction);
    }

    virtual void jump() { // jump for tails is different hence virtual
        // Only allow jumping if the player is on the ground
        if (onGround && !inAJump) {
            velocityY = jumpForce;
            onGround = false;
            inAJump = true;
        }
    }

    virtual void applyGravity(Level * level); // applyGravity for tails is different

    void isPlayerOutOfScreen(Camera& camera) {
        if (!isActive) { // only passive players can be left out of screen
            if (camera.worldToScreenX(player_x) < -200) { // if player left behind left edge
                if (isPassive1) {
                    player_x = activePlayerCoordinates[0] - 70;
                    player_y = activePlayerCoordinates[1] - 30;

                }
                else if (isPassive2) {
                    player_x = activePlayerCoordinates[0] - 140;
                    player_y = activePlayerCoordinates[1] - 30;
                }
			}
			else if (camera.worldToScreenX(player_x) > screen_x + 200) { // if player left behind right edge
                if (isPassive1) {
                    player_x = activePlayerCoordinates[0] + 70;
                    player_y = activePlayerCoordinates[1] - 30;
                }
                else if (isPassive2) {
                    player_x = activePlayerCoordinates[0] + 140;
                    player_y = activePlayerCoordinates[1] - 30;
                }
            }
        }
    }

    void draw(RenderWindow & window, Camera & camera) {
        // Calculate screen position
        float screenX = camera.worldToScreenX(player_x);
        float screenY = camera.worldToScreenY(player_y);

        // Set sprite position to screen coordinates
        sprite.setPosition(screenX, screenY);

        // Set the texture based on direction and ball form
        if (isABall) {
            if (direction == 1) {
                sprite.setTexture(ballTextureRight);
            }
            else {
                sprite.setTexture(ballTextureLeft);
            }
        }
        else {
            if (direction == 1) {
                sprite.setTexture(textureRight);
            }
            else {
                sprite.setTexture(textureLeft);
            }
        }

        window.draw(sprite);
    }

    // destructor needs to be virtual so that the children destructors get called before
    virtual ~Player() {
        delete activePlayerCoordinates;
    }
};

