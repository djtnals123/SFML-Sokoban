#pragma once
#include "SFML\Graphics.hpp"
#pragma warning(disable: 4996)

class Button_ {
public:
	Button_();
	Button_(std::string string, int position_X, int position_Y);
	void checkClick(sf::Vector2i);
	void setState(bool);
	void Button_::setInvisible(bool iv);
	bool getVar();
	bool getInvisible();
	sf::Text* getText();
private:
	sf::Text* currentTxt;
	sf::Text normal;
	sf::Text clicked;
	sf::Font font;
	bool invisible;
	bool current;
};