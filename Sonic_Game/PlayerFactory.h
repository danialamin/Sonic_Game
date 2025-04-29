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

        texture.loadFromFile("Data/0left_still.png");
        sprite.setTexture(texture);
        sprite.setScale(scale_x, scale_y);
    }

    void handleInput() {
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player_x += 1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player_x -= 1;
        }
    }

    void applyGravity(Level& level) {
        float offset_y = player_y + velocityY;

        char bottom_left = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x) / cell_size);
        char bottom_right = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth) / cell_size);
        char bottom_mid = level.getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size);

        if (bottom_left == 'w' || bottom_mid == 'w' || bottom_right == 'w') {
            onGround = true;
        }
        else {
            player_y = offset_y;
            onGround = false;
        }

        if (!onGround) {
            velocityY += gravity;
            if (velocityY > terminal_Velocity) velocityY = terminal_Velocity;
        }
        else {
            velocityY = 0;
        }
    }

    void draw(RenderWindow& window) {
        sprite.setPosition(player_x, player_y);
        window.draw(sprite);
    }
};
