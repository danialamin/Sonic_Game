#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Collectible.h"

using namespace std;
using namespace sf;

class HealthPickup : public Collectible {
public:
	HealthPickup(Sprite sprite) : Collectible(sprite) {}

    void draw(RenderWindow& window, float screenX, float screenY) override {
        sprite.setPosition(screenX, screenY);
        window.draw(sprite);
    }
};