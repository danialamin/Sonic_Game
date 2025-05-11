#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Level.h"

class Level2 : public Level {
private:

public:
    // constructor
    Level2(int l2, int l3, int width) : Level(l2, l3, width) {
        enemyFactoryArray = new EnemyFactory * [8];
        enemyFactoryArray[0] = new BatBrainFactory();
        enemyFactoryArray[1] = new BeeBotFactory();
        enemyFactoryArray[2] = new MotoBugFactory();
        enemyFactoryArray[3] = new CrabMeatFactory();
        enemyFactoryArray[4] = new BatBrainFactory();
        enemyFactoryArray[5] = new BeeBotFactory();
        enemyFactoryArray[6] = new MotoBugFactory();
        enemyFactoryArray[7] = new CrabMeatFactory();

        // calling create functions of enemies
        float x_limit_batbrain[2] = { 0, 0 };
        float y_limit_batbrain[2] = { 0, 0 };
        float x_limit_motobug[2] = { 950, 1150 };
        float y_limit_motobug[2] = { 660, 660 };
        float x_limit_beebot[2] = { 200, 350 };
        float y_limit_beebot[2] = { 250, 490 };
        float x_limit_crabmeat[2] = { 600, 800 };
        float y_limit_crabmeat[2] = { 660, 660 };
        float x_limit_motobug2[2] = { 10000, 10200 };
        float y_limit_motobug2[2] = { 660, 660 };
        float x_limit_beebot2[2] = { 2000, 2150 };
        float y_limit_beebot2[2] = { 250, 490 };
        float x_limit_crabmeat2[2] = { 7600, 7800 };
        float y_limit_crabmeat2[2] = { 660, 660 };
        enemyFactoryArray[0]->createEnemy(8000, 610, x_limit_batbrain, y_limit_batbrain); // BatBrain
        enemyFactoryArray[1]->createEnemy(100, 200, x_limit_beebot, y_limit_beebot); // BeeBot
        enemyFactoryArray[2]->createEnemy(1000, 660, x_limit_motobug, y_limit_motobug); // MotoBug
        enemyFactoryArray[3]->createEnemy(600, 660, x_limit_crabmeat, y_limit_crabmeat); // CrabMeat
        enemyFactoryArray[4]->createEnemy(4000, 610, x_limit_batbrain, y_limit_batbrain); // BatBrain
        enemyFactoryArray[5]->createEnemy(2000, 200, x_limit_beebot2, y_limit_beebot2); // BeeBot
        enemyFactoryArray[6]->createEnemy(10100, 660, x_limit_motobug2, y_limit_motobug2); // MotoBug
        enemyFactoryArray[7]->createEnemy(7600, 660, x_limit_crabmeat, y_limit_crabmeat); // CrabMeat

        // create the level layout
        // w for unbreakable wall
        // b for breakable wall
        // s for spike
        // p for platform
        // e for bottom-less pit
        // h for health pickup
        // q for special boost
        // r for ring
    char lvlArray[14][250] = {
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
    "w     h                                    b                                                            w                                      b         w                                       h  b                                                   w",
    "w    www                                   b                                                            w                                      b         w                                      www b                                                   w",
    "w                         rrrr             b                                 rrrrr                      w                 h                    b         w         rrrrr                            b                                                   w",
    "w             b           pppp             b              rrrr          h    ppppp                      w                www                   b         w         ppppp                            b                                                   w",
    "w             b                            b              pppp         www                              w                                     b   h     w                   rrrrr                   b                                                   w",
    "w             b       h                    b                                                            w      b                              b  www     w                   ppppp                  b                                                   w",
    "w             b      www                   b   qrrrrrrrrrrrrrrrh                                        b      b               rrrrrrrrrrrrrrrb         w                           rrrrrrh         b                                                   w",
    "w     www     b                  ss        b   ppppppppppppppppw                                        b      b               pppppppppppppppp         w                           ppppppw         b                                                   w",
    "w             b                 ssss       w                                                            b      b                              b         b                                           b                                                   w",
    "w      q      b       rrrrrrrrrssssssrrrrrrw                  hqq                                       b      b                              b         b            q                              w                                                   w",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  wwwwwwwwwwwwwwwwwwwwwwwwwwww           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww           wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
    "weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeew",
    "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
    };

        ringCount = 0;
        lvl = new char* [height];
        for (int i = 0; i < height; ++i) {
            lvl[i] = new char[250];
        }
        for (int i = 0; i < 14; i++)
        {
            for (int j = 0; j < 250; j++)
            {
                lvl[i][j] = lvlArray[i][j];
                if (lvlArray[i][j] == 'r') ringCount++;
            }
        }
        ringCount *= 2;
    }

    bool isLevelComplete() override {
        if (playerFactoryArray[activePlayerIndex]->getPlayer()->getX() > 12100) { // if player reaches the end of the level
            return true;
            cout << "level complete" << endl;
        }
        else {
            return false;
        }
    }
};