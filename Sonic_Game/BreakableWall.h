#pragma once
#include "Global_variables.h"
#include "Obstacle.h"

class BreakableWall : public Obstacle {
    Sprite sprite;
public:
    BreakableWall(Sprite s) { sprite = s; }
    void draw(RenderWindow& window, float screenX, float screenY) override {
        sprite.setPosition(screenX, screenY);
        window.draw(sprite);
    }
};