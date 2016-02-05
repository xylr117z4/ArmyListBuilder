#include "GeneralFunctions.h"

namespace gsh{
	
	sf::Font font;
	Army workingArmy;
	std::stringstream ssArmyName;
	bool enteringArmyName = false;
	
	//main menu button functions
	namespace mm{
		void exitButton(int& currentState){
			currentState = Exit;
		}
		
		void newArmyButton(int& currentState){
			currentState = CreateNewArmy;
			workingArmy = Army("workingName", Ace);
		}
	};
	
	//create new army button functions
	namespace cna{
		sf::Text workingArmyName;
		
		void backButton(int& currentState){
			--currentState;
		}
		
		void saveArmy(int& currentState){
			workingArmy.writeToFile();
		}
		
		void setArmyName(int& currentState){
			enteringArmyName = true;
			ssArmyName.str("");
		}
	};
	
	void init(std::vector<Resources>& resources){
		//load resources resize vector
		resources.resize(7);
		sf::Texture temp;
		temp.loadFromFile("img/button.png");
		font.loadFromFile("font/LiberationSans-Regular.ttf");
		
		//set buttons for main menu
		resources[MainMenu].textures.push_back(temp);
		resources[MainMenu].buttons.push_back(Button(300, 250, 200, 50, mm::newArmyButton, resources[MainMenu].textures[0], "New", font));
		resources[MainMenu].buttons.push_back(Button(300, 400, 200, 50, mm::exitButton, resources[MainMenu].textures[0], "Exit", font));
		
		//set buttons for create new army menu
		cna::workingArmyName.setFont(font);
		resources[CreateNewArmy].buttons.push_back(Button(0, 300, 200, 50, cna::setArmyName, resources[MainMenu].textures[0], "Set Name", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 500, 200, 50, cna::saveArmy, resources[MainMenu].textures[0], "Save", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 550, 200, 50, cna::backButton, resources[MainMenu].textures[0], "Back", font));
		
	}

	void render(sf::RenderWindow& window, gameState& currentState, std::vector<Resources>& resources){
		switch(currentState){
			case MainMenu:
				//draw buttons
				resources[MainMenu].draw(window);
				break;
				
			case CreateNewArmy:
				resources[CreateNewArmy].draw(window);
				window.draw(cna::workingArmyName);
				break;
				
			case LoadOldArmy:
				break;
				
			case EditingArmy:
				break;
				
			case SelectingOptions:
				break;
				
			case InEditMenu:
				break;
				
			default:
				break;
		}
	}

	void handleInput(sf::RenderWindow& window, gameState& currentState, std::vector<Resources>& resources){
		sf::Event event;
		while (window.pollEvent(event)){
			// Close window: exit
			if (event.type == sf::Event::Closed){
				currentState = Exit;
			}
			
			// Depending on state handle different inputs
			switch(currentState){
				case MainMenu:
					//check if buttons are clicked
					if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						printf("x: %d y: %d button: %d\n\n", mouseX, mouseY, resources[MainMenu].checkForClick(sf::Vector2f(mouseX, mouseY), currentState));
					}
					break;
					
				case CreateNewArmy:
					if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						printf("x: %d y: %d button: %d\n\n", mouseX, mouseY, resources[CreateNewArmy].checkForClick(sf::Vector2f(mouseX, mouseY), currentState));
					}
					if(enteringArmyName){
						if(event.type == sf::Event::KeyPressed){
							if(event.key.code == sf::Keyboard::Return) {
								enteringArmyName = false;
								workingArmy.armyName = ssArmyName.str();
							}
							else if(event.key.code == sf::Keyboard::BackSpace){
								std::string temp = ssArmyName.str();
								temp.pop_back();
								ssArmyName.str(temp);
								ssArmyName.seekg(0, ssArmyName.end);
								//ssArmyName.seekp(0, ssArmyName.end);
								cna::workingArmyName.setString(ssArmyName.str());
							}
						}
						else if(event.type == sf::Event::TextEntered){
							std::cout << static_cast<char>(event.text.unicode) << "\n";
							ssArmyName << static_cast<char>(event.text.unicode);
							cna::workingArmyName.setString(ssArmyName.str());
						}
					}
					break;
					
				case LoadOldArmy:
					break;
					
				case EditingArmy:
					break;
					
				case SelectingOptions:
					break;
					
				case InEditMenu:
					break;
					
				case Exit:
					window.close();
					break;
					
				default:
					break;
			}
		}
	}
};