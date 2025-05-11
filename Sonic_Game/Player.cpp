#include "Player.h"
#include "Level.h"

// making this class so i can include "Level.h" without facing the problem of circular dependecny, where Level.h includes Player and Player.h includes Level


void Player::applyGravity(Level* level) {
    // Store previous state for comparison
    bool wasInAJump = inAJump;

    // Calculate new position with velocity
    offset_y = player_y + velocityY;

    // Check if there's ground beneath the player
    int bottom_left_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_left_cell_x = (int)(player_x + hit_box_factor_x) / 64;

    int bottom_right_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_right_cell_x = (int)(player_x + hit_box_factor_x + Pwidth) / 64;

    int bottom_mid_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_mid_cell_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / 64;

    // Get the cell types
    char bottom_left = level->getCell(bottom_left_cell_y, bottom_left_cell_x);
    char bottom_right = level->getCell(bottom_right_cell_y, bottom_right_cell_x);
    char bottom_mid = level->getCell(bottom_mid_cell_y, bottom_mid_cell_x);


    // Check for ground collision - use a small threshold to fix floating-point issues
    bool groundCollision = (bottom_mid == 'w' || bottom_mid == 's' || bottom_mid == 'e' || bottom_mid == 'b' || bottom_mid == 'p');

    if (groundCollision) {
        // On ground - stop falling
        if ((bottom_mid == 's')) {
            takeDamage();
        }
        else if (bottom_mid == 'e' && isActive) {
            health = 0;
        }
        onGround = true;
        velocityY = 0;

		// Calculate the exact y-position to place the player on top of the ground cell. This fixes small floating-point issues which may cause the player to float or sink into the ground
        player_y = (bottom_left_cell_y * 64) - hit_box_factor_y - Pheight;

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

// checks collision with wall to the right, left and top
void Player::checkCollisions(Level* level) {
    // checking collision with wall to the right or left
    float offset_x = player_x + velocityX; // Calculate the offset position based on the current velocity

    if (direction==-1) { // if player is moving left
        // Get three points along the left side of the player's hitbox
        int left_x = (int)(offset_x + hit_box_factor_x) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

        char left_top = level->getCell(top_y, left_x);
        char left_mid = level->getCell(mid_y, left_x);
        char left_bottom = level->getCell(bottom_y, left_x);

        if ((left_top == 'w' || left_mid == 'w' || left_bottom == 'w') || (left_top == 'b' || left_mid == 'b' || left_bottom == 'b') || (left_top == 's' || left_mid == 's' || left_bottom == 's')) { // Collision detected
            collisionWithWallHorizontally = true;
        }
        else {
            collisionWithWallHorizontally = false;
        }
    }
    
    else if (direction==1) { // if player moving right
        // Get three points along the right side of the player's hitbox
        int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / 64;
        int top_y = (int)(player_y + hit_box_factor_y) / 64;
        int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
        int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

        char right_top = level->getCell(top_y, right_x);
        char right_mid = level->getCell(mid_y, right_x);
        char right_bottom = level->getCell(bottom_y, right_x);

        if ((right_top == 'w' || right_mid == 'w' || right_bottom == 'w') || (right_top == 'b' || right_mid == 'b' || right_bottom == 'b') || (right_top == 's' || right_mid== 's' || right_bottom == 's')) { // collision detected
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

void Player::collectibleCollision(Level* level) {
    // Calculate new position with velocity
    float offset_y = player_y + velocityY;
    float offset_x = player_x + velocityX;

    // Check if there's ground beneath the player
    int bottom_left_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_left_cell_x = (int)(player_x + hit_box_factor_x) / 64;

    int bottom_right_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_right_cell_x = (int)(player_x + hit_box_factor_x + Pwidth) / 64;

    int bottom_mid_cell_y = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
    int bottom_mid_cell_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / 64;

    // Get the cell types
    char bottom_left = level->getCell(bottom_left_cell_y, bottom_left_cell_x);
    char bottom_right = level->getCell(bottom_right_cell_y, bottom_right_cell_x);
    char bottom_mid = level->getCell(bottom_mid_cell_y, bottom_mid_cell_x);

    int left_x = (int)(offset_x + hit_box_factor_x) / 64;
    int top_y = (int)(player_y + hit_box_factor_y) / 64;
    int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / 64;
    int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;

    char left_top = level->getCell(top_y, left_x);
    char left_mid = level->getCell(mid_y, left_x);
    char left_bottom = level->getCell(bottom_y, left_x);

    int right_x = (int)(offset_x + hit_box_factor_x + Pwidth) / 64;
    //int top_y = (int)(player_y + hit_box_factor_y) / cell_size;
    //int mid_y = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
    //int bottom_y = (int)(player_y + hit_box_factor_y + Pheight - 1) / cell_size;

    char right_top = level->getCell(top_y, right_x);
    char right_mid = level->getCell(mid_y, right_x);
    char right_bottom = level->getCell(bottom_y, right_x);

    //int top_y = (int)(offset_y + hit_box_factor_y) / cell_size;
    //int left_x = (int)(player_x + hit_box_factor_x) / cell_size;
    int mid_x = (int)(player_x + hit_box_factor_x + Pwidth / 2) / 64;
    //int right_x = (int)(player_x + hit_box_factor_x + Pwidth - 1) / cell_size;
    // Check the cells at these positions
    char top_left = level->getCell(top_y, left_x);
    char top_mid = level->getCell(top_y, mid_x);
    char top_right = level->getCell(top_y, right_x);
    // ('r' || 'h' || 'x'
        
    if ((bottom_left == 'r')) {
        level->collectRing();
        level->setCell(' ', bottom_left_cell_y, bottom_left_cell_x);
    }
	if (bottom_mid == 'r') {
        level->collectRing();
		level->setCell(' ', bottom_mid_cell_y, bottom_mid_cell_x);
	}
    if (bottom_right == 'r') {
        level->collectRing();
		level->setCell(' ', bottom_right_cell_y, bottom_right_cell_x);
    }
    if (right_top == 'r') {
        level->collectRing();
        level->setCell(' ', top_y, right_x);
    }
	if (right_mid == 'r') {
        level->collectRing();
		level->setCell(' ', mid_y, right_x);
	}
    if (right_bottom == 'r') {
        level->collectRing();
        level->setCell(' ', bottom_y, right_x);
    }
    if (left_top == 'r') {
        level->collectRing();
        level->setCell(' ', top_y, left_x);
    }
    if (left_mid == 'r') {
        level->collectRing();
        level->setCell(' ', mid_y, left_x);
    }
	if (left_bottom == 'r') {
        level->collectRing();
		level->setCell(' ', bottom_y, left_x);
	}
    if (top_left == 'r') {
        level->collectRing();
        level->setCell(' ', top_y, left_x);
    }
	if (top_mid == 'r') {
        level->collectRing();
		level->setCell(' ', top_y, mid_x);
	}
	if (top_right == 'r') {
        level->collectRing();
		level->setCell(' ', top_y, right_x);
	}
    // healthpickup collision
    if (((bottom_left == 'h' || bottom_mid == 'h' || bottom_right == 'h') || (right_top == 'h' || right_mid == 'h' || right_bottom == 'h') || (left_top == 'h' || left_mid == 'h' || left_bottom == 'h') || (top_left == 'h' || top_mid == 'h' || top_right == 'h')) && isActive && health<3) {
        health++;
        if ((bottom_left == 'h')) {
            level->setCell(' ', bottom_left_cell_y, bottom_left_cell_x);
        }
        if (bottom_mid == 'h') {
            level->setCell(' ', bottom_mid_cell_y, bottom_mid_cell_x);
        }
        if (bottom_right == 'h') {
            level->setCell(' ', bottom_right_cell_y, bottom_right_cell_x);
        }
        if (right_top == 'h') {
            level->setCell(' ', top_y, right_x);
        }
        if (right_mid == 'h') {
            level->setCell(' ', mid_y, right_x);
        }
        if (right_bottom == 'h') {
            level->setCell(' ', bottom_y, right_x);
        }
        if (left_top == 'h') {
            level->setCell(' ', top_y, left_x);
        }
        if (left_mid == 'h') {
            level->setCell(' ', mid_y, left_x);
        }
        if (left_bottom == 'h') {
            level->setCell(' ', bottom_y, left_x);
        }
        if (top_left == 'h') {
            level->setCell(' ', top_y, left_x);
        }
        if (top_mid == 'h') {
            level->setCell(' ', top_y, mid_x);
        }
        if (top_right == 'h') {
            level->setCell(' ', top_y, right_x);
        }
    }

    // special boost collision
    if ((bottom_left == 'q')) {
        level->setCell(' ', bottom_left_cell_y, bottom_left_cell_x);
        activateSpecialAbility();
    }
    if (bottom_mid == 'q') {
        level->setCell(' ', bottom_mid_cell_y, bottom_mid_cell_x);
        activateSpecialAbility();
    }
    if (bottom_right == 'q') {
        level->setCell(' ', bottom_right_cell_y, bottom_right_cell_x);
        activateSpecialAbility();
    }
    if (right_top == 'q') {
        level->setCell(' ', top_y, right_x);
        activateSpecialAbility();
    }
    if (right_mid == 'q') {
        level->setCell(' ', mid_y, right_x);
        activateSpecialAbility();
    }
    if (right_bottom == 'q') {
        level->setCell(' ', bottom_y, right_x);
        activateSpecialAbility();
    }
    if (left_top == 'q') {
        level->setCell(' ', top_y, left_x);
        activateSpecialAbility();
    }
    if (left_mid == 'q') {
        level->setCell(' ', mid_y, left_x);
        activateSpecialAbility();
    }
    if (left_bottom == 'q') {
        level->setCell(' ', bottom_y, left_x);
        activateSpecialAbility();
    }
    if (top_left == 'q') {
        level->setCell(' ', top_y, left_x);
        activateSpecialAbility();
    }
    if (top_mid == 'q') {
        level->setCell(' ', top_y, mid_x);
        activateSpecialAbility();
    }
    if (top_right == 'q') {
        level->setCell(' ', top_y, right_x);
        activateSpecialAbility();
    }
}
