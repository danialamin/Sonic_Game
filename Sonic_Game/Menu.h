#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

class Menu {
private:
	int menuState, gameState;
	float arrowX, arrowY;
	Texture backgroundT, arrowT;
	Sprite backgroundS, arrowS;
	bool upKeyPressed;
	bool downKeyPressed;
	
public:
	Menu() :menuState(0),gameState(0), arrowX(675), arrowY(393) {
		backgroundT.loadFromFile("Data/Menu.png");
		backgroundS.setTexture(backgroundT);
		arrowT.loadFromFile("Data/Arrow.png");
		arrowS.setTexture(arrowT);
		downKeyPressed = false;
		upKeyPressed = false;
	}
	void setArrowPosition() {
		if (menuState == 0) {
			arrowX = 675; arrowY = 393;
		}
		else if (menuState == 1) {
			arrowX = 629; arrowY = 510;
		}
		else if (menuState == 2) {
			arrowX = 683; arrowY = 618;
		}
		else if (menuState == 3) {
			arrowX = 884; arrowY = 742;
		}
	}
	int getGameState() { return gameState; }
	void menuInput() {
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (!downKeyPressed) {
				downKeyPressed = true;
				menuState++;
				menuState = (menuState >= 4) ? 0 : menuState;
				setArrowPosition();
			}

		}
		else { downKeyPressed = false;; }
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (!upKeyPressed) { 
				upKeyPressed = true;
				menuState--;
				menuState = (menuState <= -1) ? 3 : menuState;
				setArrowPosition();
			}
		}
		else { upKeyPressed = false; }

		setArrowPosition();

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			if (menuState == 0) gameState = 1;
		}
			
	}
	void draw(RenderWindow& window) {
		window.clear();
		backgroundS.setPosition(0, 0);
		arrowS.setPosition(arrowX, arrowY);
		window.draw(backgroundS);
		window.draw(arrowS);
		window.display();
		
	}
};
