#pragma once
#include "Global_variables.h"
using namespace std;
using namespace sf;

class Camera {
private:
    float offsetX;
    float offsetY;
    float screenWidth;
    float screenHeight;
    float fixedY; // Added to store the fixed vertical position

public:
    Camera(float width, float height) {
        offsetX = 0.0f;
        offsetY = 0.0f;
        screenWidth = width;
        screenHeight = height;
        fixedY = 0.0f; // Initialize the fixed Y position
    }

    void update(float playerX, float playerY) {
        // Calculate the camera position, but only update X
        offsetX = playerX - (screenWidth / 2);

        // Set the Y offset only once (on first update)
        if (fixedY == 0.0f) {
            fixedY = playerY - (screenHeight / 2);
            offsetY = fixedY;
        }

        // Keep using the fixed Y value for camera position
        // offsetY remains unchanged after initial setup

        // Prevent camera from showing areas outside the level boundaries for X
        if (offsetX < 0) offsetX = 0;

        // Y boundary check still applies to the fixed position
        if (offsetY < 0) offsetY = 0;
    }

    float worldToScreenX(float worldX) {
        return worldX - offsetX;
    }

    float worldToScreenY(float worldY) {
        return worldY - offsetY;
    }

    float getOffsetX() const {
        return offsetX;
    }

    float getOffsetY() const {
        return offsetY;
    }
};