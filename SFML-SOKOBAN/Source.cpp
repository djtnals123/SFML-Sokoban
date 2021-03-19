#include "sokoban.h"

int main()
{
	Sokoban sokoban;
	while (sokoban.window.isOpen())
	{
		sokoban.EventHandler();
		sokoban.WhileHandler();
		sokoban.DrawScreen();
	}
	return 0;
}

Sokoban::Sokoban()
{
	window.create(sf::VideoMode(400, 350), "Sokoban Program");
	CreateShapes();
	CreateButtons();
	StartThisLevel();
	createTexts();
}

void Sokoban::StartThisLevel()
{
	char txt[16];
	sprintf_s(txt, "map\\%d.txt", level);
	fopen_s(&f, txt, "r");

	for (int i = 0; i<X; i++)
	{
		for (int j = 0; j<Y; j++)
		{
			map[i][j] = fgetc(f) - 48;

			if (map[i][j] == '\n' - 48)
			{
				j--;
				continue;
			}
			else if (map[i][j] == EOF) break;
		}
	}
	moveStep = 0;
	checkGoalBox = 0;
}

void Sokoban::CreateShapes()
{
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			null[i][j].setSize(NON_SIZE);
			null[i][j].setPosition((j + 5) * 20, (i + 3) * 20);
			//			rect_w[i][j].setOutlineColor(sf::Color::COLOR);
			//			rect_w[i][j].setOutlineThickness(1.0);

			player[i][j].setRadius(0.0f);
			player[i][j].setFillColor(sf::Color::Red);
			player[i][j].setPosition((j + 5) * 20, (i + 3) * 20);

			box[i][j].setSize(NON_SIZE);
			box[i][j].setFillColor(sf::Color::Blue);
			box[i][j].setPosition((j + 5) * 20, (i + 3) * 20);

			goal[i][j].setRadius(0.0f);
			goal[i][j].setFillColor(sf::Color::Green);
			goal[i][j].setPosition((j + 5) * 20, (i + 3) * 20);

			player_Located_In_Goal[i][j].setRadius(0.0f);
			player_Located_In_Goal[i][j].setFillColor(sf::Color::Yellow);
			player_Located_In_Goal[i][j].setPosition((j + 5) * 20, (i + 3) * 20);

			box_Located_In_Goal[i][j].setRadius(0.0f);
			box_Located_In_Goal[i][j].setFillColor(sf::Color::Cyan);
			box_Located_In_Goal[i][j].setPosition((j + 5) * 20, (i + 3) * 20);

			wall[i][j].setSize(NON_SIZE);
			wall[i][j].setFillColor(sf::Color::White);
			wall[i][j].setPosition((j + 5) * 20, (i + 3) * 20);
		}
	}
}
void Sokoban::CreateButtons()
{
	button[2] = new Button_("Resume", 140, 140);
	button[2]->setInvisible(false);
	button[0] = new Button_("Start", 140, 170);
	button[1] = new Button_("Select Stage", 140, 200);
	button[3] = new Button_("Exit", 140, 230);

	button[4] = new Button_("Next", 250, 250);
	button[5] = new Button_("Previous", 250, 280);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			char c[3],lv=(i*5)+j+1;
			itoa(lv, c, 10);
			button[5+lv] = new Button_(c, 90+50*j, 130+50*i);

		}
	}
}
void Sokoban::createTexts()
{
	if (font.loadFromFile("arial.ttf"))//화면에 텍스트를 출력하기 위한 설정
	{
		text[0].setString("120151374 Uh-SuMin(computer engineering department)");		text[0].setPosition(0, 335);
		text[0].setColor(sf::Color::White);	text[0].setOutlineColor(sf::Color::Black);
		text[0].setCharacterSize(10);		text[0].setOutlineThickness(1.0f);			text[0].setFont(font);

		text[1].setPosition(50, 280); //카운트 텍스트
		text[1].setColor(sf::Color::White);	text[1].setOutlineColor(sf::Color::Black);
		text[1].setCharacterSize(20);		text[1].setOutlineThickness(1.0f);			text[1].setFont(font);

		text[2].setPosition(50, 250); //레벨 텍스트
		text[2].setColor(sf::Color::White);	text[2].setOutlineColor(sf::Color::Black);
		text[2].setCharacterSize(20);		text[2].setOutlineThickness(1.0f);			text[2].setFont(font);

		text[3].setString("Sokoban Game");		text[3].setPosition(30, 50);
		text[3].setColor(sf::Color::Green);	text[3].setOutlineColor(sf::Color::White);
		text[3].setCharacterSize(50);		text[3].setOutlineThickness(4.0f);			text[3].setFont(font);
	}
	else {}
}

