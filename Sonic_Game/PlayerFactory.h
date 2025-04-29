#pragma once
#include "Global_variables.h"
#include "Level.h"

class PlayerFactory { // abstract class
private:
    float player_x, player_y;
    float velocityY;
    bool onGround;
    float gravity;
    float terminal_Velocity;
    Sprite sprite;
    Texture texture;
    int hit_box_factor_x, hit_box_factor_y;
    int Pwidth, Pheight;
    float offset_y;
    bool inAJump;
    float jumpForce;
public:
    PlayerFactory() {
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

        texture.loadFromFile("Data/0left_still.png");
        sprite.setTexture(texture);
        sprite.setScale(scale_x, scale_y);

        inAJump = false;
        jumpForce = -17.0f; // negative
    }

    void handleInput() {
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player_x += 4;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player_x -= 4;
        }
        
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

    void applyGravity(Level& level) {
        offset_y = player_y + velocityY;
        char bottom_left = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x) / cell_size);
        char bottom_right = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth) / cell_size);
        char bottom_mid = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size);

        // Check if player is touching ground
        if (bottom_left == 'w' || bottom_mid == 'w' || bottom_right == 'w') {
            onGround = true;
            velocityY = 0;
            inAJump = false;  // Reset jump state when landing
        }
        else {
            onGround = false;
            player_y = offset_y;
            velocityY += gravity;
            if (velocityY > terminal_Velocity) velocityY = terminal_Velocity;
        }
    }


    void draw(RenderWindow& window) {
        sprite.setPosition(player_x, player_y);
        window.draw(sprite);
    }
};

//void jump(Level& level) {
//    char bottom_left = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x) / cell_size);
//    char bottom_right = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth) / cell_size);
//    char bottom_mid = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size);
//
//
//    if (Keyboard::isKeyPressed(Keyboard::Up) && (bottom_left == 'w' || bottom_right == 'w' || bottom_mid == 'w')) {
//        inAJump = true;
//    }
//
//    jumpClockTime = static_cast<float>(jumpClock.getElapsedTime().asSeconds());
//
//    if (inAJump) {
//        player_y -= 12;
//    }
//
//    if (jumpClockTime > 0.4) {
//        inAJump = false;
//    }
//
//    if (!inAJump) {
//        jumpClock.restart();
//    }
//}
