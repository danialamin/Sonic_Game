#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "CollectibleFactory.h"
#include "Collectible.h"
#include "SpecialBoost.h"

class SpecialBoostFactory : public CollectibleFactory {
public:
	void createCollectible(Sprite specialBoostSprite) override {
		collectible = new SpecialBoost(specialBoostSprite);
	}
};