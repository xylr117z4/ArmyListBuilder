#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include "Button.h"
#include "Army.h"

enum gameState{
	MainMenu,
	CreateNewArmy,
	LoadOldArmy,
	EditingArmy,
	SelectingOptions,
	InEditMenu,
	Exit
};

enum armies{
	Ace,
	VirtueGang,
	Nameless,
	Stat,
	Bugs,
	Ghouls
};

enum palettes{
	Red,
	Blue,
	Yellow,
	Green,
	Orange,
	Purple,
	Brown,
	Pink,
	Black,
	White
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
				buttons[i].execute((int&)currentState, buttons[i].text.getString());
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
	void checkMouseClick(sf::Event& event, gameState& currentState, Resources& resources);
	void centerText(sf::Text& workingText);
	
	//button functions
	namespace mm{ //main menu
		void exitButton(int& currentState, std::string buttonText);
		void newArmyButton(int& currentState, std::string buttonText);
		void loadOldArmyButton(int& currentState, std::string buttonText);
	};
	namespace cna{ //create new army
		//general function
		void backButton(int& currentState, std::string buttonText);
		void saveArmyButton(int& currentState, std::string buttonText);
		
		//set army name buttons
		void setArmyNameButton(int& currentState, std::string buttonText);
		void takeArmyName(bool& enteringArmyName, sf::Event& event);
		void setArmyNameButton(int& currentState, std::string buttonText);
		
		//set army buttons
		void setArmyAceButton(int& currentState, std::string buttonText);
		void setArmyVirtueGangButton(int& currentState, std::string buttonText);
		void setArmyNamelessButton(int& currentState, std::string buttonText);
		void setArmyStatButton(int& currentState, std::string buttonText);
		void setArmyBugsButton(int& currentState, std::string buttonText);
		void setArmyGhoulsButton(int& currentState, std::string buttonText);
		
		//set palette
		void setArmyPaletteRedButton(int& currentState, std::string buttonText);
		void setArmyPaletteBlueButton(int& currentState, std::string buttonText);
		void setArmyPaletteYellowButton(int& currentState, std::string buttonText);
		void setArmyPaletteGreenButton(int& currentState, std::string buttonText);
		void setArmyPaletteOrangeButton(int& currentState, std::string buttonText);
		void setArmyPalettePurpleButton(int& currentState, std::string buttonText);
		void setArmyPaletteBrownButton(int& currentState, std::string buttonText);
		void setArmyPalettePinkButton(int& currentState, std::string buttonText);
		void setArmyPaletteBlackButton(int& currentState, std::string buttonText);
		void setArmyPaletteWhiteButton(int& currentState, std::string buttonText);
	};
};

#endif // GENERALFUNCTIONS_H