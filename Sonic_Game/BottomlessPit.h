#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Obstacle.h"

class BottomlessPit : public Obstacle {
    Sprite sprite;
public:
    BottomlessPit(Sprite s) { sprite = s; }
    void draw(RenderWindow& window, float screenX, float screenY) override {
        sprite.setPosition(screenX, screenY);
        window.draw(sprite);
    }
};