#pragma once
#include"ButtonOne.h"
#include"Bot.h"
#include"Line.h"

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>

# define rozmiar 24

class Plansza : Line // X, Y, Size, Scale // maybe window
{
private:

	float x;
	float y;
	float scale;
	float size;


	ButtonOne plansza[rozmiar][rozmiar];

	int pressButton[2];

	bool klik = false;

	// bot
	Bot enemy;



	void setActiveButton(int x, int y, int a, int b);

public:

	void lineDraw(sf::RenderWindow* window, std::vector <sf::Vector2i> linia);

	void updatePlansza(sf::Vector2f mousePosView);

	void drawPlansza(sf::RenderWindow* window);

	void lineWin();


	Plansza();
	Plansza(float posX,float posY,float size, float scaleB);
	~Plansza();


};

