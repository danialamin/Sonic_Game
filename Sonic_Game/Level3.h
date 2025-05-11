#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;
#include "Level.h"

class Level3 : public Level {
private:

public:
    // constructor
    Level3(int l2, int l3, int width) : Level(l2,l3,width) {
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
        float x_limit_motobug[2] = { 1200, 1400 };
        float y_limit_motobug[2] = { 660, 660 };
        float x_limit_beebot[2] = { 1200, 1350 };
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
        enemyFactoryArray[1]->createEnemy(1100, 200, x_limit_beebot, y_limit_beebot); // BeeBot
        enemyFactoryArray[2]->createEnemy(1200, 660, x_limit_motobug, y_limit_motobug); // MotoBug
        enemyFactoryArray[3]->createEnemy(600, 660, x_limit_crabmeat, y_limit_crabmeat); // CrabMeat
        enemyFactoryArray[4]->createEnemy(4000, 610, x_limit_batbrain, y_limit_batbrain); // BatBrain
        enemyFactoryArray[5]->createEnemy(1900, 200, x_limit_beebot2, y_limit_beebot2); // BeeBot
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
        char lvlArray[14][300] = {
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
    "w                    b                                         b                 b      w            b            b                       b   b              w                                   wsssssssssssssssssssssssssssssssssssssssssssssssssssssw                                                   ",
    "w        r           b                      rr                 b    sss          b      w     ss     b            b                       b   b  ssss        w                                   brrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrw                                                    ",
    "w       rr     sss   b    sssss         wwwrrrr ssss    w      b    sss  h       b      w    ssss    b      sssss b           ssss       b   b  ssss                   h                         wpppppppppppppppppppppppppppppppppppppppppppppppppppw                                                     ",
    "w      rrr  ssssss   b   sssssss              rrrr sssss     h w      b   www   ssb      w   ssssss   b     ssssssb          ssssss     wsb   b  ssss        w       sswww                       wssssssssssssssssssssssssssssssssssssssssssssssssssssw                                                    ",
    "w     rrrr ssssssss  b  sssssssss        wwpppppp ppppppp   www w      bssss    ssb      w  ssssssss  b    sssssssb         ssssssss    ssb   b  ssss        w       ssq                         brrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrw                                                    ",
    "w          ssssssss  b  ssssssssssss                          ss b      bssss    ssb      w  ssssssss  b   ssssssssb        ssssssssss   ssb   b  ssss        w  ssssrrrrrrrrrrrr               wwpppppppppppppppppppppppppppppppppppppppppppppppppppw                                                     ",
    "w          ssssssss  b  sssssssssssssss                qsss    s b      bssss h  ssb      w  ssssssss  b  sssssssssb     h  ssssssssss  ssb   b  ssss    h   w  sssppppppppppppp                 wssssssssssssssssssssssssssssssssssssssssssssssssssssw                                                    ",
    "w          ssssssss  b      ssss      sss        rrrr wwwsss    b      bsssswww  b    h w  ssssssss  b sssssssssssb    www ssssssssss ssb   b  ssss   www  w                                     brrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrw                                                    ",
    "w          ssssssss  b     ssssss    sssss       pppp   sss     b      b        h b   www  ssssssss  b  ssssss   ssb         ssssssss  ssssb   b ssq         w                                   wpppppppppppppppppppppppppppppppppppppppppppppppppppw                                                     ",
    "w     rrrrrssssssss  b    ssssssss  sssssss              sss  wb      b       www b        ssssssss  b          s  b         ssssssss sssssb   bwwwwwwwwwwwww          rrr                       wssssssssssssssssssssssssssssssssssssssssssssssssssssw    r r q q r r q q r r r q q r r q q r r r r r r rr",
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww    wwwwwwwwwwwwwwwwwwwww   wwwwwwwwwwww  wwwwwwwwwwwwwwwwwwwwwwwwwwww  wwwwwwwwwwwwww  wwwwwwwwwww  wwwwwwwww   wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww w w w w w w w w w w w w w w w w w w w w w w w ww",
    "weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
    "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
        };
        ringCount = 0;
        lvl = new char* [height];
        for (int i = 0; i < height; ++i) {
            lvl[i] = new char[300];
        }
        for (int i = 0; i < 14; i++)
        {
            for (int j = 0; j < 300; j++)
            {
                lvl[i][j] = lvlArray[i][j];
                if (lvlArray[i][j] == 'r') ringCount++;
            }
        }
        ringCount *= 2;
    }

    bool isLevelComplete() override {
        if (playerFactoryArray[activePlayerIndex]->getPlayer()->getX() > 12400) { // if player reaches the end of the level
            return true;
        }
        else {
            return false;
        }
    }
};