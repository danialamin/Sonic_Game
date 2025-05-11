#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Level.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "PlayerFactory.h"
#include "Camera.h"
#include "Menu.h"



class Game {
private:
    RenderWindow window;
    Event event;
    Level* level;  // This will point to the current active level
    Camera camera;
    Music lvlMus;
    int activePlayerIndex = 0; // 0 for sonic, 1 for tails, 2 for knuckles
    int passive1PlayerIndex = 0;
    int passive2PlayerIndex = 0;
    int volume;
    int gameState; // 0 for menu, 1 for level 1, 2 for level 2, 3 for level 3
    int currentLevel; // 1, 2, or 3 to track which level is active
    Menu menu;

public:
    Game() : window(VideoMode(1200, 900), "Sonic the Hedgehog-OOP", Style::Close),
        level(nullptr), camera(800, 600), volume(30),
        gameState(0), currentLevel(1), menu() {

        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);

        // Initialize with level 1
        level = new Level1(0,0,200);

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

                // If we're transitioning from menu to game, make sure level is set
                if (gameState != 0 && level == nullptr) {
                    loadLevel(currentLevel);
                }
            }
            else {
                // Check for level completion and switch levels if needed
                checkLevelCompletion();
                update();
                render();
            }
        }
    }

    // destructor
    ~Game() {
        if (level != nullptr) {
            delete level;
        }
    }

private:
    void loadLevel(int levelNumber) {
        // Clean up previous level if it exists
        if (level != nullptr) {
            delete level;
            level = nullptr;
        }

        // Create the new level based on the level number
        switch (levelNumber) {
        case 1:
            level = new Level1(0,0,200);
            break;
        case 2:
            level = new Level2(1,0,250);
            break;
        case 3:
            level = new Level3(0,1,300);
            break;
        default:
            level = new Level1(0,0,250); // Default to level 1
            break;
        }

        currentLevel = levelNumber;
    }

    void checkLevelCompletion() {
        if (level == nullptr) return;
        // Check if the current level is completed
        if (level->isLevelComplete()) {
            // Move to the next level
            int nextLevel = currentLevel + 1;

            // If we've completed all levels, maybe go back to the menu or show a win screen
            if (nextLevel > 3) {
                gameState = 0; // Go back to menu
                // Or you could implement a win state: gameState = 4; // Win state
            }
            else {
                loadLevel(nextLevel);
            }
        }
        if (level->levelFailed() == 1) { // if failed then restart level
            loadLevel(currentLevel);
        }
    }

    void handleEvents() {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // For testing: Allow switching levels with number keys
        if (Keyboard::isKeyPressed(Keyboard::Num1) && currentLevel != 1)
            loadLevel(1);
        else if (Keyboard::isKeyPressed(Keyboard::Num2) && currentLevel != 2)
            loadLevel(2);
        else if (Keyboard::isKeyPressed(Keyboard::Num3) && currentLevel != 3)
            loadLevel(3);
    }

    void update() {
        if (level == nullptr) return;

        if (level->getActivePlayerIndex() != 0) {
            activePlayerIndex = level->getActivePlayerIndex() - 1;
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
        level->getTails()->applyGravity(level);

        level->getKnuckles()->handleInput();
        level->getKnuckles()->checkCollisions(level);
        level->getKnuckles()->collectibleCollision(level);
        level->getKnuckles()->applyGravity(level);

        // put camera on the player who is active
        if (level->getSonic()->getIsActive() == 1) {
            camera.update(level->getSonic()->getX(), level->getSonic()->getY());
        }
        else if (level->getTails()->getIsActive() == 1) {
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

        // managing special abilities
        level->getSonic()->manageSpecialAbility();
        level->getKnuckles()->manageSpecialAbility();
        level->getTails()->manageSpecialAbility();

        // ENEMIES
        // move
        level->getBatBrain()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getMotoBug()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getBeeBot()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need
        level->getCrabMeat()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need
        level->getBatBrain2()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getMotoBug2()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain
        level->getBeeBot2()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need
        level->getCrabMeat2()->move(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer()); // giving the active player as argument to batbrain although there's no need

        // enemy and player collision
        level->getBatBrain()->checkCollisionWithPlayer(level->getSonic());
        level->getBatBrain()->checkCollisionWithPlayer(level->getTails());
        level->getBatBrain()->checkCollisionWithPlayer(level->getKnuckles());
        level->getBatBrain2()->checkCollisionWithPlayer(level->getSonic());
        level->getBatBrain2()->checkCollisionWithPlayer(level->getTails());
        level->getBatBrain2()->checkCollisionWithPlayer(level->getKnuckles());

        level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getMotoBug()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());
        level->getMotoBug2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getMotoBug2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getMotoBug2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

        level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getBeeBot()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());
        level->getBeeBot2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getBeeBot2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getBeeBot2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getCrabMeat()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());
        level->getCrabMeat2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
        level->getCrabMeat2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive1PlayerIndex]->getPlayer());
        level->getCrabMeat2()->checkCollisionWithPlayer(level->getPlayerFactoryArray()[passive2PlayerIndex]->getPlayer());

        // projectile and player collisions
        for (int i = 0; i < 20; i++) { // max 20 projectiles for crabmeat and beebot
            if (level->getBeeBot()->getProjectilesArray()[i] != nullptr && level->getBeeBot()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getBeeBot()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
            if (level->getCrabMeat()->getProjectilesArray()[i] != nullptr && level->getCrabMeat()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getCrabMeat()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
            if (level->getBeeBot2()->getProjectilesArray()[i] != nullptr && level->getBeeBot2()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getBeeBot2()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
            if (level->getCrabMeat2()->getProjectilesArray()[i] != nullptr && level->getCrabMeat2()->getProjectilesArray()[i]->isActive()) { // check collision only if projectile is active
                level->getCrabMeat2()->getProjectilesArray()[i]->checkCollision(level->getPlayerFactoryArray()[activePlayerIndex]->getPlayer());
            }
        }
    }

    void render() {
        if (level == nullptr) return;

        window.clear();
        level->draw(window, camera);
        level->getSonic()->draw(window, camera);
        level->getTails()->draw(window, camera);
        level->getKnuckles()->draw(window, camera);
        level->getBatBrain()->draw(window, camera);
        level->getMotoBug()->draw(window, camera);
        level->getBeeBot()->draw(window, camera);
        level->getCrabMeat()->draw(window, camera);
        level->getBatBrain2()->draw(window, camera);
        level->getMotoBug2()->draw(window, camera);
        level->getBeeBot2()->draw(window, camera);
        level->getCrabMeat2()->draw(window, camera);
        window.display();
    }
};