void Sokoban::reset()
{
	button[2]->setInvisible(false);
	levelChange(1);
	screenMode = 0;
}
int Sokoban::findLocation()
{
	for (int i = 0; i<X; i++)
	{
		for (int j = 0; j<Y; j++)
		{
			if (map[i][j] == 1 || map[i][j] == 4)
			{
				return i * 10 + j;
			}
		}
	}
}
void Sokoban::renderMap()
{
	for (int i = 0; i<X; i++)
	{
		for (int j = 0; j<Y; j++)
		{
			player[i][j].setRadius(0.0f);
			box[i][j].setSize(NON_SIZE);
			goal[i][j].setRadius(0.0f);
			player_Located_In_Goal[i][j].setRadius(0.0f);
			box_Located_In_Goal[i][j].setRadius(0.0f);
			wall[i][j].setSize(NON_SIZE);

			if (map[i][j] == 1)
				player[i][j].setRadius(7.5f);
			else if (map[i][j] == 2)
				box[i][j].setSize(OBJ_SIZE);
			else if (map[i][j] == 3)
				goal[i][j].setRadius(7.5f);
			else if (map[i][j] == 4)
				player_Located_In_Goal[i][j].setRadius(7.5f);
			else if (map[i][j] == 5)
				box_Located_In_Goal[i][j].setRadius(7.5f);
			else if (map[i][j] == 6)
				wall[i][j].setSize(OBJ_SIZE);
		}
	}
}
void Sokoban::clearCheck()
{
	for (int i = 0; i<X; i++)
	{
		for (int j = 0; j<Y; j++)
		{
			if (map[i][j] == 2)
			{
				return;
			}
		}
	}
	levelChange(level + 1);
}
void Sokoban::levelChange(int lv)
{
	if (lv == MAXLEVEL+1)
		reset();
	else
	{
		level = lv;
		moveStep = 0;
		screenMode = 1;
		StartThisLevel();
	}
}

void Sokoban::DrawScreen()
{
	window.clear();
	if (screenMode == 0)
	{
		for (int i = 0; i < 4; i++)
			if(button[i]->getInvisible())
				window.draw(*button[i]->getText());
		window.draw(text[3]);
	}
	else if (screenMode == 1)
	{
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X; j++)
			{
				window.draw(null[i][j]);
				window.draw(player[i][j]);
				window.draw(box[i][j]);
				window.draw(goal[i][j]);
				window.draw(player_Located_In_Goal[i][j]);
				window.draw(box_Located_In_Goal[i][j]);
				window.draw(wall[i][j]);
			}
		}
		for (int i = 0; i < 3; i++)
			window.draw(text[i]);

		for (int i = 4; i < 6; i++)
			if (button[i]->getInvisible())
				window.draw(*button[i]->getText());
	}
	else if (screenMode == 2)
	{
		for (int i = 6; i < 21; i++)
			window.draw(*button[i]->getText());
		window.draw(text[3]);
		window.draw(*button[5]->getText());
	}
	window.display();
}

