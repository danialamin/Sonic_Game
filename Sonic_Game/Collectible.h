#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Collectible {
protected:
	Sprite sprite;

public:
	// constructor
	Collectible(Sprite s) {
		sprite = s;
	}

	virtual void draw(RenderWindow& window, float screenX, float screenY) = 0;

	// virtual destructor
	~Collectible() {}
};