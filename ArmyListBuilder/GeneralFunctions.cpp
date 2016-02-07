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
		
		void loadOldArmyButton(int& currentState){
			currentState = LoadOldArmy;
			
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
			centerText(workingArmyName);
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
		
		void setArmyPaletteRedButton(int& currentState){
			workingArmy.armyPalette = Red;
		}
		
		void setArmyPaletteBlueButton(int& currentState){
			workingArmy.armyPalette = Blue;
		}
		
		void setArmyPaletteYellowButton(int& currentState){
			workingArmy.armyPalette = Yellow;
		}
		
		void setArmyPaletteGreenButton(int& currentState){
			workingArmy.armyPalette = Green;
		}
		
		void setArmyPaletteOrangeButton(int& currentState){
			workingArmy.armyPalette = Orange;
		}
		
		void setArmyPalettePurpleButton(int& currentState){
			workingArmy.armyPalette = Purple;
		}
		
		void setArmyPaletteBrownButton(int& currentState){
			workingArmy.armyPalette = Brown;
		}
		
		void setArmyPalettePinkButton(int& currentState){
			workingArmy.armyPalette = Pink;
		}
		
		void setArmyPaletteBlackButton(int& currentState){
			workingArmy.armyPalette = Black;
		}
		
		void setArmyPaletteWhiteButton(int& currentState){
			workingArmy.armyPalette = White;
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
						workingArmyName.setString(ssArmyName);
					}
				}
				else if(event.type == sf::Event::TextEntered){
					if(event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 9166){
						ssArmyName += static_cast<char>(event.text.unicode);
					}
					workingArmyName.setString(ssArmyName);
					centerText(workingArmyName);
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
	
	void centerText(sf::Text& workingText){
		sf::Rect<float> workingTextSize = workingText.getLocalBounds();
		workingText.setOrigin(workingTextSize.width/2, workingTextSize.height);
	}
	
	std::vector<std::string> getFilesInDir(std::string dir){
		DIR *dirp;
		dirp = opendir(dir.c_str());
		
		std::vector<std::string> filesInDir;
		
		struct dirent *dp;
		
		do{
			if((dp = readdir(dirp)) != NULL){
				filesInDir.push_back(dp->d_name);
			}
			else{
				closedir(dirp);
			}
		} while(dp != NULL);
		
		return filesInDir;
	}
	
	void init(std::vector<Resources>& resources){
		//load resources resize vector
		resources.resize(7);
		sf::Texture temp;
		temp.loadFromFile("img/button.png");
		font.loadFromFile("font/LiberationSans-Regular.ttf");
		std::vector<std::string> filesInDir = getFilesInDir(".");
		
		//set buttons for main menu
		resources[MainMenu].textures.push_back(temp);
		resources[MainMenu].buttons.push_back(Button(300, 200, 200, 50, mm::newArmyButton, resources[MainMenu].textures[0], "New", font));
		resources[MainMenu].buttons.push_back(Button(300, 300, 200, 50, mm::loadOldArmyButton, resources[MainMenu].textures[0], "Edit", font));
		resources[MainMenu].buttons.push_back(Button(300, 400, 200, 50, mm::exitButton, resources[MainMenu].textures[0], "Exit", font));
		
		//set buttons for create new army menu
		cna::workingArmyName.setFont(font);
		cna::workingArmyName.setPosition(400, 75);
		cna::workingArmyName.setString("New Army");
		centerText(cna::workingArmyName);
		//general buttons
		resources[CreateNewArmy].buttons.push_back(Button(300, 450, 200, 50, cna::setArmyNameButton, resources[MainMenu].textures[0], "Set Name", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 500, 200, 50, cna::saveArmyButton, resources[MainMenu].textures[0], "Save", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 550, 200, 50, cna::backButton, resources[MainMenu].textures[0], "Back", font));
		//army selection
		resources[CreateNewArmy].buttons.push_back(Button(0, 300, 200, 50, cna::setArmyAceButton, resources[MainMenu].textures[0], "A.C.E.", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 350, 200, 50, cna::setArmyVirtueGangButton, resources[MainMenu].textures[0], "VirtueGang", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 400, 200, 50, cna::setArmyNamelessButton, resources[MainMenu].textures[0], "Nameless", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 450, 200, 50, cna::setArmyStatButton, resources[MainMenu].textures[0], "S.T.A.T.", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 500, 200, 50, cna::setArmyBugsButton, resources[MainMenu].textures[0], "Bugs", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 550, 200, 50, cna::setArmyGhoulsButton, resources[MainMenu].textures[0], "Ghouls", font));
		//palette selection
		resources[CreateNewArmy].buttons.push_back(Button(600, 100, 200, 50, cna::setArmyPaletteRedButton, resources[MainMenu].textures[0], "Red", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 150, 200, 50, cna::setArmyPaletteBlueButton, resources[MainMenu].textures[0], "Blue", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 200, 200, 50, cna::setArmyPaletteYellowButton, resources[MainMenu].textures[0], "Yellow", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 250, 200, 50, cna::setArmyPaletteGreenButton, resources[MainMenu].textures[0], "Green", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 300, 200, 50, cna::setArmyPaletteOrangeButton, resources[MainMenu].textures[0], "Orange", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 350, 200, 50, cna::setArmyPalettePurpleButton, resources[MainMenu].textures[0], "Purple", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 400, 200, 50, cna::setArmyPaletteBrownButton, resources[MainMenu].textures[0], "Brown", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 450, 200, 50, cna::setArmyPalettePinkButton, resources[MainMenu].textures[0], "Pink", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 500, 200, 50, cna::setArmyPaletteBlackButton, resources[MainMenu].textures[0], "Black", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 550, 200, 50, cna::setArmyPaletteWhiteButton, resources[MainMenu].textures[0], "White", font));
		
		//set buttons for load old army menu
		
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