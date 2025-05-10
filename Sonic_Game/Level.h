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
    Texture ringText;
    Sprite ringSprite;
    Texture healthT;
    Sprite healthS1, healthS2, healthS3, healthPickup;

public:
    Level() {
        char lvlArray[14][200]= {
    "     wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                                                                                                                        b                                                                         w",
    "w                 rrrrrr                                                                                                 b                                                                         w",
    "w     w                                                                                                                  b                                                                         w",
    "w       w                        www                        www                                                          b                                                                         w",
    "w           rrrrrrrrrrrrrrrrrh      rrrr                   wwwwwww                 ssss              h                   b                                                                         w",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
    "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
        };
        ringCount = 0;
        lvl = new char* [height];
        for (int i = 0; i < height; ++i) {
            lvl[i] = new char[200];
        }
        for (int i = 0; i < 14; i++)
        {
            for (int j= 0; j < 200; j++)
            {
                lvl[i][j] = lvlArray[i][j];
                if (lvlArray[i][j] == 'r') ringCount++;
            }
        }

        // Example layout
        //lvl[11][1] = 'w';
        /*lvl[11][2] = 'w';
        lvl[11][3] = 'w';
        for (int i = 4; i < 200; i++) {
            if (i >= 50 && i<=55)
            {
                lvl[11][i] = '\0';
            }

            else if(i>=100 && i<=120){}
            else{
                lvl[11][i] = 'w';
            }
            
        }
        for (int i = 4; i < 200; i++) {
           
                lvl[13][i] = 'e';
        

        }
        lvl[7][3] = 'w';
        lvl[6][4] = 'w';
        lvl[8][7] = 'w';
        lvl[7][8] = 'w';
        lvl[6][9] = 'w';
        lvl[9][5] = 'w';

        lvl[9][180] = 'w';*/

  //      lvl[9][6] = 'w';
  //      lvl[9][180] = 'w';
		//lvl[1][12] = 'w';
  //      lvl[2][12] = 'w';
  //      lvl[3][12] = 'w';
  //      lvl[4][12] = 'w';
  //      lvl[5][12] = 'w';

        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);
        SpikeTex.loadFromFile("Data/spike.png");
        SpikeSprite.setTexture(SpikeTex);
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

        scoreFont.loadFromFile("Data/scoreFont.ttf");
        scoreText.setFont(scoreFont);
        scoreText.setCharacterSize(30);
        scoreText.setString(to_string(ringCount));
        scoreText.setPosition(1000, 860);
        scoreText.setFillColor(Color::White);


        enemyFactoryArray = new EnemyFactory*[4];
        enemyFactoryArray[0] = new BatBrainFactory();
        enemyFactoryArray[1] = new BeeBotFactory();
        enemyFactoryArray[2] = new MotoBugFactory();
        enemyFactoryArray[3] = new CrabMeatFactory();

        // calling create functions of enemies
		float x_limit_batbrain[2] = { 0, 0 };
        float y_limit_batbrain[2] = { 0, 0 };
		float x_limit_motobug[2] = { 950, 1150 };
		float y_limit_motobug[2] = { 650, 650 };
        float x_limit_beebot[2] = { 200, 350 };
        float y_limit_beebot[2] = { 250, 490 };
		float x_limit_crabmeat[2] = { 600, 800 };
		float y_limit_crabmeat[2] = { 660, 660 };
		enemyFactoryArray[0]->createEnemy(8000, 610, x_limit_batbrain, y_limit_batbrain); // BatBrain
		enemyFactoryArray[1]->createEnemy(100, 200, x_limit_beebot, y_limit_beebot); // BeeBot
        enemyFactoryArray[2]->createEnemy(1000, 660, x_limit_motobug, y_limit_motobug); // MotoBug
		enemyFactoryArray[3]->createEnemy(600, 660, x_limit_crabmeat, y_limit_crabmeat); // CrabMeat


        playerFactoryArray = new PlayerFactory*[3];
        playerFactoryArray[0] = new SonicFactory();
        playerFactoryArray[1] = new TailsFactory();
		playerFactoryArray[2] = new KnucklesFactory(); 

        // calling create functions of players
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
        if (i >= height || j >= width || i < 0 || j < 0) {
            cout << "error happened because out of bounds access: ";
            cout << "i " << i << " j " << j << endl;
        }
          return lvl[i][j];
    }

    void setCell(char newC, int x, int y) {
        lvl[x][y] = newC;
    }

    void collectRing() { ringCount--; scoreText.setString(to_string(ringCount)); }

    Player* getSonic() {
        return playerFactoryArray[0]->getPlayer();
    }
    Enemy* getBatBrain() {return enemyFactoryArray[0]->getEnemy();}
    Enemy* getBeeBot() { return enemyFactoryArray[1]->getEnemy(); }
    Enemy* getMotoBug() { return enemyFactoryArray[2]->getEnemy(); }
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
                if (lvl[i][j] == 's') {
                    // Convert world coordinates to screen coordinates
                    float worldX = j * cell_size;
                    float worldY = i * cell_size;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);

                    // Only draw if on screen (optimization)
                    if (screenX > -cell_size && screenX < window.getSize().x &&
                        screenY > -cell_size && screenY < window.getSize().y) {
                        SpikeSprite.setPosition(screenX, screenY);
                        window.draw(SpikeSprite);
                    }
                }
                if (lvl[i][j] == 'b') {
                    // Convert world coordinates to screen coordinates
                    float worldX = j * cell_size;
                    float worldY = i * cell_size;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);

                    // Only draw if on screen (optimization)
                    if (screenX > -cell_size && screenX < window.getSize().x &&
                        screenY > -cell_size && screenY < window.getSize().y) {
                        wallSprite2.setPosition(screenX, screenY);
                        window.draw(wallSprite2);
                    }
                }
                if (lvl[i][j] == 'r') {
                    // Convert world coordinates to screen coordinates
                    float worldX = j * cell_size;
                    float worldY = i * cell_size;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);

                    // Only draw if on screen (optimization)
                    if (screenX > -cell_size && screenX < window.getSize().x &&
                        screenY > -cell_size && screenY < window.getSize().y) {
                        ringSprite.setPosition(screenX, screenY);
                        window.draw(ringSprite);
                    }
                }
                if (lvl[i][j] == 'h') {
                    // Convert world coordinates to screen coordinates
                    float worldX = j * cell_size;
                    float worldY = i * cell_size;
                    float screenX = camera.worldToScreenX(worldX);
                    float screenY = camera.worldToScreenY(worldY);

                    // Only draw if on screen (optimization)
                    if (screenX > -cell_size && screenX < window.getSize().x &&
                        screenY > -cell_size && screenY < window.getSize().y) {
                        healthPickup.setPosition(screenX, screenY);
                        healthPickup.setScale(2, 2);
                        window.draw(healthPickup);
                    }
                }

            }
        }

        if (playerFactoryArray[0]->getPlayer()->getHealth() >= 1) {
            healthS1.setPosition(0, 0);
            window.draw(healthS1);

            if (playerFactoryArray[0]->getPlayer()->getHealth() >= 2) {
                healthS2.setPosition(20, 0);
                window.draw(healthS2);

                if (playerFactoryArray[0]->getPlayer()->getHealth() == 3) {
                    healthS3.setPosition(40, 0);
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

    virtual ~Level() {
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
