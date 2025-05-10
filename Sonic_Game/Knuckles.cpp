#include "Player.h"
#include "Level.h"
#include "Knuckles.h"




void Knuckles::checkCollisions(Level* level) {
    // checking collision with wall to the right or left
    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction == -1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / cell_size;
        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

        char left_top = level->getCell(top_y, left_x);
        char left_mid = level->getCell(mid_y, left_x);
        char left_bottom = level->getCell(bottom_y, left_x);

        if ((left_top == 'b' || left_mid == 'b' || left_bottom == 'b') || (left_top == 'w' || left_mid == 'w' || left_bottom == 'w')) { // Collision detected
            if (isActive && (left_top == 'b' || left_mid == 'b' || left_bottom == 'b')) { Punch(level); }
            else {
                collisionWithWallHorizontally = true;
            }

        }
        else {
            collisionWithWallHorizontally = false;
        }
    }

    else if (direction == 1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / cell_size;
        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

        if ((right_top == 'w' || right_mid == 'w' || right_bottom == 'w') || (right_top == 'b' || right_mid == 'b' || right_bottom == 'b')) { // collision detected

            if (isActive && (right_top == 'b' || right_mid == 'b' || right_bottom == 'b')) { Punch(level); }
            else
                collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
        }
    }

}

void Knuckles::Punch(Level* level) {

    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction == -1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / cell_size;
        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;



        level->setCell('\0', top_y, left_x);
        level->setCell('\0', mid_y, left_x);
        level->setCell('\0', bottom_y, left_x);

    }

    else if (direction == 1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / cell_size;
        int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

        level->setCell('\0', top_y, right_x);
        level->setCell('\0', mid_y, right_x);
        level->setCell('\0', bottom_y, right_x);
    }
}