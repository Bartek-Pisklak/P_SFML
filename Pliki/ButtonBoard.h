#pragma once
#include"ButtonOne.h"
#include"Bot.h"
#include"Line.h"

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>



class ButtonBoard : Line // X, Y, Size, Scale // maybe window
{
private:
	short typeBot;
	float scale;
	float size;
	int pressButton[2];
	sf::Font font;
	sf::Text textWin;

	bool klik = false;
	bool winPlayer = false;
	bool winEnemy = false;

	ButtonOne buttonBoard[MUCHBUTTON][MUCHBUTTON]{};
	Bot enemy;

	void setActiveButton(int x, int y, int a, int b);
	void lineWin();
	void lineDraw(sf::RenderWindow* window, std::vector <sf::Vector2i> line);
	void gameRun(bool &change, int i , int j);
	void sort(std::vector<sf::Vector2i> &line, bool xy);

public:

	void updateButtonBoard(sf::Vector2f mousePosView);
	void drawButtonBoard(sf::RenderWindow* window);


	ButtonBoard();
	ButtonBoard(float posX,float posY,float size, float scaleB, short typeBot=1);
	~ButtonBoard();
};

