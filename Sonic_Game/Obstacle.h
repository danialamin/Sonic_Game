#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Obstacle {
public:
    virtual void draw(RenderWindow& window, float screenX, float screenY) = 0;
    virtual ~Obstacle() {}
};