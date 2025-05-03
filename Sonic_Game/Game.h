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
        level->getSonic()->handleInput();
        level->getSonic()->checkCollisions(level);
        level->getSonic()->applyGravity(level);
        level->getSonic()->checkInvincibility();
        camera.update(level->getSonic()->getX(), level->getSonic()->getY());
    }

    void render() {
        window.clear();
        level->draw(window, camera);
        level->getSonic()->draw(window, camera);
        window.display();
    }
};
