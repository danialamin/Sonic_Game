#include "Level.h"
#include "Tails.h"

void Tails::applyGravity(Level* level) {
    spaceOrUpKeyPressClockTime = spaceOrUpKeyPressClock.getElapsedTime().asSeconds(); // writing it here because applyGravity is being called infinitely
	flyingClockTime = flyingClock.getElapsedTime().asSeconds();
    if (!isFlying) { // flying clock should remain zero unless flying
        flyingClock.restart();
    }
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
        isFlying = false;
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
        if (isFlying) { // less gravity when flying
            velocityY += 0.3;
        }
        else {
            velocityY += gravity;
        }

        if (velocityY > terminal_Velocity) {
            velocityY = terminal_Velocity;
        }

        if (inAJump) {
            isABall = true;
            isFlying = false;
        }

		player_y += velocityY;
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