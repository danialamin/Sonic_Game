#pragma once
#include "Global_variables.h"
#include "Level.h"
#include "PlayerFactory.h"
#include "Camera.h"
#include "Menu.h"

class Game {
private:
    RenderWindow window;
    Event event;
    Level* level;
    Camera camera;
    Music lvlMus;
	int activePlayerIndex = 0; // 0 for sonic, 1 for tails, 2 for knuckles
	int passive1PlayerIndex = 0;
    int passive2PlayerIndex = 0; 
public:
    Game() : window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close), level(new Level()), camera(800, 600), volume(30), gameState(0), menu() {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        lvlMus.openFromFile("Data/labrynth.wav");
        lvlMus.setVolume(volume);
        lvlMus.play();
        lvlMus.setLoop(true);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            
            if (gameState == 0) {
                menu.draw(window);
                menu.menuInput();
                gameState = menu.getGameState();
            }
            else if(gameState == 1) {
                
                update();
                render();
            }
            
        }
    }

    // destructor
    ~Game() {
        delete level;
    }

private:
    void handleEvents() {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        
    }

    void update() {
        if (level->getActivePlayerIndex() != 0) {
            activePlayerIndex = level->getActivePlayerIndex() - 1 ;
            if (level->getActivePlayerIndex() == 1) {
                passive1PlayerIndex = 1;
				passive2PlayerIndex = 2;
			}
            else if (level->getActivePlayerIndex() == 2) {
                passive1PlayerIndex = 2;
				passive2PlayerIndex = 0;
            }
		}
		else {
			activePlayerIndex = 2;
			passive1PlayerIndex = 0;
			passive2PlayerIndex = 1;
		}
        
        // shares the coordinates of the active player with the passive players
        level->handleActivePlayerSwitching();
        level->activePlayerCoordinatesSharing();

        level->getSonic()->handleInput();
        level->getSonic()->checkCollisions(level);
        level->getSonic()->collectibleCollision(level);
        level->getSonic()->applyGravity(level);
        camera.update(level->getSonic()->getX(), level->getSonic()->getY());

        level->getTails()->handleInput();
        level->getTails()->checkCollisions(level);
        level->getTails()->collectibleCollision(level);
        level->getSonic()->checkInvincibility();
        level->getTails()->applyGravity(level);

        level->getKnuckles()->handleInput();
        level->getKnuckles()->checkCollisions(level);
        level->getSonic()->collectibleCollision(level);
        level->getSonic()->checkInvincibility();
        level->getKnuckles()->applyGravity(level);

        // put camera on the player who is active
        if (level->getSonic()->getIsActive() == 1) {
            camera.update(level->getSonic()->getX(), level->getSonic()->getY());
        } else if (level->getTails()->getIsActive() == 1) {
            camera.update(level->getTails()->getX(), level->getTails()->getY());
        }
        else {
            camera.update(level->getKnuckles()->getX(), level->getKnuckles()->getY());
        }

		// check if players are out of screen
		level->getSonic()->isPlayerOutOfScreen(camera);
		level->getTails()->isPlayerOutOfScreen(camera);
        level->getKnuckles()->isPlayerOutOfScreen(camera);

        level->getSonic()->isInvincibleUpdate();
        level->getTails()->isInvincibleUpdate();
        level->getKnuckles()->isInvincibleUpdate();

		// health sharing between playerz
        int activePlayerHealth = level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()->activePlayerHealthSharing();
		level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer()->setHealth(activePlayerHealth);
		level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer()->setHealth(activePlayerHealth);

        // ENEMIES
        // move
		level->getBatBrain()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getMotoBug()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getBeeBot()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need
		level->getCrabMeat()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need

        // enemy and player collision
        level->getBatBrain()->checkCollisionWithPlayer(level->getSonic());
        level->getBatBrain()->checkCollisionWithPlayer(level->getTails());
        level->getBatBrain()->checkCollisionWithPlayer(level->getKnuckles());

		level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

		level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
		level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
		level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

        // projectile and player collisions
		for (int i = 0; i < 20; i++) { // max 20 projectiles for crabmeat and beebot
            if (level->getBeeBot()->getProjectilesArray()[i] != nullptr && level->getBeeBot()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getBeeBot()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
            if (level->getCrabMeat()->getProjectilesArray()[i] != nullptr && level->getCrabMeat()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getCrabMeat()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
        }
    }

    void render() {
        window.clear();
        level->draw(window, camera);
        level->getSonic()->draw(window, camera);
        level->getTails()->draw(window, camera);
        level->getKnuckles()->draw(window, camera);
		level->getBatBrain()->draw(window, camera);
        level->getMotoBug()->draw(window, camera);
		level->getBeeBot()->draw(window, camera);
		level->getCrabMeat()->draw(window, camera);
        window.display();
    }
};
