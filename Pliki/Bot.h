#pragma once
#include"ButtonOne.h"
#include"Line.h"
#include <iostream>
#include <vector>
#include <ctime>

# define rozmiar 24


class Bot : Line
{
private:
	int whatBot;

	sf::Vector2f whereStart;

	std::vector <sf::Vector2i> roadPoints;


	int planszaShadow[rozmiar][rozmiar];



	bool isDouble(std::vector <sf::Vector2i> roadCopy, std::vector <sf::Vector2i>& pointBeen, int x, int y);
	void createFastDroga(int x, int y);
	void graf(bool& wstawil, std::vector <sf::Vector2i>& roadCopy, std::vector <sf::Vector2i>& pointBeen, int& x, int& y, int zmiennaX, int zmiennaY);

public:

	Bot();
	Bot(std::vector <sf::Vector2i>& linePlayer, int typ);
	~Bot();

	void updatePlanszaShadow(std::vector <sf::Vector2i>& linePlayer, ButtonOne plansza[][rozmiar]);
	void droga(std::vector<sf::Vector2i> lineEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end);
};

