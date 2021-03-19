#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Button_.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define X 9
#define Y 9
#define MAXLEVEL 15

class Sokoban {
public:
	sf::RenderWindow window;
	Button_ *button[21];

	Sokoban();
	void StartThisLevel();
	void CreateShapes();
	void CreateButtons();
	void reset();
	int findLocation();
	void renderMap();
	void clearCheck();
	void levelChange(int lv);
	void DrawScreen();
	void createTexts();
	void EventHandler();
	void WhileHandler();
	~Sokoban();
private:
	FILE * f;

	sf::RectangleShape null[Y][X];					//0-빈공간
	sf::CircleShape player[Y][X];					//1-플레이어
	sf::RectangleShape box[Y][X];					//2-박스
	sf::CircleShape goal[Y][X];						//3-목표지점
	sf::CircleShape player_Located_In_Goal[Y][X];	//4-목표지점에 위차한 플레이어
	sf::CircleShape box_Located_In_Goal[Y][X];		//5-목표지점에 위치한 박스
	sf::RectangleShape wall[Y][X];					//6-벽

	sf::Vector2f const OBJ_SIZE = { 15.0f, 15.0f };
	sf::Vector2f const NON_SIZE = { 0.0f, 0.0f };
	sf::Text text[4];
	sf::Font font;

	int screenMode = 0;
	int level = 1;
	int moveStep = 0;

	int checkGoalBox = 0;

	char map[Y][X];

};


