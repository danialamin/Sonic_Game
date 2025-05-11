#include "Player.h"
#include "Level.h"
#include "Knuckles.h"


// knuckles overriden checkCollisions function because it can punch
void Knuckles::checkCollisions(Level* level) {
    // checking collision with wall to the right or left
    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction == -1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

        char left_top = level->getCell(top_y, left_x);
        char left_mid = level->getCell(mid_y, left_x);
        char left_bottom = level->getCell(bottom_y, left_x);

        if (left_top == 'b' || left_mid == 'b' || left_bottom == 'b') {
			Punch(level);
        }
        if ((left_top == 'w' || left_mid == 'w' || left_bottom == 'w') || (left_top == 's' || left_mid == 's' || left_bottom == 's')) { // Collision detected
            collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
        }
    }

    else if (direction == 1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

		if (right_top == 'b' || right_mid == 'b' || right_bottom == 'b') {
			Punch(level);
		}
        if ((right_top == 'w' || right_mid == 'w' || right_bottom == 'w') || (right_top == 's' || right_mid == 's' || right_bottom == 's')) { // collision detected
            collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
        }
    }

    // checking collision with wall to the top
    float offset_y = player_y + velocityY; // Calculate the offset position based on the current velocity
    if (velocityY < 0) {
        // Get three points along the top side of the player's hitbox
        int top_y = (int)(offset_y + hit_box_factor_y) / 64;
        int left_x = (int)(player_x + hit_box_factor_x) / 64;
        int mid_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / 64;
        int right_x = (int)(player_x + hit_box_factor_x + Pwidth - 1) / 64;

        // Check the cells at these positions
        char top_left = level->getCell(top_y, left_x);
        char top_mid = level->getCell(top_y, mid_x);
        char top_right = level->getCell(top_y, right_x);

        // If any of these positions contains a wall, there's a collision
        if (top_left == 'w' || top_mid == 'w' || top_right == 'w' || top_left == 's' || top_mid == 's' || top_right == 's' || top_left == 'b' || top_mid == 'b' || top_right == 'b') {
            collisionWithWallAbove = true;

            // Set the player's position to be just below the ceiling
            // This prevents the player from getting stuck in the ceiling
            player_y = ((top_y + 1) * 64) - hit_box_factor_y;
        }
        else {
            collisionWithWallAbove = false;
        }
    }
    else { // Not moving upward, so no ceiling collision possible
        collisionWithWallAbove = false;
    }
}

void Knuckles::Punch(Level* level) {

    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction == -1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

		char left_top = level->getCell(top_y, left_x);
		char left_mid = level->getCell(mid_y, left_x);
		char left_bottom = level->getCell(bottom_y, left_x);
        
		if (left_top == 'b' || left_mid == 'b' || left_bottom == 'b') { // Collision detected with breakable wal
			level->setCell('\0', top_y, left_x);
			level->setCell('\0', mid_y, left_x);
			level->setCell('\0', bottom_y, left_x);
		}

    }

    else if (direction == 1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

		if (right_top == 'b' || right_mid == 'b' || right_bottom == 'b') { // Collision detected with breakable wall
			level->setCell('\0', top_y, right_x);
			level->setCell('\0', mid_y, right_x);
			level->setCell('\0', bottom_y, right_x);
		}
    }
}