#pragma once
#include "Global_variables.h"
#include "SonicFactory.h"
#include "EnemyFactory.h"
#include "BeeBotFactory.h"
#include "BeeBot.h"
#include "BatBrainFactory.h"
#include "BatBrain.h"
#include "CrabMeatFactory.h"
#include "CrabMeat.h"
#include "MotoBugFactory.h"
#include "MotoBug.h"
#include "Enemy.h"
#include "TailsFactory.h"
#include "KnucklesFactory.h"
#include "Sonic.h"
#include "Tails.h"
#include "Knuckles.h"

class Level { // abstract class
protected:
    PlayerFactory** playerFactoryArray;
	int activePlayerIndex;
    Clock playerSwitchingClock;
    float playerSwitchingClockTime;
    char** lvl;
    Texture wallTex1;
    Sprite wallSprite1;
    EnemyFactory** enemyFactoryArray;
public:
    Level() {
        lvl = new char* [height];
        for (int i = 0; i < height; ++i) {
            lvl[i] = new char[200];
        }
        // Example layout
        lvl[11][1] = 'w';
        lvl[11][2] = 'w';
        lvl[11][3] = 'w';
        for (int i = 4; i < 200; i++) {
            lvl[11][i] = 'w';
        }
        lvl[7][3] = 'w';
        lvl[9][5] = 'w';
        lvl[9][180] = 'w';

        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);

        enemyFactoryArray = new EnemyFactory*[4];
        enemyFactoryArray[0] = new BatBrainFactory();
        enemyFactoryArray[1] = new MotoBugFactory();
        enemyFactoryArray[2] = new BeeBotFactory();
        enemyFactoryArray[3] = new CrabMeatFactory();

        playerFactoryArray = new PlayerFactory*[3];
        playerFactoryArray[0] = new SonicFactory(); 
        playerFactoryArray[1] = new TailsFactory(); 
		playerFactoryArray[2] = new KnucklesFactory(); 

        // calling create functions
        playerFactoryArray[0]->createPlayer(1); // 1: isActive
        playerFactoryArray[1]->createPlayer(2); // 2: isPassive1
        playerFactoryArray[2]->createPlayer(3); // 3: isPassive2

        activePlayerIndex = 0; // Sonic is the active player by default
        playerFactoryArray[0]->getPlayer()->setIsActive(1);
        playerFactoryArray[1]->getPlayer()->setIsActive(0);
        playerFactoryArray[2]->getPlayer()->setIsActive(0);

        playerFactoryArray[0]->getPlayer()->setIsPassive1(0);
        playerFactoryArray[1]->getPlayer()->setIsPassive1(1);
        playerFactoryArray[2]->getPlayer()->setIsPassive1(0);

