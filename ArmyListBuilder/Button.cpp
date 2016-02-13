#include "Button.h"

Button::Button(int x, int y, int sizeX, int sizeY, std::function<void(int&, std::string)> buttonFunc, sf::Texture& texture, std::string str, sf::Font& font){
	pos = sf::Vector2f(x, y);
	size = sf::Vector2f(sizeX, sizeY);
	textHeight = 22;
	sprite.setPosition(x, y);
	execute = buttonFunc;
	sprite.setTexture(texture);
	text.setFont(font);
	text.setString(str);
	sf::Rect<float> textSize = text.getLocalBounds();
	text.setOrigin(textSize.width/2, textHeight);//textSize.height);
	text.setPosition(pos.x+size.x/2, pos.y+size.y/2);
}

bool Button::isClicked(sf::Vector2f mousePos){
	if(col::AABB(pos.x, pos.y, size.x, size.y, mousePos.x, mousePos.y)){
		return true;
	}
	return false;
}

void Button::setText(std::string str){
	text.setString(str);
	sf::Rect<float> textSize = text.getLocalBounds();
	text.setOrigin(textSize.width/2, textHeight);//textSize.height);
	text.setPosition(pos.x+size.x/2, pos.y+size.y/2);
}

Button::~Button(){
}