#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Obstacle {
public:
    virtual void draw(RenderWindow& window, float screenX, float screenY) = 0;
    virtual ~Obstacle() {}
};