        playerFactoryArray[0]->getPlayer()->setIsPassive2(0);
        playerFactoryArray[1]->getPlayer()->setIsPassive2(0);
        playerFactoryArray[2]->getPlayer()->setIsPassive2(1);
        activePlayerIndex = 1;
    }

    // handleInput() to switch isActive attribute when 'S' is presses
    void handleActivePlayerSwitching() {
		playerSwitchingClockTime = playerSwitchingClock.getElapsedTime().asSeconds();
        
        if (Keyboard::isKeyPressed(Keyboard::S) && playerSwitchingClockTime>1.2) {
            if (activePlayerIndex == 0) {
                playerFactoryArray[0]->getPlayer()->setIsActive(1);
                playerFactoryArray[1]->getPlayer()->setIsActive(0);
                playerFactoryArray[2]->getPlayer()->setIsActive(0);

                playerFactoryArray[0]->getPlayer()->setIsPassive1(0);
                playerFactoryArray[1]->getPlayer()->setIsPassive1(1);
                playerFactoryArray[2]->getPlayer()->setIsPassive1(0);

                playerFactoryArray[0]->getPlayer()->setIsPassive2(0);
                playerFactoryArray[1]->getPlayer()->setIsPassive2(0);
                playerFactoryArray[2]->getPlayer()->setIsPassive2(1);
                activePlayerIndex = 1;
                playerSwitchingClock.restart();
            }
            else if (activePlayerIndex == 1 && playerSwitchingClockTime > 1.2) {
                playerFactoryArray[0]->getPlayer()->setIsActive(0);
                playerFactoryArray[1]->getPlayer()->setIsActive(1);
                playerFactoryArray[2]->getPlayer()->setIsActive(0);

                playerFactoryArray[0]->getPlayer()->setIsPassive1(0);
                playerFactoryArray[1]->getPlayer()->setIsPassive1(0);
                playerFactoryArray[2]->getPlayer()->setIsPassive1(1);

                playerFactoryArray[0]->getPlayer()->setIsPassive2(1);
                playerFactoryArray[1]->getPlayer()->setIsPassive2(0);
                playerFactoryArray[2]->getPlayer()->setIsPassive2(0);
                activePlayerIndex = 2;
                playerSwitchingClock.restart();
            }
            else if (activePlayerIndex == 2 && playerSwitchingClockTime > 1.2) {
                playerFactoryArray[0]->getPlayer()->setIsActive(0);
                playerFactoryArray[1]->getPlayer()->setIsActive(0);
                playerFactoryArray[2]->getPlayer()->setIsActive(1);

                playerFactoryArray[0]->getPlayer()->setIsPassive1(1);
                playerFactoryArray[1]->getPlayer()->setIsPassive1(0);
                playerFactoryArray[2]->getPlayer()->setIsPassive1(0);

                playerFactoryArray[0]->getPlayer()->setIsPassive2(0);
                playerFactoryArray[1]->getPlayer()->setIsPassive2(1);
                playerFactoryArray[2]->getPlayer()->setIsPassive2(0);
                activePlayerIndex = 0;
                playerSwitchingClock.restart();
            }
        }
    }

    // getters
    char getCell(int i, int j) {
        if (i >= height || j >= width || i < 0 || j < 0) {
            cout << "error happened because out of bounds access: ";
            cout << "i " << i << " j " << j << endl;
        }
        return lvl[i][j];
    }

    Player* getSonic() {
        return playerFactoryArray[0]->getPlayer();
    }

    Enemy* getBatBrain() {return enemyFactoryArray[0]->getEnemy();}
    Enemy* getMotoBug() { return enemyFactoryArray[1]->getEnemy(); }
    Enemy* getBeeBot() { return enemyFactoryArray[2]->getEnemy(); }
    Enemy* getCrabMeat() { return enemyFactoryArray[3]->getEnemy(); }

    Player* getTails() {
        return playerFactoryArray[1]->getPlayer();
    }

    Player* getKnuckles() {
        return playerFactoryArray[2]->getPlayer();
    }

    void draw(RenderWindow& window, Camera& camera) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (lvl[i][j] == 'w') {
                    // Convert world coordinates to screen coordinates
                    float worldX = j * cell_size;
                    float worldY = i * cell_size;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);

                    // Only draw if on screen (optimization)
                    if (screenX > -cell_size && screenX < window.getSize().x &&
                        screenY > -cell_size && screenY < window.getSize().y) {
                        wallSprite1.setPosition(screenX, screenY);
                        window.draw(wallSprite1);
                    }
                }
            }
        }
    }

	// this function is called in the main loop and gives the coordinates of the active player to the passive players
	void activePlayerCoordinatesSharing() {
		for (int i = 0; i < 3; i++) {
			if (playerFactoryArray[i]->getPlayer()->getIsActive() == 1) {
				for (int j = 0; j < 3; j++) {
					if (i != j) {
                        playerFactoryArray[j]->getPlayer()->setActivePlayerCoordinates(playerFactoryArray[i]->getPlayer()->getX(), playerFactoryArray[i]->getPlayer()->getY(), playerFactoryArray[i]->getPlayer()->getDirection(), playerFactoryArray[i]->getPlayer()->getMaxSpeedX(), playerFactoryArray[i]->getPlayer()->getCurrentSpeedX());
					}
				}
			}
		}
	}

    ~Level() {
        for (int i = 0; i < height; ++i) {
            delete[] lvl[i];
        }
        delete[] lvl;

        for (int i = 0; i < 3; i++) {
            delete playerFactoryArray[i];
        }

        delete[] playerFactoryArray;
    }
};
