#pragma once
#include "Global_variables.h"
#include "Level.h"
#include "PlayerFactory.h"

class Game {
private:
    RenderWindow window;
    Event event;
    Level level;
    PlayerFactory player;
    Music lvlMus;
public:
    Game() : window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close) {
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
        player.handleInput();
        player.applyGravity(level);
    }

    void render() {
        window.clear();
        level.draw(window);
        player.draw(window);
        window.display();
    }
};
