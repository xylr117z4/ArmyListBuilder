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

enum unitType{
	Infantry,
	LightVehicle,
	HeavyVehicle,
	Aircraft
};

namespace ace{
	namespace infantry{
		enum unit{
			FireTeam,
			SniperTeam,
			GunnerTeam,
			FlamerTeam,
			AntiTankTeam,
			MedicalTeam,
			EngineerTeam
		};
		
		enum weapon{
			AssaultRifle,
			SniperRifle,
			MarksmenRifle,
			LightMachinegun,
			Flamethrower,
			RocketLauncher,
			SMG,
			Pistol
		};
	};
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
				buttons[i].execute((int&)currentState, buttons[i].text.getString(), buttons[i].extraInfo);
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
	std::vector<std::string> getFilesInDir(std::string dir);
	
	//button functions
	namespace mm{ //main menu
		void saveArmyButton(int& currentState, std::string buttonText, std::string extraInfo);
		void exitButton(int& currentState, std::string buttonText, std::string extraInfo);
		void newArmyButton(int& currentState, std::string buttonText, std::string extraInfo);
		void loadOldArmyButton(int& currentState, std::string buttonText, std::string extraInfo);
	};
	
	namespace cna{ //create new army
		//general function
		void backButton(int& currentState, std::string buttonText, std::string extraInfo);
		void saveArmyButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//set army name buttons
		void setArmyNameButton(int& currentState, std::string buttonText, std::string extraInfo);
		void takeArmyName(bool& enteringArmyName, sf::Event& event);
		void setArmyNameButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//set army buttons
		void setArmyButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//set palette
		void setArmyPaletteButton(int& currentState, std::string buttonText, std::string extraInfo);
	};
	
	namespace loa{
		//general functions
		void updateButtonNames(Resources& resources);
		void backButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//load army from file buttons
		void loadArmyFromFileButton(int& currentState, std::string buttonText, std::string extraInfo);
		void incrementFilesShownButton(int& currentState, std::string buttonText, std::string extraInfo);
		void acceptButton(int& currentState, std::string buttonText, std::string extraInfo);
	};
	
	namespace ea{
		//general functions
		void menuButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//unit type buttons
		void typeButton(int& currentState, std::string buttonText, std::string extraInfo);
		
		//unit role buttons
		void roleButton(int& currentState, std::string buttonText, std::string extraInfo);
		void updateRoleBasedOnRace(Resources& resources);
		
		//squad buttons
		void addNewSquadButton(int& currentState, std::string buttonText, std::string extraInfo);
		void updateButtonNumbers(Resources& resources);
		void incrementSquadsShownButton(int& currentState, std::string buttonText, std::string extraInfo);
		void selectSquadButton(int& currentState, std::string buttonText, std::string extraInfo);
	};
};

#endif // GENERALFUNCTIONS_H