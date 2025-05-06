#pragma once
#include "Global_variables.h"
#include "Level.h"
#include "PlayerFactory.h"
#include "Camera.h"

class Game {
private:
    RenderWindow window;
    Event event;
    Level* level;
    Camera camera;
    Music lvlMus;
public:
    Game() : window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close), level(new Level()), camera(800, 600) {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        lvlMus.openFromFile("Data/labrynth.ogg");
        lvlMus.setVolume(30);
        lvlMus.play();
        lvlMus.setLoop(true);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
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
        // shares the coordinates of the active player with the passive players
        level->handleActivePlayerSwitching();
        level->activePlayerCoordinatesSharing();

        level->getSonic()->handleInput();
        level->getSonic()->checkCollisions(level);
        level->getSonic()->applyGravity(level);
        level->getSonic()->checkInvincibility();
        camera.update(level->getSonic()->getX(), level->getSonic()->getY());

        level->getTails()->handleInput();
        level->getTails()->checkCollisions(level);
        level->getTails()->applyGravity(level);

        level->getKnuckles()->handleInput();
        level->getKnuckles()->checkCollisions(level);
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
    }

    void render() {
        window.clear();
        level->draw(window, camera);
        level->getSonic()->draw(window, camera);
        level->getTails()->draw(window, camera);
        level->getKnuckles()->draw(window, camera);
        window.display();
    }
};
