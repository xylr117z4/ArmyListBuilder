#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

enum gameState{
	MainMenu,
	CreateNewArmy,
	LoadOldArmy,
	EditingArmy,
	SelectingOptions,
	InEditMenu,
	Exit
};

struct Resources{
	std::vector<sf::Texture> textures;
	std::vector<Button> buttons;
	void draw(sf::RenderWindow& window){
		for(unsigned int i = 0; i < buttons.size(); ++i){
			window.draw(buttons[i].sprite);
			window.draw(buttons[i].text);
		}
	}
	int checkForClick(sf::Vector2f mousePos, gameState& currentState){
		for(unsigned int i = 0; i < buttons.size(); ++i){
			if(buttons[i].isClicked(mousePos)){
				buttons[i].execute((int&)currentState);
				return i;
			}
		}
		return -1;
	}
};

namespace gsh{ //gamestate handler
	void init(std::vector<Resources>& resources);
	void render(sf::RenderWindow& window, gameState& currentState, std::vector<Resources>& resources);
	void handleInput(sf::RenderWindow& window, gameState& currentState, std::vector<Resources>& resources);
	
	//button functions
	namespace mm{ //main menu
		void exitButton(int& currentState);
		void newArmyButton(int& currentState);
	};
	namespace cna{
		void backButton(int& currentState);
	};
};

#endif // GENERALFUNCTIONS_H