#pragma once
#include "Global_variables.h"
#include "SonicFactory.h"
#include "Sonic.h"

class Level { // abstract class
protected:
    PlayerFactory** playerFactoryArray;
    char** lvl;
    Texture wallTex1;
    Sprite wallSprite1;
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
        lvl[9][3] = 'w';

        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);

        playerFactoryArray = new PlayerFactory*[1]; // playerFactoryArray = new PlayerFactory*[3];
        playerFactoryArray[0] = new SonicFactory();
        playerFactoryArray[0]->createPlayer();
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

    ~Level() {
        for (int i = 0; i < height; ++i) {
            delete[] lvl[i];
        }
        delete[] lvl;

        for (int i = 0; i < 1; i++) { // for (int i = 0; i < 3; i++) {
            delete playerFactoryArray[i];
        }

        delete[] playerFactoryArray;
    }
};
