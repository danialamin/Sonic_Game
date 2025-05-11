#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
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
#include "Obstacle.h"
#include "BreakableWall.h"
#include "UnbreakableWall.h"
#include "Spike.h"
#include "BottomlessPit.h"
#include "Platform.h"
#include "CollectibleFactory.h"
#include "Collectible.h"
#include "Ring.h"
#include "SpecialBoost.h"
#include "HealthPickup.h"
#include "RingFactory.h"
#include "HealthPickupFactory.h"
#include "SpecialBoostFactory.h"

class Level { // abstract class
protected:
    PlayerFactory** playerFactoryArray;
	int activePlayerIndex; // 0 for sonic, 1 for tails, 2 for knuckles
    Clock playerSwitchingClock; // after how much time pressing can change the player
    float playerSwitchingClockTime;
    Font scoreFont;
    Text scoreText;
    EnemyFactory** enemyFactoryArray;

    char** lvl;
    int ringCount;
    Texture wallTex1;
    Sprite wallSprite1;
    Texture wallTex2;
    Sprite wallSprite2;
    Texture SpikeTex;
    Sprite SpikeSprite;
    Texture PlatformTex;
	Sprite PlatformSprite;
    Texture BottomlessPitTex;
	Sprite BottomlessPitSprite;
    Texture ringText;
    Sprite ringSprite;
    Texture healthT;
	Texture specialBoostTex;
	Sprite specialBoostSprite;
    Sprite healthS1, healthS2, healthS3, healthPickup;
    Obstacle* breakableWall;
    Obstacle* unbreakableWall;
    Obstacle* spike;
	Obstacle* bottomlessPit;
    Obstacle* platform;
	CollectibleFactory** collectibleFactoryArray;

    int height;
    int width;
public:
    Level(int l2, int l3, int width) {
        height = 14;
        this->width = width;
        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);
        SpikeTex.loadFromFile("Data/spike.png");
        SpikeSprite.setTexture(SpikeTex);
		PlatformTex.loadFromFile("Data/brick2.png");
		PlatformSprite.setTexture(PlatformTex);
        BottomlessPitTex.loadFromFile("Data/bottomlesspit.png");
		BottomlessPitSprite.setTexture(BottomlessPitTex);
		BottomlessPitSprite.setScale(5.5, 6);
        healthT.loadFromFile("Data/health.png");
        wallTex2.loadFromFile("Data/brick3.png");
        wallSprite2.setTexture(wallTex2);
        healthS1.setTexture(healthT);
        healthS2.setTexture(healthT);
        healthS3.setTexture(healthT);
        healthPickup.setTexture(healthT);
        ringText.loadFromFile("Data/ring.png");
        ringSprite.setTexture(ringText);
        ringSprite.setScale(2, 2);
		specialBoostTex.loadFromFile("Data/specialboost.png");
		specialBoostSprite.setTexture(specialBoostTex);
		specialBoostSprite.setScale(2, 2);


        scoreFont.loadFromFile("Data/scoreFont.ttf");
        scoreText.setFont(scoreFont);
        scoreText.setCharacterSize(30);
        scoreText.setString(to_string(ringCount));
        scoreText.setPosition(1000, 100);
        scoreText.setFillColor(Color::White);

        playerFactoryArray = new PlayerFactory*[3];
        playerFactoryArray[0] = new SonicFactory();
        playerFactoryArray[1] = new TailsFactory();
		playerFactoryArray[2] = new KnucklesFactory(); 

        // calling create functions of players
        playerFactoryArray[0]->createPlayer(1, l2, l3); // 1: isActive
        playerFactoryArray[1]->createPlayer(2, l2, l3); // 2: isPassive1
        playerFactoryArray[2]->createPlayer(3, l2, l3); // 3: isPassive2


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

        breakableWall = new BreakableWall(wallSprite2);
        unbreakableWall = new UnbreakableWall(wallSprite1);
        spike = new Spike(SpikeSprite);
		bottomlessPit = new BottomlessPit(BottomlessPitSprite);
		platform = new Platform(PlatformSprite);

