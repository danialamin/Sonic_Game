#include "Player.h"
#include "Level.h"

// making this class so i can include "Level.h" without facing the problem of circular dependecny, where Level.h includes Player and Player.h includes Level

void Player::applyGravity(Level* level) {
    offset_y = player_y + velocityY;
    char bottom_left = level->getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x) / cell_size);
    char bottom_right = level->getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth) / cell_size);
    char bottom_mid = level->getCell((int)(offset_y + hit_box_factor_y + Pheight) / cell_size, (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size);

    if (bottom_left == 'w' || bottom_mid == 'w' || bottom_right == 'w') {
        onGround = true;
        velocityY = 0;
        inAJump = false;
    }
    else {
        onGround = false;
        player_y = offset_y;
        velocityY += gravity;
        if (velocityY > terminal_Velocity) velocityY = terminal_Velocity;
    }
}

void Player::checkCollisions(Level* level) {
    // checking collision with wall to the right or left
    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction==-1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / cell_size;

        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

        char left_top = level->getCell(top_y, left_x);
        char left_mid = level->getCell(mid_y, left_x);
        char left_bottom = level->getCell(bottom_y, left_x);

        if (left_top == 'w' || left_mid == 'w' || left_bottom == 'w') { // Collision detected
            collisionWithWall = true;
            cout << "collision detected" << endl;
        }
        else {
            collisionWithWall = false;
        }
    }
    
    else if (direction==1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / cell_size;

        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

        if (right_top == 'w' || right_mid == 'w' || right_bottom == 'w') { // collision detected
            collisionWithWall = true;
            cout << "collision detected" << endl;
        }
        else {
            collisionWithWall = false;
        }
    }
}