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

public:
    Camera(float width, float height) {
        offsetX = 0.0f;
        offsetY = 0.0f;
        screenWidth = width;
        screenHeight = height;
    }

    void update(float playerX, float playerY) {
        // Calculate the camera position to center player
        offsetX = playerX - (screenWidth / 2);
        offsetY = playerY - (screenHeight / 2);

        // Prevent camera from showing areas outside the level boundaries
        if (offsetX < 0) offsetX = 0;
        if (offsetY < 0) offsetY = 0;
        // Optional: Add max bounds if needed
        // if (offsetX > maxLevelWidth - screenWidth) offsetX = maxLevelWidth - screenWidth;
        // if (offsetY > maxLevelHeight - screenHeight) offsetY = maxLevelHeight - screenHeight;
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