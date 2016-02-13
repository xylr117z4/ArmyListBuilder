#include "GeneralFunctions.h"

namespace gsh{
	//general use
	sf::Font font;
	Army workingArmy;
	sf::Text workingArmyName;
	int textHeight = 22;
	
	//for creating new army
	std::string ssArmyName;
	bool enteringArmyName = false;
	
	//for loading old army
	std::vector<std::string> filesInDir;
	unsigned int fileIncrementor = 0;
	
	//main menu button functions
	namespace mm{
		void exitButton(int& currentState, std::string buttonText){
			currentState = Exit;
		}
		
		void newArmyButton(int& currentState, std::string buttonText){
			currentState = CreateNewArmy;
			workingArmy = Army("New Army", Ace);
			workingArmyName.setString("New Army");
			centerText(workingArmyName);
		}
		
		void loadOldArmyButton(int& currentState, std::string buttonText){
			currentState = LoadOldArmy;
			filesInDir = getFilesInDir("json");
		}
	};
	
	//create new army button functions
	namespace cna{
		
		void backButton(int& currentState, std::string buttonText){
			currentState = MainMenu;
		}
		
		void saveArmyButton(int& currentState, std::string buttonText){
			workingArmy.writeToFile();
			currentState = EditingArmy;
		}
		
		void setArmyNameButton(int& currentState, std::string buttonText){
			enteringArmyName = true;
			workingArmyName.setString("Enter new army name!");
			centerText(workingArmyName);
			ssArmyName = "";
		}
		
		void setArmyButton(int& currentState, std::string buttonText){
			if(buttonText == "A.C.E."){
				workingArmy.armyID = Ace;
			}
			else if(buttonText == "VirtueGang"){
				workingArmy.armyID = VirtueGang;
			}
			else if(buttonText == "Nameless"){
				workingArmy.armyID = Nameless;
			}
			else if(buttonText == "S.T.A.T."){
				workingArmy.armyID = Stat;
			}
			else if(buttonText == "Bugs"){
				workingArmy.armyID = Bugs;
			}
			else if(buttonText == "Ghouls"){
				workingArmy.armyID = Ghouls;
			}
		}
		
		void setArmyPaletteButton(int& currentState, std::string buttonText){
			if(buttonText == "Red"){
				workingArmy.armyPalette = Red;
			}
			else if(buttonText == "Blue"){
				workingArmy.armyPalette = Blue;
			}
			else if(buttonText == "Yellow"){
				workingArmy.armyPalette = Yellow;
			}
			else if(buttonText == "Green"){
				workingArmy.armyPalette = Green;
			}
			else if(buttonText == "Orange"){
				workingArmy.armyPalette = Orange;
			}
			else if(buttonText == "Purple"){
				workingArmy.armyPalette = Purple;
			}
			else if(buttonText == "Brown"){
				workingArmy.armyPalette = Brown;
			}
			else if(buttonText == "Pink"){
				workingArmy.armyPalette = Pink;
			}
			else if(buttonText == "Black"){
				workingArmy.armyPalette = Black;
			}
			else if(buttonText == "White"){
				workingArmy.armyPalette = White;
			}
		}
		
