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

class CollectibleFactory {
protected:
	Collectible* collectible;
public:
	virtual void createCollectible(Sprite) = 0;
	Collectible* getCollectible() {
		return collectible;
	}
	virtual ~CollectibleFactory() {}
};