        collectibleFactoryArray = new CollectibleFactory * [3];
        collectibleFactoryArray[0] = new RingFactory();
        collectibleFactoryArray[1] = new HealthPickupFactory();
        collectibleFactoryArray[2] = new SpecialBoostFactory();
        // creating the collectibles
        collectibleFactoryArray[0]->createCollectible(ringSprite);
        collectibleFactoryArray[1]->createCollectible(healthPickup);
        collectibleFactoryArray[2]->createCollectible(specialBoostSprite);

    }

    // handleInput() to switch isActive attribute when 'Z' is presses
    void handleActivePlayerSwitching() {
		playerSwitchingClockTime = playerSwitchingClock.getElapsedTime().asSeconds();
        
        if (Keyboard::isKeyPressed(Keyboard::Z) && playerSwitchingClockTime>1.2) {
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
	PlayerFactory** getPlayerFactoryArray() {
		return playerFactoryArray;
	}
    int getActivePlayerIndex() {
		return activePlayerIndex;
    }
    char getCell(int i, int j) {
        /*if (i >= height || j >= width || i < 0 || j < 0) {
            cout << "error happened because out of bounds access: ";
            cout << "i " << i << " j " << j << endl;
        }*/
          return lvl[i][j];
    }

    void setCell(char newC, int x, int y) {
        lvl[x][y] = newC;
    }

    void collectRing() { 
        ringCount--;
        scoreText.setString(to_string(ringCount));
    }

    Player* getSonic() {
        return playerFactoryArray[0]->getPlayer();
    }
    /////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    Enemy* getBatBrain() {return enemyFactoryArray[0]->getEnemy();}
    Enemy* getBeeBot() { return enemyFactoryArray[1]->getEnemy(); }
    Enemy* getMotoBug() { return enemyFactoryArray[2]->getEnemy(); }
    Enemy* getCrabMeat() { return enemyFactoryArray[3]->getEnemy(); }
    Enemy* getBatBrain2() { return enemyFactoryArray[4]->getEnemy(); }
    Enemy* getBeeBot2() { return enemyFactoryArray[5]->getEnemy(); }
    Enemy* getMotoBug2() { return enemyFactoryArray[6]->getEnemy(); }
    Enemy* getCrabMeat2() { return enemyFactoryArray[7]->getEnemy(); }
    
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
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        unbreakableWall->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 's') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        spike->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'b') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        breakableWall->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'p') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        platform->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'e') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        bottomlessPit->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'r') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        collectibleFactoryArray[0]->getCollectible()->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'h') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        collectibleFactoryArray[1]->getCollectible()->draw(window, screenX, screenY);
                    }
                }
                if (lvl[i][j] == 'q') {
                    float worldX = j * 64;
                    float worldY = i * 64;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);
                    if (screenX > -64 && screenX < window.getSize().x &&
                        screenY > -64 && screenY < window.getSize().y) {
                        collectibleFactoryArray[2]->getCollectible()->draw(window, screenX, screenY);
                    }
                }
            }
        }

        if (playerFactoryArray[0]->getPlayer()->getHealth() >= 1) {
            healthS1.setPosition(100, 50);
            window.draw(healthS1);

            if (playerFactoryArray[0]->getPlayer()->getHealth() >= 2) {
                healthS2.setPosition(120, 50);
                window.draw(healthS2);

                if (playerFactoryArray[0]->getPlayer()->getHealth() == 3) {
                    healthS3.setPosition(140, 50);
                    window.draw(healthS3);
                }
            }
            
        }

        window.draw(scoreText);
    }

	// this function is called in the main loop and gives the coordinates of the active player to the passive players
	void activePlayerCoordinatesSharing() {
		for (int i = 0; i < 3; i++) {
			if (playerFactoryArray[i]->getPlayer()->getIsActive() == 1) {
				for (int j = 0; j < 3; j++) {
					if (i != j) {
                        playerFactoryArray[j]->getPlayer()->setActivePlayerCoordinates(playerFactoryArray[i]->getPlayer()->getX(), playerFactoryArray[i]->getPlayer()->getY(), playerFactoryArray[i]->getPlayer()->getDirection(), playerFactoryArray[i]->getPlayer()->getMaxSpeedX());
					}
				}
			}
		}
	}

    bool levelFailed() {
        if (playerFactoryArray[activePlayerIndex]->getPlayer()->getHealth() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

	virtual bool isLevelComplete() = 0; // pure virtual function to be implemented in derived classes

    virtual ~Level() {
        for (int i = 0; i < 14; ++i) {
            delete[] lvl[i];
        }
        delete[] lvl;

        for (int i = 0; i < 3; i++) {
            delete playerFactoryArray[i];
        }

        delete[] playerFactoryArray;

		delete breakableWall;
		delete unbreakableWall;
		delete spike;
		delete bottomlessPit;
		delete platform;
        //////////////////////////////////////////////
        ////////////////////////////////////////////////
        //////////////////////////////////////////
        ////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////
        ///////////////////////////////////////
        ///////////////////////////////////////////
		for (int i = 0; i < 8; i++) {
			delete enemyFactoryArray[i];
		}
		delete[] enemyFactoryArray;

        for (int i = 0; i < 3; i++) {
            delete collectibleFactoryArray[i];
        }
        delete[] collectibleFactoryArray;
    }
};
