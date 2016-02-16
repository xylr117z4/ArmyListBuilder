#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <tuple>
#include <functional>
#include "Collisions.h"

class Button{
	public:
		Button(int x, int y, int sizeX, int sizeY, std::function<void(int&, std::string, std::string)> buttonFunc, sf::Texture& texture, std::string str, sf::Font& font);
		bool isClicked(sf::Vector2f mousePos);
		void setText(std::string str);
		sf::Sprite sprite;
		sf::Text text;
		sf::Vector2f size, pos;
		int textHeight;
		std::string extraInfo;
		std::function<void(int&, std::string, std::string)> execute;
		~Button();
};

#endif // BUTTON_H