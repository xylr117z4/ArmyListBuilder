#include <SFML/Graphics.hpp>
#include <json.hpp>
#include <dirent.h>
#include <stdio.h>
#include <vector>

#include "GeneralFunctions.h"
#include "Collisions.h"

int main(int argc, char **argv){
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	gameState currentState = MainMenu;
	
	std::vector<Resources> resources;
	
	gsh::init(resources);
	
	while (window.isOpen()){
		
        // Process events
        gsh::handleInput(window, currentState, resources);
		
		window.clear();
		gsh::render(window, currentState, resources);
		window.display();
	}


	return 0;
}