void Sokoban::EventHandler()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		int location_x = findLocation() % 10;
		int location_y = findLocation() / 10;

		for (int i = 0; i < 21; i++)
			if (button[i]->getInvisible())
				button[i]->checkClick(sf::Vector2i(sf::Mouse::getPosition().x - window.getPosition().x - 8,
					sf::Mouse::getPosition().y - window.getPosition().y - 37));

		if (event.type == sf::Event::Closed)
			window.close();
		if (screenMode == 0)
		{
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (button[0]->getVar() == true) { screenMode = 1;	levelChange(1); }
					else if (button[1]->getVar() == true)	screenMode = 2;
					else if (button[2]->getVar() == true)	screenMode = 1;
					else if (button[3]->getVar() == true)	exit(1);
				}
			}
		}
		else if (screenMode == 1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (map[location_y - 1][location_x] == 0) //이동하려는 위치가 빈공간인 경우 
				{
					map[location_y - 1][location_x] = 1;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					moveStep++;
				}
				else if (map[location_y - 1][location_x] == 2) //이동하려는 위치에 박스가 있을경우
				{
					if (map[location_y - 2][location_x] == 0) //박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y - 2][location_x] = 2;
						map[location_y - 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
					else if (map[location_y - 2][location_x] == 3) //박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y - 2][location_x] = 5;
						map[location_y - 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
				}
				else if (map[location_y - 1][location_x] == 3) //이동하려는 위치가 목표지점인 경우
				{
					map[location_y - 1][location_x] = 4;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					checkGoalBox++;
					moveStep++;
				}
				else if (map[location_y - 1][location_x] == 5) //이동하려는 위치에 목표지점에 위치한 박스가 있을경우
				{
					if (map[location_y - 2][location_x] == 0) //목표지점에 위치한 박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y - 2][location_x] = 2;
						map[location_y - 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
					else if (map[location_y - 2][location_x] == 3) //목표지점에 위치한 박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y - 2][location_x] = 5;
						map[location_y - 1][location_x] = 4;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (map[location_y][location_x - 1] == 0) //이동하려는 위치가 빈공간인 경우 
				{
					map[location_y][location_x - 1] = 1;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					moveStep++;
				}
				else if (map[location_y][location_x - 1] == 2) //이동하려는 위치에 박스가 있을경우
				{
					if (map[location_y][location_x - 2] == 0) //박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y][location_x - 2] = 2;
						map[location_y][location_x - 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
					else if (map[location_y][location_x - 2] == 3) //박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y][location_x - 2] = 5;
						map[location_y][location_x - 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
				}
				else if (map[location_y][location_x - 1] == 3) //이동하려는 위치가 목표지점인 경우
				{
					map[location_y][location_x - 1] = 4;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					checkGoalBox++;
					moveStep++;
				}
				else if (map[location_y][location_x - 1] == 5) //이동하려는 위치에 목표지점에 위치한 박스가 있을경우
				{
					if (map[location_y][location_x - 2] == 0) //목표지점에 위치한 박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y][location_x - 2] = 2;
						map[location_y][location_x - 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
					else if (map[location_y][location_x - 2] == 3) //목표지점에 위치한 박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y][location_x - 2] = 5;
						map[location_y][location_x - 1] = 4;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (map[location_y][location_x + 1] == 0) //이동하려는 위치가 빈공간인 경우 
				{
					map[location_y][location_x + 1] = 1;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					moveStep++;
				}
				else if (map[location_y][location_x + 1] == 2) //이동하려는 위치에 박스가 있을경우
				{
					if (map[location_y][location_x + 2] == 0) //박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y][location_x + 2] = 2;
						map[location_y][location_x + 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
					else if (map[location_y][location_x + 2] == 3) //박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y][location_x + 2] = 5;
						map[location_y][location_x + 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
				}
				else if (map[location_y][location_x + 1] == 3) //이동하려는 위치가 목표지점인 경우
				{
					map[location_y][location_x + 1] = 4;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					checkGoalBox++;
					moveStep++;
				}
				else if (map[location_y][location_x + 1] == 5) //이동하려는 위치에 목표지점에 위치한 박스가 있을경우
				{
					if (map[location_y][location_x + 2] == 0) //목표지점에 위치한 박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y][location_x + 2] = 2;
						map[location_y][location_x + 1] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
					else if (map[location_y][location_x + 2] == 3) //목표지점에 위치한 박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y][location_x + 2] = 5;
						map[location_y][location_x + 1] = 4;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (map[location_y + 1][location_x] == 0) //이동하려는 위치가 빈공간인 경우 
				{
					map[location_y + 1][location_x] = 1;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					moveStep++;
				}
				else if (map[location_y + 1][location_x] == 2) //이동하려는 위치에 박스가 있을경우
				{
					if (map[location_y + 2][location_x] == 0) //박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y + 2][location_x] = 2;
						map[location_y + 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
					else if (map[location_y + 2][location_x] == 3) //박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y + 2][location_x] = 5;
						map[location_y + 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						moveStep++;
					}
				}
				else if (map[location_y + 1][location_x] == 3) //이동하려는 위치가 목표지점인 경우
				{
					map[location_y + 1][location_x] = 4;
					if (checkGoalBox)
					{
						map[location_y][location_x] = 3;
						checkGoalBox--;
					}
					else
						map[location_y][location_x] = 0;
					checkGoalBox++;
					moveStep++;
				}
				else if (map[location_y + 1][location_x] == 5) //이동하려는 위치에 목표지점에 위치한 박스가 있을경우
				{
					if (map[location_y + 2][location_x] == 0) //목표지점에 위치한 박스가 이동될 위치가 빈공간인 경우
					{
						map[location_y + 2][location_x] = 2;
						map[location_y + 1][location_x] = 1;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
					else if (map[location_y + 2][location_x] == 3) //목표지점에 위치한 박스가 이동될 위치가 목표지점인 경우
					{
						map[location_y + 2][location_x] = 5;
						map[location_y + 1][location_x] = 4;
						if (checkGoalBox)
						{
							map[location_y][location_x] = 3;
							checkGoalBox--;
						}
						else
							map[location_y][location_x] = 0;
						checkGoalBox++;
						moveStep++;
					}
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				StartThisLevel();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				button[2]->setInvisible(true);
				screenMode = 0;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (button[4]->getVar() == true) {
						levelChange(level + 1);
					}
					else if (button[5]->getVar() == true) {
						if (level == 1)
							reset();
						else levelChange(level - 1);
					}
				}
			}
		}
		else if (screenMode == 2)
		{
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 6; i < 21; i++)
					{
						if (button[i]->getVar() == true)
						{
							screenMode = 1;
							levelChange(i - 5);
						}
						else if (button[5]->getVar() == true)
							screenMode = 0;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				screenMode = 0;
			}
		}
		//	printf("%d %d", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		//	printf("%d %d\n", sf::Mouse::getPosition().x-window.getPosition().x-8, sf::Mouse::getPosition().y-window.getPosition().y-37);
	}
}
void Sokoban::WhileHandler()
{
	char txt[16];
	sprintf_s(txt, "Step : %d", moveStep);
	text[1].setString(txt);

	sprintf_s(txt, "Level : %d", level);
	text[2].setString(txt);

	clearCheck();
	renderMap();
}
Sokoban::~Sokoban()
{
	fclose(f);
	delete []button;
}