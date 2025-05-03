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
    bool runningRight;       // Track running direction
    bool runningLeft;        // Track running direction
    Clock runClock;      // Clock to track acceleration time
    float accelerationTime;// For how long the player has been accelerating
    bool wasRightKeyHeld;         // Track if the right key was held previously
    bool wasLeftKeyHeld;         // Track if the left key was held previously
    bool isMoving;   // Track if player is moving
    bool collisionWithWall; // checks if there's a wall in front of the player
    int direction; // direction is 1 if player facing right and -1 for left
    bool onGround;
    float gravity;
    float terminal_Velocity;
    Sprite sprite;
    Texture textureRight;
    Texture textureLeft;
    int hit_box_factor_x, hit_box_factor_y;
    int Pwidth, Pheight;
    float offset_y;
    bool inAJump; // checks if player is in air or groun
    float jumpForce; // the starting up velocity when up key is presses
public:
    Player(string textureRightPath, string textureLeftPath, int maxSpeedX_arg) { // attributes whose values are different per child, will be passed as parameter
        maxSpeedX = maxSpeedX_arg;
        velocityX = 0;
        accelerationX = 0;
        minSpeedX = 2.0f;
        accelerationTime = 0.0f;
        runningRight = false;
        runningLeft = false;
        direction = 1;
        collisionWithWall = false;
        isMoving = false;

        player_x = 100;
        player_y = 100;
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
        sprite.setTexture(textureRight);
        sprite.setScale(scale_x, scale_y);
        
        inAJump = false;
        jumpForce = -20.0f; // negative is up
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

    // manageRun function applies acceleration, makes the player run if right/left keys are pressed
    void manageRun(bool isMoving, int direction) {
        // Handle running with acceleration
        if (isMoving && !collisionWithWall) {
            if (!wasRightKeyHeld && direction == 1) { // if player was previously moving left and now want to move right so start acceleration from zero
                accelerationTime = 0.0f;
                runClock.restart();
                wasRightKeyHeld = true;
                wasLeftKeyHeld = false;
                sprite.setTexture(textureRight);
            }
            else if (!wasLeftKeyHeld && direction == -1) { // if player was previously moving right and now want to move left so start acceleration from zero
                accelerationTime = 0.0f;
                runClock.restart();
                wasLeftKeyHeld = true;
                wasRightKeyHeld = false;
                sprite.setTexture(textureLeft);
            }

            accelerationTime = runClock.getElapsedTime().asSeconds();

            // Calculate the current speed based on acceleration time
            double currentSpeed = accelerationTime * accelerationTime; // currentSpeed is a quadratic curve: y=x^2

            // Set velocity based on direction
            if (currentSpeed>=maxSpeedX) {
                velocityX = maxSpeedX * direction;
            }
            else {
                velocityX = currentSpeed * direction + (minSpeedX * direction);
            }

            // Apply velocity to position
            player_x += velocityX;
        }
        else {
            // No movement keys pressed, reset acceleration
            accelerationTime = 0.0f;
            velocityX = 0.0f;
            wasRightKeyHeld = false;
            wasLeftKeyHeld = false;
            runClock.restart();
        }
    }

    void checkCollisions(Level* level);

    void handleInput() {
        // Check if movement keys are pressed
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            isMoving = true;
            direction = 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            isMoving = true;
            direction = -1;
        }
        else {
            isMoving = false;
        }


        manageRun(isMoving, direction);

        // call jump() if up key/space presses
        if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) {
            jump();
        }
    }

    void jump() {
        // Only allow jumping if the player is on the ground
        if (onGround && !inAJump) {
            velocityY = jumpForce;
            onGround = false;
            inAJump = true;
        }
    }

    void applyGravity(Level* level);


    void draw(RenderWindow& window, Camera& camera) {
        // Calculate screen position
        float screenX = camera.worldToScreenX(player_x);
        float screenY = camera.worldToScreenY(player_y);

        // Set sprite position to screen coordinates
        sprite.setPosition(screenX, screenY);
        window.draw(sprite);
    }

    // destructor needs to be virtual so that the children destructors get called before
    virtual ~Player() {}
};