		void takeArmyName(bool& enteringArmyName, sf::Event& event){
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
				else if(event.type == sf::Event::MouseButtonPressed && ssArmyName != ""){
					enteringArmyName = false;
					workingArmy.armyName = ssArmyName;
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
	
	namespace loa{
		int numOtherOfButtons = 4;
		
		void backButton(int& currentState, std::string buttonText){
			currentState = MainMenu;
		}
		
		void updateButtonNames(Resources& resources){
			std::string extention = ".json";
			std::vector<std::string> useableFiles;
			for(unsigned int i = 0; i < filesInDir.size(); ++i){
				if(filesInDir[i].find(extention) != std::string::npos){
					useableFiles.push_back(filesInDir[i]);
				}
			}
			for(unsigned int i = 0; i < resources.buttons.size(); ++i){
				if(i+fileIncrementor < useableFiles.size()){
					resources.buttons[i+numOtherOfButtons].setText(useableFiles[i+fileIncrementor]);
				}
				else if(i+numOtherOfButtons < resources.buttons.size()){
					resources.buttons[i+numOtherOfButtons].setText("");
				}
				else{
					break;
				}
			}
		}
		
		void incrementFilesShown(int& currentState, std::string buttonText){
			if(buttonText == "v" && fileIncrementor < filesInDir.size()){ //alt 31
				++fileIncrementor;
			}
			else if(buttonText == "^" && fileIncrementor > 0){ //alt 30
				--fileIncrementor;
			}
		}
		
		void loadArmyFromFile(int& currentState, std::string buttonText){
			if(buttonText != ""){
				Army temp(buttonText, 0);
				temp.readFromFile(buttonText);
				workingArmy = temp;
				printf("armyName: %s\n", workingArmy.armyName.c_str());
				printf("armyID: %d\n", workingArmy.armyID);
				printf("armyPallette: %d\n\n", workingArmy.armyPalette);
			}
		}
		
		void acceptButton(int& currentState, std::string buttonText){
			if(workingArmy.armyName != ""){
				currentState = EditingArmy;
			}
		}
	};
	
	namespace ea{
		void menuButton(int& currentState, std::string buttonText){
			currentState = MainMenu; //just temporary as I build the edit army screen
		}
		
		void typeButton(int& currentState, std::string buttonText){
			//need squad ground work first
		}
	};
	
	void checkMouseClick(sf::Event& event, gameState& currentState, Resources& resources){
		if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			int mouseX = event.mouseButton.x;
			int mouseY = event.mouseButton.y;
			resources.checkForClick(sf::Vector2f(mouseX, mouseY), currentState);
		}
	}
	
	void centerText(sf::Text& workingText){
		sf::Rect<float> workingTextSize = workingText.getLocalBounds();
		workingText.setOrigin(workingTextSize.width/2, textHeight);//workingTextSize.height);
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
		font.loadFromFile("font/LiberationSans-Regular.ttf");
		
		//we'll just use the main menu texture vector to hold the button sprites eh...
		sf::Texture temp;
		temp.loadFromFile("img/button.png");
		resources[MainMenu].textures.push_back(temp);
		temp.loadFromFile("img/largeButton.png");
		resources[MainMenu].textures.push_back(temp);
		temp.loadFromFile("img/smallButton.png");
		resources[MainMenu].textures.push_back(temp);
		
		//set buttons for main menu
		resources[MainMenu].buttons.push_back(Button(300, 200, 200, 50, mm::newArmyButton, resources[MainMenu].textures[0], "New", font));
		resources[MainMenu].buttons.push_back(Button(300, 300, 200, 50, mm::loadOldArmyButton, resources[MainMenu].textures[0], "Edit", font));
		resources[MainMenu].buttons.push_back(Button(300, 400, 200, 50, mm::exitButton, resources[MainMenu].textures[0], "Exit", font));
		
		//set buttons for create new army menu
		workingArmyName.setFont(font);
		workingArmyName.setPosition(400, 75);
		workingArmyName.setString("New Army");
		centerText(workingArmyName);
		//general buttons
		resources[CreateNewArmy].buttons.push_back(Button(300, 450, 200, 50, cna::setArmyNameButton, resources[MainMenu].textures[0], "Set Name", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 500, 200, 50, cna::saveArmyButton, resources[MainMenu].textures[0], "Save", font));
		resources[CreateNewArmy].buttons.push_back(Button(300, 550, 200, 50, cna::backButton, resources[MainMenu].textures[0], "Back", font));
		//army selection
		resources[CreateNewArmy].buttons.push_back(Button(0, 300, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "A.C.E.", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 350, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "VirtueGang", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 400, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "Nameless", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 450, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "S.T.A.T.", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 500, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "Bugs", font));
		resources[CreateNewArmy].buttons.push_back(Button(0, 550, 200, 50, cna::setArmyButton, resources[MainMenu].textures[0], "Ghouls", font));
		//palette selection
		resources[CreateNewArmy].buttons.push_back(Button(600, 100, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Red", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 150, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Blue", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 200, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Yellow", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 250, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Green", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 300, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Orange", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 350, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Purple", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 400, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Brown", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 450, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Pink", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 500, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "Black", font));
		resources[CreateNewArmy].buttons.push_back(Button(600, 550, 200, 50, cna::setArmyPaletteButton, resources[MainMenu].textures[0], "White", font));
		
		//set buttons for load old army menu
		resources[LoadOldArmy].buttons.push_back(Button(0, 550, 200, 50, loa::backButton, resources[MainMenu].textures[0], "Back", font));
		resources[LoadOldArmy].buttons.push_back(Button(600, 550, 200, 50, loa::acceptButton, resources[MainMenu].textures[0], "Accept", font));
		resources[LoadOldArmy].buttons.push_back(Button(300, 50, 200, 50, loa::incrementFilesShown, resources[MainMenu].textures[0], "^", font));
		resources[LoadOldArmy].buttons.push_back(Button(300, 500, 200, 50, loa::incrementFilesShown, resources[MainMenu].textures[0], "v", font));
		//buttons based on files
		resources[LoadOldArmy].buttons.push_back(Button(100, 100, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 150, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 200, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 250, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 300, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 350, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 400, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		resources[LoadOldArmy].buttons.push_back(Button(100, 450, 600, 50, loa::loadArmyFromFile, resources[MainMenu].textures[1], "", font));
		
		//set buttons for editting army menu
		resources[EditingArmy].buttons.push_back(Button(750, 0, 50, 50, ea::menuButton, resources[MainMenu].textures[2], "[=]", font));
		//unit type buttons (generic)
		resources[EditingArmy].buttons.push_back(Button(0, 350, 200, 50, ea::typeButton, resources[MainMenu].textures[0], "Infantry", font));
		resources[EditingArmy].buttons.push_back(Button(0, 400, 200, 50, ea::typeButton, resources[MainMenu].textures[0], "Light", font));
		resources[EditingArmy].buttons.push_back(Button(0, 450, 200, 50, ea::typeButton, resources[MainMenu].textures[0], "Heavy", font));
		resources[EditingArmy].buttons.push_back(Button(0, 500, 200, 50, ea::typeButton, resources[MainMenu].textures[0], "Air", font));
		//available unit buttons (army specific)
	}

	void render(sf::RenderWindow& window, gameState& currentState, std::vector<Resources>& resources){
		switch(currentState){
			case MainMenu:
				//draw buttons
				resources[MainMenu].draw(window);
				break;
				
			case CreateNewArmy:
				resources[CreateNewArmy].draw(window);
				window.draw(workingArmyName);
				break;
				
			case LoadOldArmy:
				resources[LoadOldArmy].draw(window);
				break;
				
			case EditingArmy:
				resources[EditingArmy].draw(window);
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
					loa::updateButtonNames(resources[LoadOldArmy]);
					checkMouseClick(event, currentState, resources[LoadOldArmy]);
					break;
					
				case EditingArmy:
					checkMouseClick(event, currentState, resources[EditingArmy]);
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