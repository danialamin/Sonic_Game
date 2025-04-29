#pragma once
#include "Global_variables.h"

class Level {
private:
    char** lvl;
    Texture wallTex1;
    Sprite wallSprite1;
public:
    Level() {
        lvl = new char* [height];
        for (int i = 0; i < height; ++i) {
            lvl[i] = new char[width] {'\0'};
        }
        // Example layout
        lvl[11][1] = 'w';
        lvl[11][2] = 'w';
        lvl[11][3] = 'w';

        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);
    }

    ~Level() {
        for (int i = 0; i < height; ++i) {
            delete[] lvl[i];
        }
        delete[] lvl;
    }

    char getCell(int i, int j) {
        return lvl[i][j];
    }

    void draw(RenderWindow& window) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (lvl[i][j] == 'w') {
                    wallSprite1.setPosition(j * cell_size, i * cell_size);
                    window.draw(wallSprite1);
                }
            }
        }
    }
};
