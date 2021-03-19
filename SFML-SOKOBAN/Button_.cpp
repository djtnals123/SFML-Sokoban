#include "Button_.h"

Button_::Button_()	{}
Button_::Button_(std::string string, int position_X, int position_Y) {
	if (font.loadFromFile("arial.ttf"))//화면에 텍스트를 출력하기 위한 설정
	{
		normal.setString(string);		normal.setPosition(position_X, position_Y);
		normal.setColor(sf::Color::White);	normal.setOutlineColor(sf::Color::Black);
		normal.setCharacterSize(20);		normal.setOutlineThickness(5.0f);	normal.setFont(font);

		clicked.setString(string);	clicked.setPosition(position_X, position_Y);
		clicked.setColor(sf::Color::Red);	clicked.setOutlineColor(sf::Color::Black);
		clicked.setCharacterSize(20);		clicked.setOutlineThickness(5.0f);	clicked.setFont(font);
	}
	this->currentTxt = &this->normal;
	invisible = true;
	current = false;
}
void Button_::checkClick(sf::Vector2i mousePos) {
	if (mousePos.x > currentTxt->getPosition().x + (int)(currentTxt->getLocalBounds().left) &&
		mousePos.x < currentTxt->getPosition().x + (int)(currentTxt->getLocalBounds().width) &&
		mousePos.y > currentTxt->getPosition().y + (int)(currentTxt->getLocalBounds().top) &&
		mousePos.y < currentTxt->getPosition().y + (int)(currentTxt->getLocalBounds().height)) {
			setState(true);
	}
	else setState(false);
	//printf("%d %d\n\n", mousePos.x, mousePos.y);
}
void Button_::setState(bool which) {
	current = which;
	if (current) {
		currentTxt = &clicked;
		return;
	}
	currentTxt = &normal;
}
void Button_::setInvisible(bool iv){
	invisible = iv;
}

bool Button_::getVar() {
	return current;
}
bool Button_::getInvisible() {
	return invisible;
}
sf::Text* Button_::getText() {
	return currentTxt;
}

