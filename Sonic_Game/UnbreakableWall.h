#pragma once
#include "Global_variables.h"
#include "Obstacle.h"

class UnbreakableWall : public Obstacle {
    Sprite sprite;
public:
    UnbreakableWall(Sprite s) { sprite = s; }
    void draw(RenderWindow& window, float screenX, float screenY) override {
        sprite.setPosition(screenX, screenY);
        window.draw(sprite);
    }
};