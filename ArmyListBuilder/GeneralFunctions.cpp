#include "GeneralFunctions.h"

namespace gsh{
	
	sf::Font font;
	Army workingArmy;
	std::string ssArmyName;
	bool enteringArmyName = false;
	
	//main menu button functions
	namespace mm{
		void exitButton(int& currentState){
			currentState = Exit;
		}
		
		void newArmyButton(int& currentState){
			currentState = CreateNewArmy;
			workingArmy = Army("New Army", Ace);
		}
	};
	
	//create new army button functions
	namespace cna{
		sf::Text workingArmyName;
		
		void backButton(int& currentState){
			--currentState;
		}
		
		void saveArmyButton(int& currentState){
			workingArmy.writeToFile();
		}
		
		void setArmyNameButton(int& currentState){
			enteringArmyName = true;
			workingArmyName.setString("Enter new army name!");
			ssArmyName = "";
		}
		
		void setArmyAceButton(int& currentState){
			workingArmy.armyID = Ace;
		}
		
		void setArmyVirtueGangButton(int& currentState){
			workingArmy.armyID = VirtueGang;
		}
		
		void setArmyNamelessButton(int& currentState){
			workingArmy.armyID = Nameless;
		}
		
		void setArmyStatButton(int& currentState){
			workingArmy.armyID = Stat;
		}
		
		void setArmyBugsButton(int& currentState){
			workingArmy.armyID = Bugs;
		}
		
		void setArmyGhoulsButton(int& currentState){
			workingArmy.armyID = Ghouls;
		}
		
		void takeArmyName(bool& enteringArmyName,sf::Event& event){
			if(enteringArmyName){
				if(event.type == sf::Event::KeyPressed){
					if(event.key.code == sf::Keyboard::Return) {
						enteringArmyName = false;
						workingArmy.armyName = ssArmyName;
					}
					else if(event.key.code == sf::Keyboard::BackSpace){
						ssArmyName.pop_back();
						cna::workingArmyName.setString(ssArmyName);
					}
				}
				else if(event.type == sf::Event::TextEntered){
					if(event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 9166){
						ssArmyName += static_cast<char>(event.text.unicode);
					}
					cna::workingArmyName.setString(ssArmyName);
				}
			}
		}
	};
	
	void checkMouseClick(sf::Event& event, gameState& currentState, Resources& resources){
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			int mouseX = event.mouseButton.x;
			int mouseY = event.mouseButton.y;
			printf("x: %d y: %d button: %d\n\n", mouseX, mouseY, resources.checkForClick(sf::Vector2f(mouseX, mouseY), currentState));
		}
	}
	
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
		cna::workingArmyName.setPosition(200, 75);
		cna::workingArmyName.setString("New Army");
		resources[CreateNewArmy].buttons.push_back(Button(0, 300, 200, 50, cna::setArmyNameButton, resources[MainMenu].textures[0], "Set Name", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 500, 200, 50, cna::saveArmyButton, resources[MainMenu].textures[0], "Save", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 550, 200, 50, cna::backButton, resources[MainMenu].textures[0], "Back", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 250, 200, 50, cna::setArmyAceButton, resources[MainMenu].textures[0], "A.C.E.", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 300, 200, 50, cna::setArmyVirtueGangButton, resources[MainMenu].textures[0], "Virtue Gang", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 350, 200, 50, cna::setArmyNamelessButton, resources[MainMenu].textures[0], "Nameless", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 400, 200, 50, cna::setArmyStatButton, resources[MainMenu].textures[0], "S.T.A.T.", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 450, 200, 50, cna::setArmyBugsButton, resources[MainMenu].textures[0], "Bugs", font));
		
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
					checkMouseClick(event, currentState, resources[MainMenu]);
					break;
					
				case CreateNewArmy:
					checkMouseClick(event, currentState, resources[CreateNewArmy]);
					cna::takeArmyName(enteringArmyName, event);
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