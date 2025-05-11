#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "CollectibleFactory.h"
#include "Collectible.h"
#include "HealthPickup.h"

class HealthPickupFactory : public CollectibleFactory {
public:
	void createCollectible(Sprite healthPickupSprite) override {
		collectible = new HealthPickup(healthPickupSprite);
	}
};