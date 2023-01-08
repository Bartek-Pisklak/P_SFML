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
public:

	Bot();
	Bot(std::vector <sf::Vector2i>& liniePlayer, int typ);
	~Bot();

	void updatePlanszaShadow(std::vector <sf::Vector2i>& liniePlayer, ButtonOne plansza[][rozmiar]);
	void droga(std::vector<sf::Vector2i> linieEnemyCurrent, sf::Vector2i& begin, sf::Vector2i& end);
	void normalLVL();


	void createFastDroga(int x,int y);
	void graf(bool& wstawil, std::vector <sf::Vector2i>& trasaKopia, int& x, int& y, int zmiennaX, int zmiennaY);

};

