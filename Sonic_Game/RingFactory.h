#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "CollectibleFactory.h"
#include "Collectible.h"
#include "Ring.h"

class RingFactory: public CollectibleFactory {
public:
	void createCollectible(Sprite ringSprite) override {
		collectible = new Ring(ringSprite);
	}
};