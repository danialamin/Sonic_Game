#include "Player.h"
#include "Level.h"

// making this class so i can include "Level.h" without facing the problem of circular dependecny, where Level.h includes Player and Player.h includes Level



int Player::health = 3;


void Player::applyGravity(Level* level) {
    // Store previous state for comparison
    bool wasInAJump = inAJump;

    // Calculate new position with velocity
    offset_y = player_y + velocityY;

    // Check if there's ground beneath the player
    int bottom_left_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int bottom_left_cell_x = (int)(player_x + hit_box_factor_x) / cell_size;

    int bottom_right_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int bottom_right_cell_x = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;

    int bottom_mid_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int bottom_mid_cell_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size;

    // Get the cell types
    char bottom_left = level->getCell(bottom_left_cell_y, bottom_left_cell_x);
    char bottom_right = level->getCell(bottom_right_cell_y, bottom_right_cell_x);
    char bottom_mid = level->getCell(bottom_mid_cell_y, bottom_mid_cell_x);


    // Check for ground collision - use a small threshold to fix floating-point issues
    bool groundCollision = ((bottom_left == 'w' || bottom_mid == 'w' || bottom_right == 'w') || (bottom_left == 's' || bottom_mid == 's' || bottom_right == 's')|| (bottom_left == 'e' || bottom_mid == 'e' || bottom_right == 'e'));

    if (groundCollision) {
        // On ground - stop falling
        if ((bottom_left == 's' || bottom_mid == 's' || bottom_right == 's')) {
            takeDamage();
        }
        else if (bottom_left == 'e' || bottom_mid == 'e' || bottom_right == 'e') {
            health = 0;
        }
        onGround = true;
        velocityY = 0;

		// Calculate the exact y-position to place the player on top of the ground cell. This fixes small floating-point issues which may cause the player to float or sink into the ground
        player_y = (bottom_left_cell_y * cell_size) - hit_box_factor_y - Pheight;

        // Reset jump state
        if (wasInAJump) {
            inAJump = false;
            isABall = false;
        }
    }
    else { // In air - apply gravity
        onGround = false;
		if (collisionWithWallAbove) { // if player is colliding with wall above then stop moving up
			velocityY = 0;
			collisionWithWallAbove = false;
		}
        player_y = offset_y;
        velocityY += gravity;

        if (velocityY > terminal_Velocity) {
            velocityY = terminal_Velocity;
        }

        if (inAJump) {
            isABall = true;
        }
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
            collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
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
            collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
        }
    }

	// checking collision with wall to the top
    //float offset_y = player_y + velocityY; // Calculate the offset position based on the current velocity
    //if (velocityY < 0) {
    //    // Get three points along the top side of the player's hitbox
    //    int top_y = (int)(offset_y + hit_box_factor_y) / cell_size;
    //    int left_x = (int)(player_x + hit_box_factor_x) / cell_size;
    //    int mid_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size;
    //    int right_x = (int)(player_x + hit_box_factor_x + Pwidth - 1) / cell_size;

    //    // Check the cells at these positions
    //    char top_left = level->getCell(top_y, left_x);
    //    char top_mid = level->getCell(top_y, mid_x);
    //    char top_right = level->getCell(top_y, right_x);

    //    // If any of these positions contains a wall, there's a collision
    //    if (top_left == 'w' || top_mid == 'w' || top_right == 'w') {
    //        collisionWithWallAbove = true;

    //        // Set the player's position to be just below the ceiling
    //        // This prevents the player from getting stuck in the ceiling
    //        player_y = ((top_y + 1) * cell_size) - hit_box_factor_y;
    //    }
    //    else {
    //        collisionWithWallAbove = false;
    //    }
    //}
    //else { // Not moving upward, so no ceiling collision possible
    //    collisionWithWallAbove = false;
    //}
}
